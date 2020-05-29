#include "vnpch.h"
#include "Core/Random/Random.h"

namespace Vein
{
    Random* Random::s_random = new Random();
    std::random_device Random::m_rd;
    std::mt19937 Random::m_mt;

    Random::Random()
    {
        m_mt = std::mt19937(m_rd());
    }

    VN_API uint16_t Random::Uint16(const uint16_t min, const uint16_t max)
    {
        if (s_random == nullptr)
            s_random = new Random();
        static std::uniform_int_distribution<uint16_t> dist(min, max);

        return dist(s_random->m_mt);
    }

    VN_API uint32_t Random::Uint32(const uint32_t min, const uint32_t max)
    {
        if (s_random == nullptr)
            s_random = new Random();
        static std::uniform_int_distribution<uint32_t> dist(min, max);

        return dist(s_random->m_mt);
    }

    VN_API uint64_t Random::Uint64(const uint64_t min, const uint64_t max)
    {
        if (s_random == nullptr)
            s_random = new Random();
        static std::uniform_int_distribution<uint64_t> dist(min, max);

        return dist(s_random->m_mt);
    }

    VN_API int Random::Int(const int min, const int max)
    {
        if (s_random == nullptr)
            s_random = new Random();
        static std::uniform_int_distribution<int> dist(min, max);

        return dist(s_random->m_mt);
    }

    VN_API float Random::Float(const float t_min, const float t_max)
    {
        if (s_random == nullptr)
            s_random = new Random();
        std::uniform_real_distribution<float> dist(t_min, t_max);

        return dist(s_random->m_mt);
    }

    VN_API double Random::Double(const double min, const double max)
    {
        if (s_random == nullptr)
            s_random = new Random();
        static std::uniform_real_distribution<double> dist(min, max);

        return dist(s_random->m_mt);
    }

}