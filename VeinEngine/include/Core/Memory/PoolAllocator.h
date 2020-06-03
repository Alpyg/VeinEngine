#pragma once

#include "Allocator.h"

namespace Vein
{

    class PoolAllocator : public Allocator
    {
    public:
        VN_API PoolAllocator(size_t t_ObjectSize, uint8_t t_ObjectAlignment, size_t t_Size, void* t_Mem);
        VN_API ~PoolAllocator();

        VN_API void* allocate(size_t t_Size, uint8_t t_Alignment) override;
        VN_API void deallocate(void* t_P) override;

    private:
        VN_API PoolAllocator(const PoolAllocator&);

        //Prevent copies because it might cause errors 
        VN_API PoolAllocator& operator=(const PoolAllocator&) = delete;
        
        size_t m_ObjectSize;
        uint8_t m_ObjectAlignment;
        void** m_FreeList;
    };

}