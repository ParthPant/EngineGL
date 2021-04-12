#pragma once

#include "spdlog/spdlog.h"
#include <memory>

class Log{
public:
    static void init();

    inline static std::shared_ptr<spdlog::logger>& getLogger() {return _logger;};

private:
    static std::shared_ptr<spdlog::logger> _logger;
};

#define ERROR(...) ::Log::getLogger()->error(__VA_ARGS__)
#define WARN(...) ::Log::getLogger()->warn(__VA_ARGS__)
#define INFO(...) ::Log::getLogger()->info(__VA_ARGS__)
#define TRACE(...) ::Log::getLogger()->trace(__VA_ARGS__)
