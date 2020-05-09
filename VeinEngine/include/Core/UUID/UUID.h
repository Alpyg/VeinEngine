#pragma once

#include "Core/String/String.h"

namespace Vein
{

    class UUID
    {
    public:
        VN_API UUID();
        VN_API virtual ~UUID() = default;
        VN_API UUID& operator=(const UUID& value);

        VN_API const uint64_t GetMost() const { return _most; }
        VN_API const uint64_t GetLeast() const { return _least; }

        VN_API const String ToString() const;
        VN_API static UUID FromString(String str);

        VN_API friend bool operator==(const UUID& lhs, const UUID& rhs);
        VN_API friend bool operator!=(const UUID& lhs, const UUID& rhs);
        VN_API friend bool operator<(const UUID& lhs, const UUID& rhs);
    private:
        uint64_t _most;
        uint64_t _least;
    };

}