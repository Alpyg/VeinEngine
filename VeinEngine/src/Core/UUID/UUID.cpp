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
        m_most = Random::Uint64();
        m_least = Random::Uint64();

        m_most = (m_most & 0xFFFFFFFFFFFF0FFFULL) | 0x0000000000004000ULL;
        m_least = (m_least & 0x3FFFFFFFFFFFFFFFULL) | 0x8000000000000000ULL;
    }

    UUID::UUID(const char* uuidStr)
    {
        UUID uuid = FromString(uuidStr);
        m_most = uuid.m_most;
        m_least = uuid.m_least;
    }

    UUID::UUID(const String& uuidStr)
    {
        UUID uuid = FromString(uuidStr);
        m_most = uuid.m_most;
        m_least = uuid.m_least;
    }

    VN_API UUID& UUID::operator=(const UUID& u)
    {
        m_most = u.m_most; m_least = u.m_least;
        return *this;
    }

    VN_API const String UUID::ToString() const
    {
        std::stringstream ss;
        ss << std::hex << std::nouppercase << std::setfill('0');
    
        uint32_t a = (m_most >> 32);
        uint32_t b = (m_most & 0xFFFFFFFF);
        uint32_t c = (m_least >> 32);
        uint32_t d = (m_least & 0xFFFFFFFF);
    
        ss << std::setw(8) << (a) << '-';
        ss << std::setw(4) << (b >> 16) << '-';
        ss << std::setw(4) << (b & 0xFFFF) << '-';
        ss << std::setw(4) << (c >> 16) << '-';
        ss << std::setw(4) << (c & 0xFFFF);
        ss << std::setw(8) << d;
    
        return String(ss.str().c_str());
    }

    VN_API UUID UUID::FromString(String str)
    {
        UUID uuid;
        String uuidStr = str.replace('-', "");
    
        static std::stringstream ss;
        ss << uuidStr.substr(0, 16);
        ss >> std::hex >> uuid.m_most;
        ss.clear();
        ss << uuidStr.substr(16, 32);
        ss >> std::hex >> uuid.m_least;
        ss.clear();
    
        return uuid;
    }



    VN_API bool operator==(const UUID& lhs, const UUID& rhs) {
        return lhs.m_most == rhs.m_most && lhs.m_least == rhs.m_least;
    };
    VN_API bool operator!=(const UUID& lhs, const UUID& rhs) {
        return lhs.m_most != rhs.m_most || lhs.m_least != rhs.m_least;
    };
    VN_API bool operator>=(const UUID& lhs, const UUID& rhs) {
        return lhs.m_most >= rhs.m_most || (lhs.m_most == rhs.m_most && lhs.m_least >= rhs.m_least);
    };
    VN_API bool operator<=(const UUID& lhs, const UUID& rhs) {
        return lhs.m_most <= rhs.m_most || (lhs.m_most == rhs.m_most && lhs.m_least <= rhs.m_least);
    };
    VN_API bool operator>(const UUID& lhs, const UUID& rhs) {
        return lhs.m_most > rhs.m_most || (lhs.m_most == rhs.m_most && lhs.m_least > rhs.m_least);
    };
    VN_API bool operator<(const UUID& lhs, const UUID& rhs) {
        return lhs.m_most < rhs.m_most || (lhs.m_most == rhs.m_most && lhs.m_least < rhs.m_least);
    };

}