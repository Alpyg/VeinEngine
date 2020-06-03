#include "vnpch.h"
#include "Core/Memory/StackAllocator.h"

#include "Core/Memory/PointerMath.h"

namespace Vein
{

    StackAllocator::StackAllocator(size_t t_Size, void* t_Start) : Allocator(t_Size, t_Start), m_CurrentPos(t_Start)
    {
        VN_ASSERT(t_Size > 0, "Invalid size");
        #if VN_DEBUG 
        previousPos = nullptr;
        #endif 
    }

    StackAllocator::~StackAllocator()
    {
        #if VN_DEBUG 
        previousPos = nullptr;
        #endif 

        m_CurrentPos = nullptr;
    }

    void* StackAllocator::allocate(size_t t_Size, uint8_t t_Alignment)
    {
        VN_ASSERT(t_Size != 0, "Invalid size");
        uint8_t adjustment = pointer_math::alignForwardAdjustmentWithHeader(m_CurrentPos, t_Alignment, sizeof(AllocationHeader));

        if (m_UserMemory + adjustment + t_Size > m_Size) return nullptr;

        void* aligned_address = pointer_math::add(m_CurrentPos, adjustment);

        //Add Allocation Header 
        AllocationHeader* header = (AllocationHeader*)(pointer_math::subtract(aligned_address, sizeof(AllocationHeader)));
        header->adjustment = adjustment;

        #if VN_DEBUG 
        header->previousAddress = previousPos;
        previousPos = aligned_address;
        #endif 

        m_CurrentPos = pointer_math::add(aligned_address, t_Size);
        m_UserMemory += t_Size + adjustment;
        m_NumAllocations++;

        return aligned_address;
    }

    void StackAllocator::deallocate(void* t_P)
    {
        VN_ASSERT(t_P == previousPos, "{0} has to be the last element of the stack", t_P);

        //Access the AllocationHeader in the bytes before p 
        AllocationHeader* header = (AllocationHeader*)(pointer_math::subtract(t_P, sizeof(AllocationHeader)));
        m_UserMemory -= (uintptr_t)m_CurrentPos - (uintptr_t)t_P + header->adjustment;
        m_CurrentPos = pointer_math::subtract(t_P, header->adjustment);

        #if VN_DEBUG 
        previousPos = header->previousAddress;
        #endif 

        m_NumAllocations--;
    }

}