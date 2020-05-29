#pragma once

#include "Allocator.h"

namespace Vein
{

    class PoolAllocator : public Allocator
    {
    public:
        VN_API PoolAllocator(size_t t_objectSize, uint8_t t_objectAlignment, size_t t_size, void* t_mem);
        VN_API ~PoolAllocator();

        VN_API void* allocate(size_t t_size, uint8_t t_alignment) override;
        VN_API void deallocate(void* t_p) override;

    private:
        VN_API PoolAllocator(const PoolAllocator&);

        //Prevent copies because it might cause errors 
        VN_API PoolAllocator& operator=(const PoolAllocator&) = delete;
        
        size_t m_objectSize;
        uint8_t m_objectAlignment;
        void** m_freeList;
    };

}