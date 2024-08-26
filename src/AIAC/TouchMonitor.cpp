#include "aiacpch.h"

#include "AIAC/TouchMonitor.h"
#include "AIAC/Log.h"
#include "AIAC/Config.h"

#include "stb/stb_image.h"
#include "stb/stb_image_write.h"

namespace AIAC
{
    static bool IsGlfwInitialized()
    {
        (void)glfwGetKeyScancode(0);
        return glfwGetError(NULL) != GLFW_NOT_INITIALIZED;
    }

    static void GLFWMonitorCallback(GLFWmonitor* monitor, int event)
    {
        if (event == GLFW_CONNECTED) AIAC_INFO("Monitor connected: {0}", glfwGetMonitorName(monitor));
        else if (event == GLFW_DISCONNECTED) AIAC_INFO("Monitor disconnected: {0}", glfwGetMonitorName(monitor));
    }

    TouchMonitor::TouchMonitor()
    {
        Init();
    }

    TouchMonitor::TouchMonitor(bool isPrintMonitorsInfo)
    : m_IsPrintMonitorsInfo(isPrintMonitorsInfo)
    {
        Init();
    }

    void TouchMonitor::PrintInfoMonitors(int count, GLFWmonitor**& monitors)
    {
        int width_mm, height_mm;
        float xScale, yScale;
        int xPos, yPos;
        int xpos, ypos, width, height;
        for (int i = 0; i < count; i++)
        {
            GLFWmonitor* monitor = monitors[i];

            const GLFWvidmode* mode = glfwGetVideoMode(monitor);
            AIAC_INFO("Monitor {0}: {1}x{2}@{3}Hz", i, mode->width, mode->height, mode->refreshRate);

            glfwGetMonitorPhysicalSize(monitor, &width_mm, &height_mm);
            AIAC_INFO("Monitor {0} physical size: {1}x{2}", i, width_mm, height_mm);

            glfwGetMonitorContentScale(monitor, &xScale, &yScale);
            AIAC_INFO("Monitor {0} content scale: {1}x{2}", i, xScale, yScale);

            glfwGetMonitorPos(monitor, &xPos, &yPos);
            AIAC_INFO("Monitor {0} position: {1}, {2}", i, xPos, yPos);

            glfwGetMonitorWorkarea(monitor, &xpos, &ypos, &width, &height);
            AIAC_INFO("Monitor {0} workarea: {1}, {2}, {3}, {4}", i, xpos, ypos, width, height);

            const char* name = glfwGetMonitorName(monitor);
            AIAC_INFO("Monitor {0} name: {1}", i, name);
        }
    }

    inline std::string TouchMonitor::ImportNameFromConfig() {
        return  AIAC::Config::Get<std::string>(Config::SEC_TOUCH_MONITOR_SPECS, Config::NAME, "WaveShare WS170120"); }
    inline std::string TouchMonitor::ImportVideoModeFromConfig() {
        return AIAC::Config::Get<std::string>(Config::SEC_TOUCH_MONITOR_SPECS, Config::LINK_MODE, "HDMI"); }
    inline std::string TouchMonitor::ImportResolutionFromConfig(){
        return AIAC::Config::Get<std::string>(Config::SEC_TOUCH_MONITOR_SPECS, Config::RESOLUTION, "800x400"); }

