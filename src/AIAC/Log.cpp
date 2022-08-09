#include "AIAC/Log.h"



namespace AIAC
{
    std::shared_ptr<spdlog::logger> Log::s_Logger;

    void Log::Init()
    {
        spdlog::set_pattern("[source %s] [function %!] [line %#] %^[%T] %n: %v%$");

        s_Logger = spdlog::stdout_color_mt("APP");
        s_Logger->set_level(spdlog::level::trace);
    }

    void Log::Shutdown()
    {
        spdlog::shutdown();
    }
}