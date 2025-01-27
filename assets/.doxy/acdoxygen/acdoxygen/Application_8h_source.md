

# File Application.h

[**File List**](files.md) **>** [**AIAC**](dir_21da83368f7816722f2b707a7b03c84f.md) **>** [**Application.h**](Application_8h.md)

[Go to the documentation of this file](Application_8h.md)


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
#pragma once

#include "AIAC/Camera.h"
#include "AIAC/Render/Renderer.h"

#include "AIAC/Assert.h"
#include "AIAC/Window.h"

#include "AIAC/Layer.h"
#include "AIAC/LayerSlam.h"
#include "AIAC/LayerCamera.h"
#include "AIAC/LayerModel.h"
#include "AIAC/LayerToolhead.h"
#include "AIAC/LayerFeedback.h"

#include "AIAC/EventSys/EventBus.h"

#include "AIAC/GOSys/GO.h"

namespace AIAC
{
    struct ApplicationSpecification
        {
            const char* Name;
            uint32_t WinWidth;
            uint32_t WinHeight;
            bool IsResizable;
            bool VSync;
            ImVec4 WindowBackColor;
        };

    class Application
    {
    public:
        Application(const ApplicationSpecification& appSpec);
        virtual ~Application();

        void Run();
        void Close();

        template<typename T>
        void PushLayer()
        {
            static_assert(std::is_base_of<AIAC::Layer, T>::value, "Pushed type is not subclass of Layer!");
            std::shared_ptr<T> layer = std::make_shared<T>();
            m_LayerMap[typeid(T)] = layer;
            m_LayerStack.emplace_back(layer);
            layer->OnAttach();
        }

        template<typename T>
        std::shared_ptr<T> GetLayer()
        {
            static_assert(std::is_base_of<AIAC::Layer, T>::value, "Pushed type is not subclass of Layer!");
            if(std::dynamic_pointer_cast<T>(m_LayerMap[typeid(T)]))
            {
                return std::dynamic_pointer_cast<T>(m_LayerMap[typeid(T)]);
            }
            AIAC_ERROR("Layer not found!");
            AIAC_BREAK();
            return nullptr;
        }

        inline AIAC::Window*& GetWindow() { return m_Window; }  //FIXME: bad practice to return reference of internal variable
        inline Renderer*& GetRenderer() { return m_Renderer; }  //FIXME: bad practice to return reference of internal variable
        inline EventBus*& GetEventBus() { return m_EventBus; }  //FIXME: bad practice to return reference of internal variable
        inline GORegistry* GetGORegistry() { return m_GORegistry; }  //FIXME: bad practice to return reference of internal variable

        inline static Application& GetInstance() { return *s_Instance; }

        inline const ApplicationSpecification& GetSpecification() const { return m_AppSpec; }

    private:
        void Init();
        void Shutdown();

    private:
        ApplicationSpecification m_AppSpec;

        Window* m_Window;
        EventBus* m_EventBus;
        Renderer* m_Renderer;
        GORegistry* m_GORegistry;

        bool m_IsRunning = false;

        std::vector<std::shared_ptr<AIAC::Layer>> m_LayerStack;
        std::unordered_map<std::type_index, std::shared_ptr<AIAC::Layer>> m_LayerMap;

        static Application* s_Instance;
    };
}

#define AIAC_APP AIAC::Application::GetInstance()
#define AIAC_EBUS AIAC_APP.GetEventBus()
#define AIAC_GOREG AIAC_APP.GetGORegistry()





```


