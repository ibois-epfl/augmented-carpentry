#pragma once

#include <memory>
#include <stdint.h>
#include <vector>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

#include "AIAC/Camera.h"
#include "AIAC/Layer.h"
#include "AIAC/Assert.h"

#include "AIAC/LayerSlam.h"
#include "AIAC/LayerCamera.h"
#include "AIAC/LayerExample.h"

namespace AIAC
{
    struct ApplicationSpecification
        {
            const char* Name;
            uint32_t WinWidth;
            uint32_t WinHeight;
            bool IsResizable;
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

        inline static Application& GetInstance() { return *s_Instance; }

        inline const ApplicationSpecification& GetSpecification() const { return m_AppSpec; }
        inline GLFWwindow* GetWindow() const { return m_Window; }
        inline const char* GetGlslVersion() const { return m_GlslVersion; }

        inline const ImVec4& GetWindowBackColor() const { return m_WindowBackColor; }
        inline void SetWindowBackColor(const ImVec4& color) { m_WindowBackColor = color; }

    private:
        void Init();
        void Shutdown();

    private:
        ApplicationSpecification m_AppSpec;
        bool m_IsRunning = false;
        GLFWwindow* m_Window;
        const char* m_GlslVersion;
        ImVec4 m_WindowBackColor;

        std::vector<std::shared_ptr<AIAC::Layer>> m_LayerStack;
        std::unordered_map<std::type_index, std::shared_ptr<AIAC::Layer>> m_LayerMap;

        static Application* s_Instance;
    };
}

#define AIAC_APP() AIAC::Application::GetInstance()


