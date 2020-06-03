#pragma once

#ifdef VN_PLATFORM_WINDOWS
    #ifdef BUILD_SHARED_LIB
        #define VN_API __declspec(dllexport)
    #else
        #define VN_API __declspec(dllimport)
    #endif
#elif VN_PLATFORM_LINUX
    #ifdef BUILD_SHARED_LIB
        #define VN_API __attribute__ ((visibility("default")))
    #else
        #define VN_API
    #endif
#endif

#define BIT(x) (1 << x)

#define VN_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)