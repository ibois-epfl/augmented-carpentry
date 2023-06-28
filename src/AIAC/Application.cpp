#include "aiacpch.h"

#include "AIAC/Application.h"
#include "AIAC/Log.h"
#include "AIAC/LayerUI.h"


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
        m_Window = new Window(
            WindowProps(
                m_AppSpec.Name,
                m_AppSpec.WinWidth,
                m_AppSpec.WinHeight,
                m_AppSpec.IsResizable,
                m_AppSpec.VSync
            ));

        m_EventBus = new EventBus();

        m_GORegistry = new GORegistry();

        m_Renderer = new Renderer();
    }

    void Application::Run()
    {
        m_IsRunning = true;

        while (m_Window->IsOpen())
        {
            if(!m_EventBus->IsEventQueueEmpty())
                m_EventBus->ProcessQueue();

            for (auto& layer : m_LayerStack)
                layer->OnFrameAwake();

            for (auto& layer : m_LayerStack)
                layer->OnFrameStart();                
            m_Window->ReleaseCurrent();
            m_Window->MakeCurrent();

            m_Window->OnUpdate();

            m_Renderer->OnRender();

            GetLayer<AIAC::LayerUI>()->OnUIRender();

            // m_Window->ReleaseCurrent();

            for (auto& layer : m_LayerStack)
                layer->OnFrameEnd();

            // m_Window->MakeCurrent();  //TODO: add
            m_Window->OnBufferSwap();
            // m_Window->ReleaseCurrent();  //TODO: add


            for (auto& layer : m_LayerStack)
                layer->OnFrameFall();

            // TODO: add an event call to release the context of window
            // m_Window->OnContextRelease();

        }
    }

    void Application::Close()
    {
        m_IsRunning = false;
        Shutdown();
    }

    void Application::Shutdown()
    {
        for (auto& layer : m_LayerStack)
            layer->OnDetach();

        m_LayerStack.clear();

        m_Window->Shutdown();

        AIAC::Log::Shutdown();

        exit(EXIT_SUCCESS);
    }

}
