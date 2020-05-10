#include "vnpch.h"
#include "Core/Random/Random.h"

#include <random>

namespace Vein
{

    VN_API uint16_t Random::RandU16(const uint16_t min, const uint16_t max)
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<uint16_t> dist(min, max);

        return dist(mt);
    }

    VN_API uint32_t Random::RandU32(const uint32_t min, const uint32_t max)
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<uint32_t> dist(min, max);

        return dist(mt);
    }

    VN_API uint64_t Random::RandU64(const uint64_t min, const uint64_t max)
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<uint64_t> dist(min, max);

        return dist(mt);
    }

    VN_API int Random::RandI(const int min, const int max)
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(min, max);
        
        return dist(mt);
    }

    VN_API float Random::RandF(const float min, const float max)
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<float> dist(min, max);

        return dist(mt);
    }

    VN_API double Random::RandD(const double min, const double max)
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(min, max);

        return dist(mt);
    }

}