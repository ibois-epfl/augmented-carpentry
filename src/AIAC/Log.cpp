#include "AIAC/Log.hpp"



namespace AIAC
{
    std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
    std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

    void Log::Init()
    {
        spdlog::set_pattern("[source %s] [function %!] [line %#] %^[%T] %n: %v%$");

        s_CoreLogger = spdlog::stdout_color_mt("CORE");
        s_CoreLogger->set_level(spdlog::level::trace);

        s_ClientLogger = spdlog::stdout_color_mt("CLI");
        s_ClientLogger->set_level(spdlog::level::trace);
    }

    void Log::Shutdown()
    {
        spdlog::shutdown();
    }
}