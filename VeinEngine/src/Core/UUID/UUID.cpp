#include "vnpch.h"
#include "Core/UUID/UUID.h"

#include "Core/Random/Random.h"

#include <random>
#include <iomanip>
#include <sstream>

namespace Vein
{

    UUID::UUID()
    {
        m_Most = Random::Uint64();
        m_Least = Random::Uint64();

        m_Most = (m_Most & 0xFFFFFFFFFFFF0FFFULL) | 0x0000000000004000ULL;
        m_Least = (m_Least & 0x3FFFFFFFFFFFFFFFULL) | 0x8000000000000000ULL;
    }

    UUID::UUID(const char* t_UuidStr)
    {
        UUID uuid = FromString(t_UuidStr);
        m_Most = uuid.m_Most;
        m_Least = uuid.m_Least;
    }

    UUID::UUID(const String& t_UuidStr)
    {
        UUID uuid = FromString(t_UuidStr);
        m_Most = uuid.m_Most;
        m_Least = uuid.m_Least;
    }

    VN_API UUID& UUID::operator=(const UUID& u)
    {
        m_Most = u.m_Most; m_Least = u.m_Least;
        return *this;
    }

    VN_API const String UUID::ToString() const
    {
        std::stringstream ss;
        ss << std::hex << std::nouppercase << std::setfill('0');
    
        uint32_t a = (m_Most >> 32);
        uint32_t b = (m_Most & 0xFFFFFFFF);
        uint32_t c = (m_Least >> 32);
        uint32_t d = (m_Least & 0xFFFFFFFF);
    
        ss << std::setw(8) << (a) << '-';
        ss << std::setw(4) << (b >> 16) << '-';
        ss << std::setw(4) << (b & 0xFFFF) << '-';
        ss << std::setw(4) << (c >> 16) << '-';
        ss << std::setw(4) << (c & 0xFFFF);
        ss << std::setw(8) << d;
    
        return String(ss.str().c_str());
    }

    VN_API UUID UUID::FromString(String t_Str)
    {
        UUID uuid;
        String uuidStr = t_Str.replace('-', "");
    
        static std::stringstream ss;
        ss << uuidStr.substr(0, 16);
        ss >> std::hex >> uuid.m_Most;
        ss.clear();
        ss << uuidStr.substr(16, 32);
        ss >> std::hex >> uuid.m_Least;
        ss.clear();
    
        return uuid;
    }



    VN_API bool operator==(const UUID& lhs, const UUID& rhs) {
        return lhs.m_Most == rhs.m_Most && lhs.m_Least == rhs.m_Least;
    };
    VN_API bool operator!=(const UUID& lhs, const UUID& rhs) {
        return lhs.m_Most != rhs.m_Most || lhs.m_Least != rhs.m_Least;
    };
    VN_API bool operator>=(const UUID& lhs, const UUID& rhs) {
        return lhs.m_Most >= rhs.m_Most || (lhs.m_Most == rhs.m_Most && lhs.m_Least >= rhs.m_Least);
    };
    VN_API bool operator<=(const UUID& lhs, const UUID& rhs) {
        return lhs.m_Most <= rhs.m_Most || (lhs.m_Most == rhs.m_Most && lhs.m_Least <= rhs.m_Least);
    };
    VN_API bool operator>(const UUID& lhs, const UUID& rhs) {
        return lhs.m_Most > rhs.m_Most || (lhs.m_Most == rhs.m_Most && lhs.m_Least > rhs.m_Least);
    };
    VN_API bool operator<(const UUID& lhs, const UUID& rhs) {
        return lhs.m_Most < rhs.m_Most || (lhs.m_Most == rhs.m_Most && lhs.m_Least < rhs.m_Least);
    };

}