#pragma once

#if defined(VN_ENABLE_ASSERTS) && defined(VN_PLATFORM_WINDOWS)
    #define VN_ASSERT(x, ...) { if(!(x)) { VN_ERROR("Assertion Failed: {0}. File: {1}. Line: {2}", __VA_ARGS__, __FILE__, __LINE__); __debugbreak(); } }
#else
    #define VN_ASSERT(x, ...)
#endif