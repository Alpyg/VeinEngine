#pragma once

#include <random>

namespace Vein
{

    class Random
    {
    public:
        VN_API Random();

        VN_API static uint16_t Uint16(const uint16_t t_Min = 0, const uint16_t t_Max = UINT16_MAX);
        VN_API static uint32_t Uint32(const uint32_t t_Min = 0, const uint32_t t_Max = UINT32_MAX);
        VN_API static uint64_t Uint64(const uint64_t t_Min = 0, const uint64_t t_Max = UINT64_MAX);
        VN_API static int Int(const int t_Min = INT_MIN, const int t_Max = INT_MAX);
        VN_API static float Float(const float t_Min = FLT_MIN, const float t_Max = FLT_MAX);
        VN_API static double Double(const double t_Min = DBL_MIN, const double t_Max = DBL_MAX);
    private:
        VN_API static Random* s_Instance;

        static std::random_device m_RD;
        static std::mt19937 m_MT;
    };

}