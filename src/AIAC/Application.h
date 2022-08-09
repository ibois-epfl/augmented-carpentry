#pragma once

#include <memory>
#include <stdint.h>
#include <vector>
#include <type_traits>

#include <GL/gl.h>
#include <GL/glut.h>
#include <GLES2/gl2.h>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "AIAC/Camera.h"
#include "AIAC/Layer.h"
#include "AIAC/Assert.h"

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
            m_LayerStack.emplace_back(layer);
            layer->OnAttach();
        }


        void PushLayer(const std::shared_ptr<AIAC::Layer>& layer) { m_LayerStack.emplace_back(layer); layer->OnAttach(); }
        inline static Application& GetInstance() { return *s_Instance; }
        inline const ApplicationSpecification& GetSpecification() const { return m_AppSpec; }


        LayerExample* LayerExampleRef = nullptr;
        LayerCamera* LayerCameraRef = nullptr;

    private:
        void Init();
        void Shutdown();

    public:
        inline static Application& GetInstance() { return *s_Instance; }

        inline const ApplicationSpecification& GetSpecification() const { return m_AppSpec; }

        inline const ImVec4& GetWindowBackColor() const { return m_WindowBackColor; }
        inline void SetWindowBackColor(const ImVec4& color) { m_WindowBackColor = color; }

    private:
        ApplicationSpecification m_AppSpec;
        bool m_IsRunning = false;
        GLFWwindow* m_Window = nullptr;
        ImVec4 m_WindowBackColor;

        std::vector<std::shared_ptr<AIAC::Layer>> m_LayerStack;

        static Application* s_Instance;

    };
}