#pragma once

#include "Allocator.h"

namespace Vein
{

    class ProxyAllocator : public Allocator
    {
    public:
        VN_API ProxyAllocator(Allocator& t_Allocator);
        VN_API ~ProxyAllocator();

        VN_API void* allocate(size_t t_Size, uint8_t t_Alignment) override;
        VN_API void deallocate(void* t_P) override;

    private:
        VN_API ProxyAllocator(const ProxyAllocator&);

        //Prevent copies because it might cause errors 
        VN_API ProxyAllocator& operator=(const ProxyAllocator&) = delete;

        Allocator& m_Allocator;
    };

}