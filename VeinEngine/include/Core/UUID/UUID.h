#pragma once

#include "Core/String/String.h"

namespace Vein
{

    class UUID
    {
    public:
        VN_API UUID();
        VN_API UUID(const char* t_UuidStr);
        VN_API UUID(const String& t_UuidStr);
        VN_API virtual ~UUID() = default;
        VN_API UUID& operator=(const UUID& t_Value);

        VN_API const uint64_t GetMost() const { return m_Most; }
        VN_API const uint64_t GetLeast() const { return m_Least; }

        VN_API const String ToString() const;
        VN_API static UUID FromString(String t_Str);

        VN_API friend bool operator==(const UUID& lhs, const UUID& rhs);
        VN_API friend bool operator!=(const UUID& lhs, const UUID& rhs);
        VN_API friend bool operator>(const UUID& lhs, const UUID& rhs);
        VN_API friend bool operator<(const UUID& lhs, const UUID& rhs);
        VN_API friend bool operator>=(const UUID& lhs, const UUID& rhs);
        VN_API friend bool operator<=(const UUID& lhs, const UUID& rhs);
    private:
        uint64_t m_Most;
        uint64_t m_Least;
    };

}