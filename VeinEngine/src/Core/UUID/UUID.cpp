#include "vnpch.h"
#include "Core/UUID/UUID.h"

#include <random>
#include <iomanip>
#include <sstream>

namespace Vein
{

    UUID::UUID()
    {
        static std::random_device rd;
        static std::uniform_int_distribution<uint64_t> dist(0, (uint64_t)(~0));

        _most = dist(rd);
        _least = dist(rd);

        _most = (_most & 0xFFFFFFFFFFFF0FFFULL) | 0x0000000000004000ULL;
        _least = (_least & 0x3FFFFFFFFFFFFFFFULL) | 0x8000000000000000ULL;
    }

    VN_API UUID& UUID::operator=(const UUID& u)
    {
        _most = u._most; _least = u._least;
        return *this;
    }

    VN_API const String UUID::ToString() const
    {
        std::stringstream ss;
        ss << std::hex << std::nouppercase << std::setfill('0');
    
        uint32_t a = (_most >> 32);
        uint32_t b = (_most & 0xFFFFFFFF);
        uint32_t c = (_least >> 32);
        uint32_t d = (_least & 0xFFFFFFFF);
    
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
        String uuidStr = str.remove(str.begin(), str.end(), '-');
    
        static std::stringstream ss;
        ss << uuidStr.substr(0, 16);
        ss >> std::hex >> uuid._most;
        ss.clear();
        ss << uuidStr.substr(16, 32);
        ss >> std::hex >> uuid._least;
        ss.clear();
    
        return uuid;
    }



    VN_API bool operator==(const UUID& lhs, const UUID& rhs) {
        return lhs._most == rhs._most && lhs._least == rhs._least;
    };
    VN_API bool operator!=(const UUID& lhs, const UUID& rhs) {
        return lhs._most != rhs._most || lhs._least != rhs._least;
    };
    VN_API bool operator<(const UUID& lhs, const UUID& rhs) {
        return lhs._most < rhs._most || (lhs._most == rhs._most && lhs._least < rhs._least);
    };

}