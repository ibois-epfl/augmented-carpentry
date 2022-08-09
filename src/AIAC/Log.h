#pragma once

#include "../../deps/spdlog/include/spdlog/spdlog.h"
#include "../../deps/spdlog/include/spdlog/sinks/stdout_color_sinks.h"



namespace AIAC
{
    class Log
    {
    public:

        static void Init();
        static void Shutdown();

        inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }

    private:
        static std::shared_ptr<spdlog::logger> s_Logger;
    };
}

#ifdef SILENT_LOGGING
    #define AIAC_INFO(...)                     SPDLOG_LOGGER_INFO(AIAC::Log::GetLogger(), __VA_ARGS__)
    #define AIAC_WARN(...)                     SPDLOG_LOGGER_WARN(AIAC::Log::GetLogger(), __VA_ARGS__)
    #define AIAC_ERROR(...)                    SPDLOG_LOGGER_ERROR(AIAC::Log::GetLogger(), __VA_ARGS__)
    #define AIAC_CRITICAL(...)                 SPDLOG_LOGGER_CRITICAL(AIAC::Log::GetLogger(), __VA_ARGS__)
#else
    #define AIAC_INFO
    #define AIAC_WARN
    #define AIAC_ERROR
    #define AIAC_CRITICAL
#endif