    void TouchMonitor::Init()
    {
        m_Name = ImportNameFromConfig();
        m_VideoMode = ImportVideoModeFromConfig();
        m_Resolution = ImportResolutionFromConfig();
        m_IsConnected = false;

        if (IsGlfwInitialized) { AIAC_ASSERT(glfwInit(), "Could not initialize GLFW!"); }
        else { AIAC_CRITICAL("Multiple windows not supported."); exit(EXIT_FAILURE); }

        int count;
        GLFWmonitor** monitors = glfwGetMonitors(&count);
        if(count<=0) { AIAC_CRITICAL("No monitors found."); exit(EXIT_FAILURE); }
        glfwSetMonitorCallback(GLFWMonitorCallback);

        if(m_IsPrintMonitorsInfo) PrintInfoMonitors(count, monitors);

        if(!SiftMonitorsByMode(m_VideoMode, count, monitors)) { AIAC_CRITICAL("No video mode specified found in list monitors."); exit(EXIT_FAILURE); }
        if(!SiftMonitorsByResolution(m_Resolution, m_SiftedMonitors)) { AIAC_CRITICAL("No resolution specified found in list monitors."); exit(EXIT_FAILURE); }
#if __linux__
        if(!GetMonitorID(m_Name)) { AIAC_CRITICAL("No monitor ID retrieved."); exit(EXIT_FAILURE); }

        if(!MapMonitor(m_ID, m_SiftedMonitors[0])) { AIAC_CRITICAL("Mapping monitor failed."); exit(EXIT_FAILURE); }
#endif
        m_IsConnected = true;
    }

    bool TouchMonitor::SiftMonitorsByMode(std::string videoMode, int count, GLFWmonitor**& monitors)
    {
        bool isVideoModPresent = false;

        for (int i = 0; i < count; i++)
        {  
            AIAC_INFO("Monitor {0} name: {1} looking for {2}", i, glfwGetMonitorName(monitors[i]), videoMode.c_str());
            if (strstr(glfwGetMonitorName(monitors[i]), videoMode.c_str()) != NULL)
            {
                AIAC_INFO("Monitor {0} name: {1} found", i, glfwGetMonitorName(monitors[i]));

                isVideoModPresent = true;
                m_SiftedMonitors.push_back(monitors[i]);
            }
        }
        return isVideoModPresent;
    }

    bool TouchMonitor::SiftMonitorsByResolution(std::string res, std::vector<GLFWmonitor*>& monitors)
    {
        bool isResolutionPresent = false;
        int count = monitors.size();
        for (int i = 0; i < count; i++)
        {
            AIAC_INFO("Monitor {0} name: {1} looking for {2}", i, glfwGetMonitorName(monitors[i]), res.c_str());
            const GLFWvidmode* mode = glfwGetVideoMode(monitors[i]);
            AIAC_INFO("Mode width: {0} height: {1}. Looking for {2} x {3}", mode->width, mode->height, std::stoi(res.substr(0, res.find('x'))), std::stoi(res.substr(res.find('x') + 1)));
            if (!(mode->width == std::stoi(res.substr(0, res.find('x'))) && mode->height == std::stoi(res.substr(res.find('x') + 1))))
            {
                monitors.erase(monitors.begin() + i);
            }
            else isResolutionPresent = true;
        }
        if (!isResolutionPresent || monitors.size() > 1) return false; 
        else if (monitors.size() > 1) return false;
        else return true;
    }

    bool TouchMonitor::GetMonitorID(std::string MonitorName)
    {
        char buffer[1024];
        FILE* Fpipe;

        const char* command = "xinput";
        if ( Fpipe = (FILE*)popen(command, "r") )
        {
            while (fgets(buffer, sizeof(buffer), Fpipe))
            {
                if (strstr(buffer, MonitorName.c_str()))
                {
                    char* MonitorConfig_id_ptr = strstr(buffer, "id=");
                    MonitorConfig_id_ptr = strchr(MonitorConfig_id_ptr, '=') + 1;
                    MonitorConfig_id_ptr[3] = '\0';
                    m_ID = atoi(MonitorConfig_id_ptr);
                    break;
                }
            }
            pclose(Fpipe);
        }
        else { AIAC_CRITICAL("popen() failed"); exit(EXIT_FAILURE);}
        if (m_ID == -1) return false;
        return true;
    }

    bool TouchMonitor::MapMonitor(int32_t monitorID, GLFWmonitor* touchMonitor)
    {
        std::string commandMto = "xinput map-to-output ";
        commandMto += std::to_string(monitorID);
        commandMto += " ";
        commandMto += std::string(glfwGetMonitorName(touchMonitor));

        int commandMto_result = system(commandMto.c_str());
        if (commandMto_result != 0) return false;
        return true;
    }

}