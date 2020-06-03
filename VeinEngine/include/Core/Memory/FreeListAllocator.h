#pragma once

#include "Allocator.h"

namespace Vein
{

    class FreeListAllocator : public Allocator
    {
    public:
        VN_API FreeListAllocator(size_t t_Size, void* t_Start);
        VN_API ~FreeListAllocator();

        VN_API void* allocate(size_t t_Size, uint8_t t_Alignment) override;
        VN_API void deallocate(void* t_P) override;

    private:
        VN_API FreeListAllocator(const FreeListAllocator&);

        //Prevent copies because it might cause errors 
        VN_API FreeListAllocator& operator=(const FreeListAllocator&) = delete;

        struct AllocationHeader
        {
            size_t size;
            uint8_t adjustment;
        };
        struct FreeBlock
        {
            size_t size;
            FreeBlock* next;
        };

        FreeBlock* m_FreeBlocks;
    };

}