#include "aiacpch.h"

#include "AIAC/Application.h"
#include "AIAC/Log.h"
#include "AIAC/LayerUI.h"
#include "AIAC/LayerRender.h"


// inline static void glfwErrorCallback(int error, const char* description) {
//     AIAC_ERROR("GLFW Error ({0}): {1}", error, description);
// }


namespace AIAC
{
    GLuint VertexArrayID;

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

        // TODO: Move to Render
        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);
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
            // Render->OnRender();
            GetLayer<AIAC::LayerRender>()->OnRender();
            GetLayer<AIAC::LayerUI>()->OnUIRender();


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
