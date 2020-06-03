#include "vnpch.h"
#include "Core/Memory/PoolAllocator.h"

#include "Core/Memory/PointerMath.h"

namespace Vein
{

    PoolAllocator::PoolAllocator(size_t t_ObjectSize, uint8_t t_ObjectAlignment, size_t t_Size, void* t_Mem) : Allocator(t_Size, t_Mem), m_ObjectSize(t_ObjectSize), m_ObjectAlignment(t_ObjectAlignment)
    {
        VN_ASSERT(t_ObjectSize >= sizeof(void*), "Object size has to be larger than a pointer's size");

        //Calculate adjustment needed to keep object correctly aligned 
        uint8_t adjustment = pointer_math::alignForwardAdjustment(t_Mem, t_ObjectAlignment);
        m_FreeList = (void**)pointer_math::add(t_Mem, adjustment);
        size_t numObjects = (t_Size - adjustment) / t_ObjectSize;
        void** p = m_FreeList;

        //Initialize free blocks list 
        for (size_t i = 0; i < numObjects - 1; i++)
        {
            *p = pointer_math::add(p, t_ObjectSize);
            p = (void**)*p;
        }

        *p = nullptr;
    }

    PoolAllocator::~PoolAllocator()
    {
        m_FreeList = nullptr;
    }

    void* PoolAllocator::allocate(size_t t_Size, uint8_t t_Alignment)
    {
        VN_ASSERT(t_Size == m_ObjectSize && t_Alignment == m_ObjectAlignment, "Invalid size");
        if (m_FreeList == nullptr) return nullptr;
        void* p = m_FreeList;
        m_FreeList = (void**)(*m_FreeList);
        m_UserMemory += t_Size;
        m_NumAllocations++;
        return p;
    }

    void PoolAllocator::deallocate(void* t_P)
    {
        *((void**)t_P) = m_FreeList;
        m_FreeList = (void**)t_P;
        m_UserMemory -= m_ObjectSize;
        m_NumAllocations--;
    }

}