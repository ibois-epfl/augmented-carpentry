#include "aiacpch.h"

#include "AIAC/Window.h"
// #include "AIAC/Image.h"
#include "AIAC/Log.h"
#include "AIAC/Config.h"

#include "stb/stb_image.h"
#include "stb/stb_image_write.h"


namespace AIAC
{
    static uint8_t s_GLFWWindowCount = 0;

    static void GLFWErrorCallback(int error, const char* description)
    {
        AIAC_ERROR("GLFW Error ({0}): {1}", error, description);
    }

    static void GLFWMonitorCallback(GLFWmonitor* monitor, int event)
    {
        if (event == GLFW_CONNECTED) AIAC_INFO("Monitor connected: {0}", glfwGetMonitorName(monitor));
        else if (event == GLFW_DISCONNECTED) AIAC_INFO("Monitor disconnected: {0}", glfwGetMonitorName(monitor));
    }


    Window::Window(const WindowProps& props)
    {
        Init(props);
    }

    Window::~Window()
    {
        Shutdown();
    }

    void Window::Init(const WindowProps& props)
    {
        if(s_GLFWWindowCount == 0)
        {
            glfwSetErrorCallback(GLFWErrorCallback);
            AIAC_ASSERT(glfwInit(), "Could not initialize GLFW!");
        } else AIAC_CRITICAL("Multiple windows not supported."); EXIT_FAILURE;


        m_GlslVersion = "#version 130";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#ifdef AIAC_DEPLOY_ON_TOUCH
        glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_FALSE);
#else
        glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, props.IsResizable);
#endif


#ifdef AIAC_DEPLOY_ON_TOUCH
    #if __linux__


        // Get videos
        int count;
        GLFWmonitor** monitors = glfwGetMonitors(&count);
        if(count==1) { AIAC_ERROR("No external monitors found."); EXIT_FAILURE; }
        
        glfwSetMonitorCallback(GLFWMonitorCallback);



        // sift from video mode from config
        bool isVideoModPresent = false;
        std::vector<GLFWmonitor*> siftMonitors;
        std::string modeConfig = AIAC::Config::Get<std::string>("TouchMonitorSpecs", "LinkMode");
        for (int i = 0; i < count; i++)
        {
            if (strstr(glfwGetMonitorName(monitors[i]), modeConfig.c_str()) != NULL)
            {
                isVideoModPresent = true;
                siftMonitors.push_back(monitors[i]);
            }
        }
        if (!isVideoModPresent)
        {
            AIAC_ERROR("No external monitor found.");
            EXIT_FAILURE;
        }


        // sift for resolution from config
        std::string resConfig = AIAC::Config::Get<std::string>("TouchMonitorSpecs", "Resolution");
        bool isResolutionPresent = false;
        for (int i = 0; i < siftMonitors.size(); i++)
        {
            const GLFWvidmode* mode = glfwGetVideoMode(siftMonitors[i]);
            if (!(mode->width == std::stoi(resConfig.substr(0, resConfig.find('x'))) && mode->height == std::stoi(resConfig.substr(resConfig.find('x') + 1))))
            {
                siftMonitors.erase(siftMonitors.begin() + i);
            }
            else isResolutionPresent = true;
        }
        if (!isResolutionPresent || siftMonitors.size() > 1)
        {
            AIAC_ERROR("No monitor found with resolution {0}.", resConfig);
            EXIT_FAILURE;
        }
        else if (siftMonitors.size() > 1)
        {
            AIAC_ERROR("Multiple monitors found with resolution {0}.", resConfig);
            EXIT_FAILURE;
        }




        char buffer[1024];
        FILE* Fpipe;
        int32_t TouchMonitorConfigId = -1;
        std::string monitorConfigName = AIAC::Config::Get<std::string>("TouchMonitorSpecs", "Name");

        const char* command = "xinput";
        if ( Fpipe = (FILE*)popen(command, "r") )
        {
            while (fgets(buffer, sizeof(buffer), Fpipe))
            {
                if (strstr(buffer, monitorConfigName.c_str()))
                {
                    char* MonitorConfig_id_ptr = strstr(buffer, "id=");
                    MonitorConfig_id_ptr = strchr(MonitorConfig_id_ptr, '=') + 1;
                    MonitorConfig_id_ptr[3] = '\0';
                    TouchMonitorConfigId = atoi(MonitorConfig_id_ptr);
                    break;
                }
            }
            pclose(Fpipe);
        }
        else
        {
            AIAC_ERROR("popen() failed");
            EXIT_FAILURE;
        }
        if (TouchMonitorConfigId == -1) AIAC_ERROR("Monitor Id not retrieved"); EXIT_FAILURE;




        std::string commandMto = "xinput map-to-output ";
        commandMto += std::to_string(TouchMonitorConfigId);
        commandMto += " ";
        // commandMto += m_MonitorConfigLinkType;
        // commandMto += m_MonitorConfigLinkType;
        // std::string commandMtoId0 = commandMto + "-0";
        // std::string commandMtoId1 = commandMto + "-1";
        // convert to string
        commandMto += std::string(glfwGetMonitorName(siftMonitors[0]));

        int commandMto_result = system(commandMto.c_str());
        // if (commandMto_result != 0)
        //     {
        //         AIAC_WARN("{} with index 0 failed", commandMtoId0);
        //         commandMto_result = system(commandMtoId1.c_str());
        //     }
        if (commandMto_result != 0)
            {
                AIAC_CRITICAL("MonitorConfig failed to map.");
                EXIT_FAILURE;
            }




        //==========================================================================================

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

        //==========================================================================================







        const GLFWvidmode* mode = glfwGetVideoMode(monitors[1]);

        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
        m_GLFWWindow = glfwCreateWindow(mode->width, mode->height, props.Title, monitors[1], NULL);
    #endif
#else
        m_GLFWWindow = glfwCreateWindow(props.Width, props.Height, props.Title, NULL, NULL);
#endif
        if (m_GLFWWindow == NULL) {
            AIAC_CRITICAL("Failed to create GLFW window");
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
        ++s_GLFWWindowCount;


        GLFWimage logo[1];
        logo[0].pixels = stbi_load((AIAC::Config::Get<std::string>("AIAC", "IconPath")).c_str(),
        &logo[0].width, &logo[0].height, 0, 4);
        glfwSetWindowIcon(m_GLFWWindow, 1, logo); 
        stbi_image_free(logo[0].pixels);


        glfwMakeContextCurrent(m_GLFWWindow);
        SetVSync(props.VSync);


        glewExperimental = true;
        if (glewInit() != GLEW_OK)
        {
            AIAC_CRITICAL("Failed to initialize GLEW");
            EXIT_FAILURE;
        }
    }

    void Window::Shutdown()
    {
        glfwDestroyWindow(m_GLFWWindow);
        --s_GLFWWindowCount;
        if (s_GLFWWindowCount == 0)
        {
            glfwTerminate();
        }
    }

    bool Window::IsOpen()
    {
        return !(glfwWindowShouldClose(m_GLFWWindow));
    }

    void Window::OnUpdate()
    {
        glfwPollEvents();
        glfwGetFramebufferSize(m_GLFWWindow, &m_DisplayW, &m_DisplayH);
    }

    void Window::OnBufferSwap()
    {
        glfwSwapBuffers(m_GLFWWindow);
    }

    void Window::SetVSync(bool enabled)
    {
        if(enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);
        m_Data.VSync = enabled;
    }
}