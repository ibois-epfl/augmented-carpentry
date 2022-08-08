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
    class Application
    {
        public:
            Application();
            ~Application();

            void Init();
            void Run();
            void Shutdown();
        
        private:
            bool _IsRunning = false;
            GLFWwindow* _Window = nullptr;
            ImVec4 _WindowBackColor = ImVec4(0.f, 0.f, 0.f, 1.f);

    };
}