#pragma once

#include "Allocator.h" 

namespace Vein
{

    class LinearAllocator : public Allocator
    {
    public:
        VN_API LinearAllocator(size_t t_size, void* t_start);
        VN_API ~LinearAllocator();

        VN_API void* allocate(size_t t_size, uint8_t t_alignment) override;
        VN_API void deallocate(void* t_p) override;
        VN_API void clear();

    private:
        VN_API LinearAllocator(const LinearAllocator&);

        //Prevent copies because it might cause errors 
        VN_API LinearAllocator& operator=(const LinearAllocator&) = delete;

        void* m_currentPos;
    };

}