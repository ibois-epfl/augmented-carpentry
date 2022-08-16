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

        #ifdef AIAC_DEPLOY_ON_TOUCH
            m_IsTouch = true;
            Init();
        #else
            AIAC_INFO("AC is built for NON-touch monitor.");
            m_IsTouch = false;
        #endif
    }


    void Monitor::Init()
    {
        ImportParamFromConfig();

        if (!FindMonitorID())      { AIAC_ERROR("Monitor ID not found."); return; }

        if (!Check4MonitorNbr())   { AIAC_ERROR("Multiple monitors not supported."); return; }
        if (!Check4MonitorRes())   { AIAC_ERROR("Resolution monitor does not match config. "); return; }

        if (!MapMonitor())         { AIAC_ERROR("Monitor mapping failed."); return; }
    }


    void Monitor::ImportParamFromConfig()
    {
        m_TouchMonitorName = AIAC::Config::Get<std::string>("MonitorSpecs", "monitor_name", "WaveShare WS170120");
        m_TouchMonitorLinkType = AIAC::Config::Get<std::string>("MonitorSpecs", "monitor_link_t", "HDMI");
        m_TouchResolution = AIAC::Config::Get<std::string>("MonitorSpecs", "monitor_resolution", "800x400");

        AIAC_INFO("Monitor name from config: {0}", m_TouchMonitorName);
        AIAC_INFO("Monitor link type from config: {0}", m_TouchMonitorLinkType);
        AIAC_INFO("Monitor resolution from config: {0}", m_TouchResolution);
    }


    bool Monitor::FindMonitorID()
    {
        const char* command = "xinput";

        if ( m_Fpipe = (FILE*)popen(command, "r") )
        {
            while (fgets(m_Buffer, sizeof(m_Buffer), m_Fpipe))
            {
                if (strstr(m_Buffer, m_TouchMonitorName.c_str()))
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
    }

    bool Monitor::Check4MonitorNbr()
    {
        const char* command = "xrandr";

        if ( m_Fpipe = (FILE*)popen(command, "r") )
        {
            int monitor_linked_count_of_type = 0;
            while (fgets(m_Buffer, sizeof(m_Buffer), m_Fpipe)) {
                if (strstr(m_Buffer, m_TouchMonitorLinkType.c_str()))
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
    }

    bool Monitor::Check4MonitorRes()
    {
        const char* command = "xrandr";

        if ( m_Fpipe = (FILE*)popen(command, "r") )
        {
            int monitor_linked_count_of_type = 0;
            while (fgets(m_Buffer, sizeof(m_Buffer), m_Fpipe))
            {
                std::cout << m_TouchResolution << std::endl;
                if (strstr(m_Buffer, m_TouchResolution.c_str()))  return true;
            }
            pclose(m_Fpipe);
        }
        else
        {
            AIAC_ERROR("popen() failed");
            exit(EXIT_FAILURE);
        }
        return false;
    }

    bool Monitor::MapMonitor()
    {
        std::string commandMto = "xinput map-to-output ";
        commandMto += std::to_string(m_TouchMonitorId);
        commandMto += " ";
        commandMto += m_TouchMonitorLinkType;
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
                AIAC_CRITICAL("Monitor failed to map to {0}", m_TouchMonitorLinkType);
                return false;
            }
        return true;
    }






}