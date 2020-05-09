#pragma once

#include "Core/Core.h"
#include <spdlog/spdlog.h>

namespace Vein
{

    class Logger
    {
    public:
        VEIN_EXPORT static void Init();

        VEIN_EXPORT static std::shared_ptr<spdlog::logger>& GetLogger();
    private:
        std::shared_ptr<spdlog::logger> m_Logger;
    };

}

// Logger macros
#define VEIN_INFO(...)			Vein::Logger::GetLogger()->info(__VA_ARGS__)
#define VEIN_WARN(...)			Vein::Logger::GetLogger()->warn(__VA_ARGS__)
#define VEIN_TRACE(...)			Vein::Logger::GetLogger()->trace(__VA_ARGS__)
#define VEIN_ERROR(...)			Vein::Logger::GetLogger()->error(__VA_ARGS__)
#define VEIN_FATAL(...)			Vein::Logger::GetLogger()->critical(__VA_ARGS__)