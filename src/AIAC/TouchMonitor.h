#pragma once

#include "GlHeader.h"


namespace AIAC
{
    class TouchMonitor
    {
    public:
        TouchMonitor();
        TouchMonitor(bool isPrintMonitorsInfo);
        virtual ~TouchMonitor() = default;

        void PrintInfoMonitors(int count, GLFWmonitor**& monitors);

        GLFWmonitor*& GetGLFWMonitor() { return m_SiftedMonitors[0]; }

    private:
        inline std::string ImportNameFromConfig();
        inline std::string ImportVideoModeFromConfig();
        inline std::string ImportResolutionFromConfig();

        void Init();

        bool SiftMonitorsByMode(std::string videoMode, int count, GLFWmonitor**& monitors);
        bool SiftMonitorsByResolution(std::string res, std::vector<GLFWmonitor*>& monitors);
        bool GetMonitorID(std::string MonitorName);
        bool MapMonitor(int32_t monitorID, GLFWmonitor* touchMonitor);

    private:
        std::string m_Name;
        std::string m_VideoMode;
        std::string m_Resolution;

        int32_t m_ID = -1;

        bool m_IsPrintMonitorsInfo;
        bool m_IsConnected = false;

        std::vector<GLFWmonitor*> m_SiftedMonitors = {};
    };
}