#include "vnpch.h"
#include "Core/Memory/FreeListAllocator.h"

#include "Core/Memory/PointerMath.h"

namespace Vein
{

    FreeListAllocator::FreeListAllocator(size_t size, void* start) : Allocator(size, start), m_freeBlocks((FreeBlock*)start)
    {
        VN_ASSERT(size > sizeof(FreeBlock), "Invalid size");
        m_freeBlocks->size = size;
        m_freeBlocks->next = nullptr;
    }

    FreeListAllocator::~FreeListAllocator()
    {
        m_freeBlocks = nullptr;
    }

    void* FreeListAllocator::allocate(size_t size, uint8_t alignment)
    {
        VN_ASSERT(size != 0 && alignment != 0, "Invalid size");
        FreeBlock* prev_free_block = nullptr;
        FreeBlock* free_block = m_freeBlocks;

        while (free_block != nullptr)
        {
            //Calculate adjustment needed to keep object correctly aligned 
            uint8_t adjustment = pointer_math::alignForwardAdjustmentWithHeader(free_block, alignment, sizeof(AllocationHeader));
            size_t total_size = size + adjustment;

            //If allocation doesn't fit in this FreeBlock, try the next 
            if (free_block->size < total_size)
            {
                prev_free_block = free_block;
                free_block = free_block->next;
                continue;
            }

            static_assert(sizeof(AllocationHeader) >= sizeof(FreeBlock), "sizeof(AllocationHeader) < sizeof(FreeBlock)");

            //If allocations in the remaining memory will be impossible 
            if (free_block->size - total_size <= sizeof(AllocationHeader))
            {
                //Increase allocation size instead of creating a new FreeBlock 
                total_size = free_block->size;

                if (prev_free_block != nullptr)
                    prev_free_block->next = free_block->next;
                else
                    m_freeBlocks = free_block->next;
            }
            else
            {
                //Else create a new FreeBlock containing remaining memory 
                FreeBlock* next_block = (FreeBlock*)(pointer_math::add(free_block, total_size));

                next_block->size = free_block->size - total_size;
                next_block->next = free_block->next;

                if (prev_free_block != nullptr)
                    prev_free_block->next = next_block;
                else
                    m_freeBlocks = next_block;
            }

            uintptr_t aligned_address = (uintptr_t)free_block + adjustment;
            AllocationHeader* header = (AllocationHeader*)(aligned_address - sizeof(AllocationHeader));
            header->size = total_size;
            header->adjustment = adjustment;
            m_usedMemory += total_size;
            m_numAllocations++;

            VN_ASSERT(pointer_math::alignForwardAdjustment((void*)aligned_address, alignment) == 0, "Invalid alignment");

            return (void*)aligned_address;
        }

        //ASSERT(false && "Couldn't find free block large enough!"); 
        return nullptr;
    }

    void FreeListAllocator::deallocate(void* p)
    {
        VN_ASSERT(p != nullptr, "Invalid pointer: {0}", p);
        AllocationHeader* header = (AllocationHeader*)pointer_math::subtract(p, sizeof(AllocationHeader));
        uintptr_t block_start = reinterpret_cast<uintptr_t>(p) - header->adjustment;
        size_t block_size = header->size;
        uintptr_t block_end = block_start + block_size;
        FreeBlock* prev_free_block = nullptr;
        FreeBlock* free_block = m_freeBlocks;

        while (free_block != nullptr)
        {
            if ((uintptr_t)free_block >= block_end) break;
            prev_free_block = free_block;
            free_block = free_block->next;
        }

        if (prev_free_block == nullptr)
        {
            prev_free_block = (FreeBlock*)block_start;
            prev_free_block->size = block_size;
            prev_free_block->next = m_freeBlocks;
            m_freeBlocks = prev_free_block;
        }
        else if ((uintptr_t)prev_free_block + prev_free_block->size == block_start)
        {
            prev_free_block->size += block_size;
        }
        else
        {
            FreeBlock* temp = (FreeBlock*)block_start;
            temp->size = block_size;
            temp->next = prev_free_block->next;
            prev_free_block->next = temp;
            prev_free_block = temp;
        }

        if (free_block != nullptr && (uintptr_t)free_block == block_end)
        {
            prev_free_block->size += free_block->size;
            prev_free_block->next = free_block->next;
        }

        m_numAllocations--;
        m_usedMemory -= block_size;
    }

}