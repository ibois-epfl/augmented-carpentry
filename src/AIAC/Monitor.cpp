#include "aiacpch.h"

#include "AIAC/Monitor.h"
#include "AIAC/Config.h"
#include "AIAC/Log.h"
#include "AIAC/Assert.h"


namespace AIAC
{
    Monitor* Monitor::s_Instance = nullptr;
    Monitor::Monitor()
    {
        AIAC_ASSERT(!s_Instance, "Monitor already exists!");
        s_Instance = this;

        Init();
    }


    void Monitor::Init()
    {
        #ifdef AIAC_DEPLOY_ON_TOUCH
            m_IsTouch = true;
            ImportParamFromConfig();
            if (!FindMonitorID())      { AIAC_ERROR("Monitor ID not found."); exit(EXIT_FAILURE); }

            if (!Check4MonitorNbr())   { AIAC_ERROR("Multiple monitors not supported."); exit(EXIT_FAILURE); }
            if (!Check4MonitorRes())   { AIAC_ERROR("Resolution monitor does not match config. "); exit(EXIT_FAILURE); }

            if (!MapMonitor())         { AIAC_ERROR("Monitor mapping failed."); exit(EXIT_FAILURE); }
        #else
            m_IsTouch = false;
            m_MonitorName = "Non-touchMonitor";
            m_MonitorLinkType = "Non-touchLinkType";
            m_Resolution = ImportMonitorResolution();
            ParseResolution2Int32_t();
        #endif
    }

    inline std::string Monitor::ImportMonitorName() { return  AIAC::Config::Get<std::string>("MonitorSpecs", "monitor_name", "WaveShare WS170120"); }
    inline std::string Monitor::ImportMonitorLinkType() { return AIAC::Config::Get<std::string>("MonitorSpecs", "monitor_link_t", "HDMI"); }
    inline std::string Monitor::ImportMonitorResolution(){ return AIAC::Config::Get<std::string>("MonitorSpecs", "monitor_resolution", "800x400"); }

    void Monitor::ImportParamFromConfig()
    {
        m_MonitorName = ImportMonitorName();
        m_MonitorLinkType = ImportMonitorLinkType();
        m_Resolution = ImportMonitorResolution();
        ParseResolution2Int32_t();
    }


    bool Monitor::FindMonitorID()
    {
        #if __linux__
            const char* command = "xinput";

            if ( m_Fpipe = (FILE*)popen(command, "r") )
            {
                while (fgets(m_Buffer, sizeof(m_Buffer), m_Fpipe))
                {
                    if (strstr(m_Buffer, m_MonitorName.c_str()))
                    {
                        char* monitor_id_ptr = strstr(m_Buffer, "id=");
                        monitor_id_ptr = strchr(monitor_id_ptr, '=') + 1;
                        monitor_id_ptr[3] = '\0';
                        m_TouchMonitorId = atoi(monitor_id_ptr);
                        break;
                    }
                }
                pclose(m_Fpipe);

                if (m_TouchMonitorId == -1) return false;
            }
            else
            {
                AIAC_ERROR("popen() failed");
                exit(EXIT_FAILURE);
            }
            return true;
        #endif
    }

    bool Monitor::Check4MonitorNbr()
    {
        #if __linux__
            const char* command = "xrandr";

            if ( m_Fpipe = (FILE*)popen(command, "r") )
            {
                int monitor_linked_count_of_type = 0;
                while (fgets(m_Buffer, sizeof(m_Buffer), m_Fpipe)) {
                    if (strstr(m_Buffer, m_MonitorLinkType.c_str()))
                    {
                        monitor_linked_count_of_type++;
                        if (monitor_linked_count_of_type > 1) return false;
                    }
                }
                pclose(m_Fpipe);
            }
            else
            {
                AIAC_ERROR("popen() failed");
                exit(EXIT_FAILURE);
            }
            return true;
        #endif
    }

    bool Monitor::Check4MonitorRes()
    {
        #if __linux__
            const char* command = "xrandr";

            if ( m_Fpipe = (FILE*)popen(command, "r") )
            {
                int monitor_linked_count_of_type = 0;
                while (fgets(m_Buffer, sizeof(m_Buffer), m_Fpipe))
                {
                    std::cout << m_Resolution << std::endl;
                    if (strstr(m_Buffer, m_Resolution.c_str()))  return true;
                }
                pclose(m_Fpipe);
            }
            else
            {
                AIAC_ERROR("popen() failed");
                exit(EXIT_FAILURE);
            }
            return false;
        #endif
    }

    bool Monitor::MapMonitor()
    {
        #if __linux__
            std::string commandMto = "xinput map-to-output ";
            commandMto += std::to_string(m_TouchMonitorId);
            commandMto += " ";
            commandMto += m_MonitorLinkType;
            std::string commandMtoId0 = commandMto + "-0";
            std::string commandMtoId1 = commandMto + "-1";

            int commandMto_result = system(commandMtoId0.c_str());
            if (commandMto_result != 0)
                {
                    AIAC_WARN("{} with index 0 failed", commandMtoId0);
                    commandMto_result = system(commandMtoId1.c_str());
                }
            if (commandMto_result != 0)
                {
                    AIAC_CRITICAL("Monitor failed to map to {0}", m_MonitorLinkType);
                    return false;
                }
            return true;
        #endif
    }
}