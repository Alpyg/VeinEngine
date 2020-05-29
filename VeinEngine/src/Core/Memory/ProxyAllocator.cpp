#include "vnpch.h"
#include "Core/Memory/ProxyAllocator.h"

#include "Core/Memory/PointerMath.h"

namespace Vein
{

    ProxyAllocator::ProxyAllocator(Allocator& t_allocator) : Allocator(t_allocator.getSize(), t_allocator.getStart()), m_allocator(t_allocator)
    {
    }

    ProxyAllocator::~ProxyAllocator()
    {
    }

    void* ProxyAllocator::allocate(size_t t_size, uint8_t t_alignment)
    {
        VN_ASSERT(t_size != 0, "Invalid size");
        m_numAllocations++;
        size_t mem = m_allocator.getUsedMemory();

        void* p = m_allocator.allocate(t_size, t_alignment);
        m_usedMemory += m_allocator.getUsedMemory() - mem;
        return p;
    }

    void ProxyAllocator::deallocate(void* t_p)
    {
        m_numAllocations--;
        size_t mem = m_allocator.getUsedMemory();
        m_allocator.deallocate(t_p);
        m_usedMemory -= mem - m_allocator.getUsedMemory();
    }

}