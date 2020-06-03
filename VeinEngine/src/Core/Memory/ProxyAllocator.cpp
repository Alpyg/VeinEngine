#include "vnpch.h"
#include "Core/Memory/ProxyAllocator.h"

#include "Core/Memory/PointerMath.h"

namespace Vein
{

    ProxyAllocator::ProxyAllocator(Allocator& t_Allocator) : Allocator(t_Allocator.getSize(), t_Allocator.getStart()), m_Allocator(t_Allocator)
    {
    }

    ProxyAllocator::~ProxyAllocator()
    {
    }

    void* ProxyAllocator::allocate(size_t t_Size, uint8_t t_Alignment)
    {
        VN_ASSERT(t_Size != 0, "Invalid size");
        m_NumAllocations++;
        size_t mem = m_Allocator.getUsedMemory();

        void* p = m_Allocator.allocate(t_Size, t_Alignment);
        m_UserMemory += m_Allocator.getUsedMemory() - mem;
        return p;
    }

    void ProxyAllocator::deallocate(void* t_P)
    {
        m_NumAllocations--;
        size_t mem = m_Allocator.getUsedMemory();
        m_Allocator.deallocate(t_P);
        m_UserMemory -= mem - m_Allocator.getUsedMemory();
    }

}