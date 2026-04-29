

# File Application.cpp

[**File List**](files.md) **>** [**AIAC**](dir_21da83368f7816722f2b707a7b03c84f.md) **>** [**Application.cpp**](Application_8cpp.md)

[Go to the documentation of this file](Application_8cpp.md)


```C++
// #####################################################################
// >>>>>>>>>>>>>>>>>>>>> BEGINNING OF LEGAL NOTICE >>>>>>>>>>>>>>>>>>>>>
//######################################################################
//
// This source file, along with its associated content, was authored by
// Andrea Settimi, Hong-Bin Yang, Naravich Chutisilp, and numerous other
// contributors. The code was originally developed at the Laboratory for
// Timber Construction (IBOIS, director: Prof. Yves Weinand) at the School of 
// Architecture, Civil and Environmental Engineering (ENAC) at the Swiss
// Federal Institute of Technology in Lausanne (EPFL) for the Doctoral
// Research "Augmented Carpentry" (PhD researcher: Andrea Settimi,
// co-director: Dr. Julien Gamerro, director: Prof. Yves Weinand).
//
// Although the entire repository is distributed under the GPL license,
// these particular source files may also be used under the terms of the
// MIT license. By accessing or using this file, you agree to the following:
//
// 1. You may reproduce, modify, and distribute this file in accordance
//    with the terms of the MIT license.
// 2. You must retain this legal notice in all copies or substantial
//    portions of this file.
// 3. This file is provided "AS IS," without any express or implied
//    warranties, including but not limited to the implied warranties of
//    merchantability and fitness for a particular purpose.
//
// If you cannot or will not comply with the above conditions, you are
// not permitted to use this file. By proceeding, you acknowledge and
// accept all terms and conditions herein.
//
//######################################################################
// <<<<<<<<<<<<<<<<<<<<<<< END OF LEGAL NOTICE <<<<<<<<<<<<<<<<<<<<<<<<
// #####################################################################
//
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
```


