#include "vnpch.h"
#include "Core/Random/Random.h"

namespace Vein
{
    Random* Random::s_Instance = new Random();
    std::random_device Random::m_RD;
    std::mt19937 Random::m_MT;

    Random::Random()
    {
        m_MT = std::mt19937(m_RD());
    }

    VN_API uint16_t Random::Uint16(const uint16_t t_Min, const uint16_t t_Max)
    {
        if (s_Instance == nullptr)
            s_Instance = new Random();
        static std::uniform_int_distribution<uint16_t> dist(t_Min, t_Max);

        return dist(s_Instance->m_MT);
    }

    VN_API uint32_t Random::Uint32(const uint32_t t_Min, const uint32_t t_Max)
    {
        if (s_Instance == nullptr)
            s_Instance = new Random();
        static std::uniform_int_distribution<uint32_t> dist(t_Min, t_Max);

        return dist(s_Instance->m_MT);
    }

    VN_API uint64_t Random::Uint64(const uint64_t t_Min, const uint64_t t_Max)
    {
        if (s_Instance == nullptr)
            s_Instance = new Random();
        static std::uniform_int_distribution<uint64_t> dist(t_Min, t_Max);

        return dist(s_Instance->m_MT);
    }

    VN_API int Random::Int(const int t_Min, const int t_Max)
    {
        if (s_Instance == nullptr)
            s_Instance = new Random();
        static std::uniform_int_distribution<int> dist(t_Min, t_Max);

        return dist(s_Instance->m_MT);
    }

    VN_API float Random::Float(const float t_Min, const float t_Max)
    {
        if (s_Instance == nullptr)
            s_Instance = new Random();
        std::uniform_real_distribution<float> dist(t_Min, t_Max);

        return dist(s_Instance->m_MT);
    }

    VN_API double Random::Double(const double t_Min, const double t_Max)
    {
        if (s_Instance == nullptr)
            s_Instance = new Random();
        static std::uniform_real_distribution<double> dist(t_Min, t_Max);

        return dist(s_Instance->m_MT);
    }

}