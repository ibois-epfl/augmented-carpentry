#include "aiacpch.h"

#include "AIAC/Window.h"


namespace AIAC
{
    static uint8_t s_GLFWWindowCount = 0;

    inline static void GLFWErrorCallback(int error, const char* description)
    {
        AIAC_ERROR("GLFW Error ({0}): {1}", error, description);
    }

    static void GLFWMonitorCallbrack(GLFWmonitor* monitor, int event)
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

        //<------------------
        // It might be possible to initialize the monitor here rather than in ACApp.cpp



        int count;
        GLFWmonitor** monitors = glfwGetMonitors(&count);
        AIAC_INFO("Found {0} monitors.", count);

        glfwSetMonitorCallback(GLFWMonitorCallbrack);

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



        //------------------>

        const GLFWvidmode* mode = glfwGetVideoMode(monitors[1]);

        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

        // // TODO: if click on main the screen is black
        // m_GLFWWindow = glfwCreateWindow(mode->width, mode->height, props.Title, monitors[1], NULL);
        // if (m_GLFWWindow == NULL) {
        //     AIAC_CRITICAL("Failed to create GLFW window");
        //     glfwTerminate();
        //     exit(EXIT_FAILURE);
        // }
        // ++s_GLFWWindowCount;

        // // set the window to be focused


        m_GLFWWindow = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title, nullptr, nullptr);
        if (m_GLFWWindow == NULL) {
            AIAC_CRITICAL("Failed to create GLFW window");
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
        ++s_GLFWWindowCount;



        //------------------>




#if defined(IMGUI_IMPL_OPENGL_ES2)
            // GL ES 2.0 + GLSL 100
            m_GlslVersion GLSL_VERSION = "#version 100";
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
            glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
            // GL 3.2 + GLSL 150
            m_GlslVersion GLSL_VERSION = "#version 150";
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
            // GL 3.0 + GLSL 130
            m_GlslVersion = "#version 130";
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            glfwWindowHint(GLFW_RESIZABLE, props.IsResizable);  // GL_FALSE to set the full screen
#endif

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