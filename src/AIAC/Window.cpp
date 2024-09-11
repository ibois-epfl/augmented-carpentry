#include "aiacpch.h"

#include "AIAC/Window.h"
#include "AIAC/Log.h"
#include "AIAC/Config.h"

#include "stb/stb_image.h"
#include "stb/stb_image_write.h"


namespace AIAC
{
    static uint8_t s_GLFWWindowCount = 0;
    static bool s_IsMouseButtonPressed = false;
    static struct Position { double x, y; } s_CursorPos;

    static void GLFWErrorCallback(int error, const char* description)
    {
        AIAC_ERROR("GLFW Error ({0}): {1}", error, description);
    }

    Window::Window(const WindowProps& props)
    {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;
        m_Data.VSync = props.VSync;
        m_Data.IsResizable = props.IsResizable;
    }

    Window::~Window()
    {
        Shutdown();
    }

    void Window::Init()
    {
        if(s_GLFWWindowCount == 0)
        {
            glfwSetErrorCallback(GLFWErrorCallback);
            AIAC_ASSERT(glfwInit(), "Could not initialize GLFW!");
        } else { AIAC_CRITICAL("Multiple windows not supported."); exit(EXIT_FAILURE); }

        m_GlslVersion = "#version 130";

        int verMajor, verMinor, rev;
        glfwGetVersion(&verMajor, &verMinor, &rev);
        std::cout << "glfw version: " << verMajor << "." << verMinor << "." << rev << std::endl;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef AIAC_DEPLOY_ON_TOUCH
        glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_FALSE);
#else
        glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, m_Data.IsResizable);
#endif

#ifdef AIAC_DEPLOY_ON_TOUCH
        m_TouchMonitor = new AIAC::TouchMonitor();

        const GLFWvidmode* mode = glfwGetVideoMode(m_TouchMonitor->GetGLFWMonitor());
        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

        m_GLFWWindow = glfwCreateWindow(mode->width, mode->height, m_Data.Title, m_TouchMonitor->GetGLFWMonitor(), NULL);
#else
        m_GLFWWindow = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title, NULL, NULL);
#endif

        if (m_GLFWWindow == NULL) {
            AIAC_CRITICAL("Failed to create GLFW window");
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
        ++s_GLFWWindowCount;

        GLFWimage logo[1];
        logo[0].pixels = stbi_load("assets/images/logos/logo_linux_gray_light.png",
        &logo[0].width, &logo[0].height, 0, 4);
        glfwSetWindowIcon(m_GLFWWindow, 1, logo); 
        stbi_image_free(logo[0].pixels);

        glfwMakeContextCurrent(m_GLFWWindow);
        SetVSync(m_Data.VSync);

        glewExperimental = true;
        if (glewInit() != GLEW_OK)
        {
            AIAC_CRITICAL("Failed to initialize GLEW");
            exit(EXIT_FAILURE);
        }

//        glfwSetMouseButtonCallback(m_GLFWWindow, m_MouseButtonCallback);
//        glfwSetCursorPosCallback(m_GLFWWindow, m_MouseMoveCallback);
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

//    void Window::m_MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
//    {
//        if (button == GLFW_MOUSE_BUTTON_LEFT) {
//            if(GLFW_PRESS == action){
//                s_IsMouseButtonPressed = true;
//                double x;
//                double y;
//                glfwGetCursorPos(window, &x, &y);
//                s_CursorPos = { x, y };
//            }
//            else if(GLFW_RELEASE == action)
//                s_IsMouseButtonPressed = false;
//        }
//    }
//
//    void Window::m_MouseMoveCallback(GLFWwindow* window, double x, double y)
//    {
//        if(s_IsMouseButtonPressed)
//        {
//            double x_diff = x - s_CursorPos.x;
//            double y_diff = y - s_CursorPos.y;
//            s_CursorPos = { x, y };
//        }
//    }
}