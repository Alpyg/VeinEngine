#pragma once

#include "Allocator.h" 

namespace Vein
{

    class StackAllocator : public Allocator
    {
    public:
        VN_API StackAllocator(size_t t_Size, void* t_Start);
        VN_API ~StackAllocator();

        VN_API void* allocate(size_t t_Size, uint8_t t_Alignment) override;
        VN_API void deallocate(void* t_P) override;

    private:
        VN_API StackAllocator(const StackAllocator&);

        //Prevent copies because it might cause errors 
        VN_API StackAllocator& operator=(const StackAllocator&) = delete;

        struct AllocationHeader
        {
        #if VN_DEBUG 
            void* previousAddress;
        #endif 

            uint8_t adjustment;
        };

        #if VN_DEBUG 
        void* previousPos;
        #endif 

        void* m_CurrentPos;
    };

}