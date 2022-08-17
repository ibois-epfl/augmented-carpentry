#include "aiacpch.h"

#include "AIAC/Window.h"


namespace AIAC
{
    static uint8_t s_GLFWWindowCount = 0;

    inline static void GLFWErrorCallback(int error, const char* description)
    {
        AIAC_ERROR("GLFW Error ({0}): {1}", error, description);
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

        m_GLFWWindow = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title, nullptr, nullptr);
        if (m_GLFWWindow == NULL) {
            AIAC_CRITICAL("Failed to create GLFW window");
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
        ++s_GLFWWindowCount;

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