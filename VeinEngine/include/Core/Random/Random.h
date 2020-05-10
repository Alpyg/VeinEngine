#pragma once

namespace Vein
{

    class Random
    {
    public:
        VN_API static uint16_t RandU16(const uint16_t min = 0, const uint16_t max = UINT16_MAX);
        VN_API static uint32_t RandU32(const uint32_t min = 0, const uint32_t max = UINT32_MAX);
        VN_API static uint64_t RandU64(const uint64_t min = 0, const uint64_t max = UINT64_MAX);
        VN_API static int RandI(const int min = INT_MIN, const int max = INT_MAX);
        VN_API static float RandF(const float min = FLT_MIN, const float max = FLT_MAX);
        VN_API static double RandD(const double min = DBL_MIN, const double max = DBL_MAX);
    };

}