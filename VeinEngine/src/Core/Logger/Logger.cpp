#include "vnpch.h"
#include "Core/Logger/Logger.h"

#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Vein
{
    Logger* logger = nullptr;

    void Logger::Init()
    {
        logger = new Logger();
        spdlog::set_pattern("%^[%T] %n: %v%$");

        logger->_logger = spdlog::stdout_color_mt("VEIN");
        logger->_logger->set_level(spdlog::level::trace);
    }

    std::shared_ptr<spdlog::logger>& Logger::GetLogger()
    {
        if (logger == nullptr) Init();

        return logger->_logger;
    }

}