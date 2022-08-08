#pragma once

#include <GL/gl.h>
#include <GL/glut.h>

#include <GLES2/gl2.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "AIAC/Log.hpp"

namespace AIAC
{
    struct ApplicationSpecification
        {
            std::string name;
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
            void Shutdown();

            static Application& Get() { return *_Instance; }
            const ApplicationSpecification& GetSpecification() const { return _AppSpec; }

        private:
            static ApplicationSpecification _AppSpec;
            bool _IsRunning = false;
            GLFWwindow* _Window = nullptr;
            ImVec4 _WindowBackColor;

        private:
            static Application* _Instance;

    };
}