#include "vnpch.h"
#include "Core/Memory/LinearAllocator.h"

#include "Core/Memory/PointerMath.h"

namespace Vein
{

    LinearAllocator::LinearAllocator(size_t t_Size, void* t_Start) : Allocator(t_Size, t_Start), m_CurrentPos(t_Start)
    {
        VN_ASSERT(t_Size > 0, "Invalid size");
    }

    LinearAllocator::~LinearAllocator()
    {
        m_CurrentPos = nullptr;
    }

    void* LinearAllocator::allocate(size_t t_Size, uint8_t t_Alignment)
    {
        VN_ASSERT(t_Size != 0, "Invalid size");
        uint8_t adjustment = pointer_math::alignForwardAdjustment(m_CurrentPos, t_Alignment);

        if (m_UserMemory + adjustment + t_Size > m_Size) return nullptr;

        uintptr_t aligned_address = (uintptr_t)m_CurrentPos + adjustment;
        m_CurrentPos = (void*)(aligned_address + t_Size);
        m_UserMemory += t_Size + adjustment;
        m_NumAllocations++;

        return (void*)aligned_address;
    }

    void LinearAllocator::deallocate(void* t_P)
    {
        VN_WARN("Use clear() instead of deallocate(void* p)");
        clear();
    }

    void LinearAllocator::clear()
    {
        m_NumAllocations = 0;
        m_UserMemory = 0;
        m_CurrentPos = m_Start;
    }

}