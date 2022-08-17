#include "aiacpch.h"

#include "AIAC/Application.h"
#include "AIAC/Log.h"


// inline static void glfwErrorCallback(int error, const char* description) {
//     AIAC_ERROR("GLFW Error ({0}): {1}", error, description);
// }


namespace AIAC
{
    Application* Application::s_Instance = nullptr;
    Application::Application(const ApplicationSpecification& appSpec)
        : m_AppSpec(appSpec)
    {
        AIAC_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;
        Init();
    }

    Application::~Application()
    {
        Shutdown();
    }


    void Application::Init()
    {
        m_Window = new AIAC::Window(
            AIAC::WindowProps(
                m_AppSpec.Name,
                m_AppSpec.WinWidth,
                m_AppSpec.WinHeight,
                m_AppSpec.IsResizable,
                m_AppSpec.VSync
            ));
    }

    void Application::Run()
    {
        m_IsRunning = true;

        while (m_Window->IsOpen())
        {
            for (auto& layer : m_LayerStack)
                layer->OnFrameAwake();

            for (auto& layer : m_LayerStack)
                layer->OnFrameStart();

            m_Window->OnUpdate();

            // TODO: this should go to Render.h / this becomes OnRender()
            glViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
            glClearColor(m_AppSpec.WindowBackColor.x * m_AppSpec.WindowBackColor.w,
                         m_AppSpec.WindowBackColor.y * m_AppSpec.WindowBackColor.w,
                         m_AppSpec.WindowBackColor.z * m_AppSpec.WindowBackColor.w,
                         m_AppSpec.WindowBackColor.w);
            glClear(GL_COLOR_BUFFER_BIT);


            for (auto& layer : m_LayerStack)
                layer->OnUIRender();


            for (auto& layer : m_LayerStack)
                layer->OnFrameEnd();


            for (auto& layer : m_LayerStack)
                layer->OnFrameFall();

        }
    }

    void Application::Close()
    {
        m_IsRunning = false;
    }

    void Application::Shutdown()
    {
        for (auto& layer : m_LayerStack)
            layer->OnDetach();

        m_LayerStack.clear();

        // glfwDestroyWindow(m_Window);
        // glfwTerminate();

        m_Window->Shutdown();

        AIAC::Log::Shutdown();
    }

}
