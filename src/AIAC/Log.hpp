#pragma once


#include "Core.hpp"

#include "../../deps/spdlog/include/spdlog/spdlog.h"
#include "../../deps/spdlog/include/spdlog/sinks/stdout_color_sinks.h"



namespace AIAC 
{
    class Log
    {
    public:

        static void Init();
        static void Shutdown();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}


#if SILENT_LOGGING
    #define AIAC_CORE_INFO(...)                     SPDLOG_LOGGER_INFO(AIAC::Log::GetCoreLogger(), __VA_ARGS__)
    #define AIAC_CORE_WARN(...)                     SPDLOG_LOGGER_WARN(AIAC::Log::GetCoreLogger(), __VA_ARGS__)
    #define AIAC_CORE_DEBUG(...)                    SPDLOG_LOGGER_DEBUG(AIAC::Log::GetCoreLogger(), __VA_ARGS__)
    #define AIAC_CORE_ERROR(...)                    SPDLOG_LOGGER_ERROR(AIAC::Log::GetCoreLogger(), __VA_ARGS__)
    #define AIAC_CORE_CRITICAL(...)                 SPDLOG_LOGGER_CRITICAL(AIAC::Log::GetCoreLogger(), __VA_ARGS__)

    #define AIAC_CLI_INFO(...)                      SPDLOG_LOGGER_INFO(AIAC::Log::GetClientLogger(), __VA_ARGS__)
    #define AIAC_CLI_WARN(...)                      SPDLOG_LOGGER_WARN(AIAC::Log::GetClientLogger(), __VA_ARGS__)
    #define AIAC_CLI_DEBUG(...)                     SPDLOG_LOGGER_DEBUG(AIAC::Log::GetClientLogger(), __VA_ARGS__)
    #define AIAC_CLI_ERROR(...)                     SPDLOG_LOGGER_ERROR(AIAC::Log::GetClientLogger(), __VA_ARGS__)
    #define AIAC_CLI_CRITICAL(...)                  SPDLOG_LOGGER_CRITICAL(AIAC::Log::GetClientLogger(), __VA_ARGS__)
#else
    #define AIAC_CORE_INFO
    #define AIAC_CORE_WARN
    #define AIAC_CORE_DEBUG
    #define AIAC_CORE_ERROR
    #define AIAC_CORE_CRITICAL

    #define AIAC_CLI_INFO
    #define AIAC_CLI_WARN
    #define AIAC_CLI_DEBUG
    #define AIAC_CLI_ERROR
    #define AIAC_CLI_CRITICAL
#endif