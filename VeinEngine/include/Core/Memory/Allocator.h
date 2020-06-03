#pragma once

#include <cstdint>
#include "Core/Assert/Assert.h"
#include "Core/Logger/Logger.h"

namespace Vein
{

    class Allocator
    {
    public:
        VN_API Allocator(size_t t_Size, void* t_Start)
        {
            m_Start = t_Start;
            m_Size = t_Size;
            m_UserMemory = 0;
            m_NumAllocations = 0;
        }

        VN_API virtual ~Allocator()
        {
            VN_ASSERT(m_NumAllocations == 0 && m_UserMemory == 0, "Memory Leak Detected");
            m_Start = nullptr; m_Size = 0;
        }

        VN_API virtual void* allocate(size_t t_Size, uint8_t t_Alignment = 4) = 0;
        VN_API virtual void deallocate(void* p) = 0;
        VN_API void* getStart() const { return m_Start; }
        VN_API size_t getSize() const { return m_Size; }
        VN_API size_t getUsedMemory() const { return m_UserMemory; }
        VN_API size_t getNumAllocations() const { return m_NumAllocations; }

    protected:
        void* m_Start;
        size_t m_Size;
        size_t m_UserMemory;
        size_t m_NumAllocations;
    };

    namespace allocator
    {

        template <class T>
        T* allocateNew(Allocator& allocator)
        {
            return new (allocator.allocate(sizeof(T), __alignof(T))) T;
        }

        template <class T>
        T* allocateNew(Allocator& allocator, const T& t)
        {
            return new (allocator.allocate(sizeof(T), __alignof(T))) T(t);
        }

        template <class T>
        void deallocateDelete(Allocator& allocator, T& object)
        {
            object.~T();
            allocator.deallocate(&object);
        }

        template <class T>
        T* allocateArray(Allocator& allocator, size_t length)
        {
            VN_ASSERT(length != 0, "Invalid length");
            uint8_t headerSize = sizeof(size_t) / sizeof(T);

            if (sizeof(size_t) % sizeof(T) > 0) headerSize += 1;

            //Allocate extra space to store array length in the bytes before the array 
            T* p = ((T*)allocator.allocate(sizeof(T) * (length + headerSize), __alignof(T))) + headerSize;
            *(((size_t*)p) - 1) = length;

            for (size_t i = 0; i < length; i++)
                new (&p[i]) T;

            return p;
        }

        template <class T>
        void deallocateArray(Allocator& allocator, T* array)
        {
            VN_ASSERT(array != nullptr, "Invalid array pointer");
            size_t length = *(((size_t*)array) - 1);

            for (size_t i = 0; i < length; i++) array.~T();

            //Calculate how much extra memory was allocated to store the length before the array 
            uint8_t headerSize = sizeof(size_t) / sizeof(T);
            if (sizeof(size_t) % sizeof(T) > 0)
                headerSize += 1;
            allocator.deallocate(array - headerSize);
        }

    }

}