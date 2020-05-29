#include "vnpch.h"
#include "Core/Memory/LinearAllocator.h"

#include "Core/Memory/PointerMath.h"

namespace Vein
{

    LinearAllocator::LinearAllocator(size_t t_size, void* t_start) : Allocator(t_size, t_start), m_currentPos(t_start)
    {
        VN_ASSERT(t_size > 0, "Invalid size");
    }

    LinearAllocator::~LinearAllocator()
    {
        m_currentPos = nullptr;
    }

    void* LinearAllocator::allocate(size_t t_size, uint8_t t_alignment)
    {
        VN_ASSERT(t_size != 0, "Invalid size");
        uint8_t adjustment = pointer_math::alignForwardAdjustment(m_currentPos, t_alignment);

        if (m_usedMemory + adjustment + t_size > m_size) return nullptr;

        uintptr_t aligned_address = (uintptr_t)m_currentPos + adjustment;
        m_currentPos = (void*)(aligned_address + t_size);
        m_usedMemory += t_size + adjustment;
        m_numAllocations++;

        return (void*)aligned_address;
    }

    void LinearAllocator::deallocate(void* t_p)
    {
        VN_WARN("Use clear() instead of deallocate(void* p)");
        clear();
    }

    void LinearAllocator::clear()
    {
        m_numAllocations = 0;
        m_usedMemory = 0;
        m_currentPos = m_start;
    }

}