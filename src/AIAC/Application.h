#pragma once

#include <stdint.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GLES2/gl2.h>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

namespace AIAC
{
    struct ApplicationSpecification
        {
            const char* name;
            uint32_t winWidth;
            uint32_t winHeight;
            bool isFullscreen;
        };

    class Application
    {
        public:
            Application(const ApplicationSpecification& appSpec);
            virtual ~Application();

            void Init();
            void Run();
            void Close();
            void Shutdown();

            static Application& GetInstance() { return *m_Instance; }
            const ApplicationSpecification& GetSpecification() const { return m_AppSpec; }

        private:
            ApplicationSpecification m_AppSpec;
            bool m_IsRunning = false;
            GLFWwindow* m_Window = nullptr;
            ImVec4 m_WindowBackColor;

        private:
            static Application* m_Instance;

    };
}