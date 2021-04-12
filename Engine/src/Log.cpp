#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Engine{

std::shared_ptr<spdlog::logger> Log::_logger;

void Log::init()
{
    spdlog::set_pattern("%^[%T] %n: %v%$");

    _logger = spdlog::stdout_color_mt("ENGINE");
    _logger->set_level(spdlog::level::trace);
}

}
