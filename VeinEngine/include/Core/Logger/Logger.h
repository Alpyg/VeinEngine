#pragma once

#include "Core/Core.h"
#include <spdlog/spdlog.h>

namespace Vein
{

    class Logger
    {
    public:
        VN_API static void Init();

        VN_API static std::shared_ptr<spdlog::logger>& GetLogger();
    private:
        std::shared_ptr<spdlog::logger> m_Logger;
    };

}

// Logger macros
#define VN_INFO(...)			Vein::Logger::GetLogger()->info(__VA_ARGS__)
#define VN_WARN(...)			Vein::Logger::GetLogger()->warn(__VA_ARGS__)
#define VN_TRACE(...)			Vein::Logger::GetLogger()->trace(__VA_ARGS__)
#define VN_ERROR(...)			Vein::Logger::GetLogger()->error(__VA_ARGS__)
#define VN_FATAL(...)			Vein::Logger::GetLogger()->critical(__VA_ARGS__)