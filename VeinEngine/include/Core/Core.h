#pragma once

#ifdef VEIN_PLATFORM_WINDOWS
    #ifdef BUILD_SHARED_LIB
        #define VEIN_EXPORT __declspec(dllexport)
    #else
        #define VEIN_EXPORT __declspec(dllimport)
    #endif
#elif VEIN_PLATFORM_LINUX
    #ifdef BUILD_SHARED_LIB
        #define VEIN_EXPORT __attribute__ ((visibility("default")))
    #else
        #define VEIN_EXPORT
    #endif
#endif

#if defined(VEIN_ENABLE_ASSERTS) && defined(VEIN_PLATFORM_WINDOWS)
    #define VEIN_ASSERT(x, ...) { if(!(x)) { VEIN_ERROR("Assertion Failed: {0}. File: {1}. Line: {2}", __VA_ARGS__, __FILE__, __LINE__); __debugbreak(); } }
#else
    #define VEIN_ASSERT(x, ...)
#endif