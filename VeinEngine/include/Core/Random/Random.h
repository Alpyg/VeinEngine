#pragma once

#include <random>

namespace Vein
{

    class Random
    {
    public:
        VN_API Random();

        VN_API static uint16_t Uint16(const uint16_t min = 0, const uint16_t max = UINT16_MAX);
        VN_API static uint32_t Uint32(const uint32_t min = 0, const uint32_t max = UINT32_MAX);
        VN_API static uint64_t Uint64(const uint64_t min = 0, const uint64_t max = UINT64_MAX);
        VN_API static int Int(const int min = INT_MIN, const int max = INT_MAX);
        VN_API static float Float(const float t_min = FLT_MIN, const float t_max = FLT_MAX);
        VN_API static double Double(const double min = DBL_MIN, const double max = DBL_MAX);
    private:
        VN_API static Random* s_random;

        static std::random_device m_rd;
        static std::mt19937 m_mt;
    };

}