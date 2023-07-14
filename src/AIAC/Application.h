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





