#include "aiacpch.h"

#include "AIAC/MonitorConfig.h"
#include "AIAC/Config.h"
#include "AIAC/Log.h"
#include "AIAC/Assert.h"


namespace AIAC
{
    MonitorConfig* MonitorConfig::s_Instance = nullptr;
    MonitorConfig::MonitorConfig()
    {
        AIAC_ASSERT(!s_Instance, "MonitorConfig already exists!");
        s_Instance = this;

        Init();
    }


    void MonitorConfig::Init()
    {
#ifdef AIAC_DEPLOY_ON_TOUCH
            m_IsTouch = true;
            ImportParamFromConfig();
            if (!FindMonitorConfigID())      { AIAC_ERROR("MonitorConfig ID not found."); EXIT_FAILURE; }

            if (!Check4MonitorConfigNbr())   { AIAC_ERROR("Multiple MonitorConfigs not supported."); EXIT_FAILURE; }
            if (!Check4MonitorConfigRes())   { AIAC_ERROR("Resolution MonitorConfig does not match config. "); EXIT_FAILURE; }

            if (!MapMonitorConfig())         { AIAC_ERROR("MonitorConfig mapping failed."); EXIT_FAILURE; }
#else
            m_IsTouch = false;
            m_MonitorConfigName = "Non-touchMonitorConfig";
            m_MonitorConfigLinkType = "Non-touchLinkType";
            m_Resolution = ImportMonitorConfigResolutionFromConfig();
            ParseResolution2Int32_t();
#endif
    }

    inline std::string MonitorConfig::ImportMonitorConfigNameFromConfig() { return  AIAC::Config::Get<std::string>("MonitorConfigSpecs", "MonitorConfig_name", "WaveShare WS170120"); }
    inline std::string MonitorConfig::ImportMonitorConfigLinkTypeFromConfig() { return AIAC::Config::Get<std::string>("MonitorConfigSpecs", "MonitorConfig_link_t", "HDMI"); }
    inline std::string MonitorConfig::ImportMonitorConfigResolutionFromConfig(){ return AIAC::Config::Get<std::string>("MonitorConfigSpecs", "MonitorConfig_resolution", "800x400"); }

    void MonitorConfig::ImportParamFromConfig()
    {
        m_MonitorConfigName = ImportMonitorConfigNameFromConfig();
        m_MonitorConfigLinkType = ImportMonitorConfigLinkTypeFromConfig();
        m_Resolution = ImportMonitorConfigResolutionFromConfig();
        ParseResolution2Int32_t();
    }


    bool MonitorConfig::FindMonitorConfigID()
    {
#if __linux__
            const char* command = "xinput";

            if ( m_Fpipe = (FILE*)popen(command, "r") )
            {
                while (fgets(m_Buffer, sizeof(m_Buffer), m_Fpipe))
                {
                    if (strstr(m_Buffer, m_MonitorConfigName.c_str()))
                    {
                        char* MonitorConfig_id_ptr = strstr(m_Buffer, "id=");
                        MonitorConfig_id_ptr = strchr(MonitorConfig_id_ptr, '=') + 1;
                        MonitorConfig_id_ptr[3] = '\0';
                        m_TouchMonitorConfigId = atoi(MonitorConfig_id_ptr);
                        break;
                    }
                }
                pclose(m_Fpipe);

                if (m_TouchMonitorConfigId == -1) return false;
            }
            else
            {
                AIAC_ERROR("popen() failed");
                EXIT_FAILURE;
            }
            return true;
#endif
    }

    bool MonitorConfig::Check4MonitorConfigNbr()
    {
#if __linux__
            const char* command = "xrandr";

            if ( m_Fpipe = (FILE*)popen(command, "r") )
            {
                int MonitorConfig_linked_count_of_type = 0;
                while (fgets(m_Buffer, sizeof(m_Buffer), m_Fpipe)) {
                    if (strstr(m_Buffer, m_MonitorConfigLinkType.c_str()))
                    {
                        MonitorConfig_linked_count_of_type++;
                        if (MonitorConfig_linked_count_of_type > 1) return false;
                    }
                }
                pclose(m_Fpipe);
            }
            else
            {
                AIAC_ERROR("popen() failed");
                EXIT_FAILURE;
            }
            return true;
#endif
    }

    bool MonitorConfig::Check4MonitorConfigRes()
    {
#if __linux__
            const char* command = "xrandr";

            if ( m_Fpipe = (FILE*)popen(command, "r") )
            {
                int MonitorConfig_linked_count_of_type = 0;
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
                EXIT_FAILURE;
            }
            return false;
#endif
    }

    bool MonitorConfig::MapMonitorConfig()
    {
#if __linux__
            std::string commandMto = "xinput map-to-output ";
            commandMto += std::to_string(m_TouchMonitorConfigId);
            commandMto += " ";
            commandMto += m_MonitorConfigLinkType;
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
                    AIAC_CRITICAL("MonitorConfig failed to map to {0}", m_MonitorConfigLinkType);
                    return false;
                }
            return true;
#endif
    }
}