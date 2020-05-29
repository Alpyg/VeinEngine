#include "vnpch.h"
#include "Core/Memory/PoolAllocator.h"

#include "Core/Memory/PointerMath.h"

namespace Vein
{

    PoolAllocator::PoolAllocator(size_t t_objectSize, uint8_t t_objectAlignment, size_t t_size, void* t_mem) : Allocator(t_size, t_mem), m_objectSize(t_objectSize), m_objectAlignment(t_objectAlignment)
    {
        VN_ASSERT(t_objectSize >= sizeof(void*), "Object size has to be larger than a pointer's size");

        //Calculate adjustment needed to keep object correctly aligned 
        uint8_t adjustment = pointer_math::alignForwardAdjustment(t_mem, t_objectAlignment);
        m_freeList = (void**)pointer_math::add(t_mem, adjustment);
        size_t numObjects = (t_size - adjustment) / t_objectSize;
        void** p = m_freeList;

        //Initialize free blocks list 
        for (size_t i = 0; i < numObjects - 1; i++)
        {
            *p = pointer_math::add(p, t_objectSize);
            p = (void**)*p;
        }

        *p = nullptr;
    }

    PoolAllocator::~PoolAllocator()
    {
        m_freeList = nullptr;
    }

    void* PoolAllocator::allocate(size_t t_size, uint8_t t_alignment)
    {
        VN_ASSERT(t_size == m_objectSize && t_alignment == m_objectAlignment, "Invalid size");
        if (m_freeList == nullptr) return nullptr;
        void* p = m_freeList;
        m_freeList = (void**)(*m_freeList);
        m_usedMemory += t_size;
        m_numAllocations++;
        return p;
    }

    void PoolAllocator::deallocate(void* t_p)
    {
        *((void**)t_p) = m_freeList;
        m_freeList = (void**)t_p;
        m_usedMemory -= m_objectSize;
        m_numAllocations--;
    }

}