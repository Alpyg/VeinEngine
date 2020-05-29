#include "vnpch.h"
#include "Core/Memory/StackAllocator.h"

#include "Core/Memory/PointerMath.h"

namespace Vein
{

    StackAllocator::StackAllocator(size_t t_size, void* t_start) : Allocator(t_size, t_start), m_currentPos(t_start)
    {
        VN_ASSERT(t_size > 0, "Invalid size");
        #if VN_DEBUG 
        previousPos = nullptr;
        #endif 
    }

    StackAllocator::~StackAllocator()
    {
        #if VN_DEBUG 
        previousPos = nullptr;
        #endif 

        m_currentPos = nullptr;
    }

    void* StackAllocator::allocate(size_t t_size, uint8_t t_alignment)
    {
        VN_ASSERT(t_size != 0, "Invalid size");
        uint8_t adjustment = pointer_math::alignForwardAdjustmentWithHeader(m_currentPos, t_alignment, sizeof(AllocationHeader));

        if (m_usedMemory + adjustment + t_size > m_size) return nullptr;

        void* aligned_address = pointer_math::add(m_currentPos, adjustment);

        //Add Allocation Header 
        AllocationHeader* header = (AllocationHeader*)(pointer_math::subtract(aligned_address, sizeof(AllocationHeader)));
        header->adjustment = adjustment;

        #if VN_DEBUG 
        header->previousAddress = previousPos;
        previousPos = aligned_address;
        #endif 

        m_currentPos = pointer_math::add(aligned_address, t_size);
        m_usedMemory += t_size + adjustment;
        m_numAllocations++;

        return aligned_address;
    }

    void StackAllocator::deallocate(void* t_p)
    {
        VN_ASSERT(t_p == previousPos, "{0} has to be the last element of the stack", t_p);

        //Access the AllocationHeader in the bytes before p 
        AllocationHeader* header = (AllocationHeader*)(pointer_math::subtract(t_p, sizeof(AllocationHeader)));
        m_usedMemory -= (uintptr_t)m_currentPos - (uintptr_t)t_p + header->adjustment;
        m_currentPos = pointer_math::subtract(t_p, header->adjustment);

        #if VN_DEBUG 
        previousPos = header->previousAddress;
        #endif 

        m_numAllocations--;
    }

}