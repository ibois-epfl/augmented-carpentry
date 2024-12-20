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

            m_Window->OnUpdate();
#ifndef HEADLESS_TEST
            m_Renderer->OnRender();

            GetLayer<AIAC::LayerUI>()->OnUIRender();
#endif

            for (auto& layer : m_LayerStack)
                layer->OnFrameEnd();

            m_Window->OnBufferSwap();


            for (auto& layer : m_LayerStack)
                layer->OnFrameFall();

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

    // Function to capture the frame and return pixel data
    std::vector<GLubyte> CaptureFramePixels(const ApplicationSpecification& appSpec) {
        // Assuming your window is m_Window and framebuffer size is known (640x480 in this case)
        std::vector<GLubyte> pixels(appSpec.WinWidth * appSpec.WinHeight * 4); // Assuming RGBA

        glReadPixels(0, 0, appSpec.WinWidth, appSpec.WinHeight, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

        return pixels;
    }

}
