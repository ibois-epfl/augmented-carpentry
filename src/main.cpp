
#include <iostream>
#include <string>

#include <GL/glut.h>
#include <GL/gl.h>

#include "GLFW/glfw3.h"
#include "GLES2/gl2.h"  // <-- comes with OpenGL3 or needs to be added?

#include "../deps/imgui/imgui.h"
#include "../deps/imgui/imgui_impl_glfw.h"
#include "../deps/imgui/imgui_impl_opengl3.h"

#include "../deps/spdlog/include/spdlog/spdlog.h"

// #include "../../ACConfig.h"  // ???

#include "AIAC/CLI.hpp"
#include "AIAC/Client.hpp"
#include "AIAC/Log.hpp"


// For more info on imgui structure:https://github.com/ocornut/imgui/blob/master/examples/example_glfw_opengl3/main.cpp


inline static void glfwErrorCallback(int error, const char* description)
{
    AIAC_CLI_ERROR("GLFW Error ({0}): {1}", error, description);
}

int main(int argc, char* argv[])
{
    AIAC::Log::Init();

    const char* glsl_version = "#version 130"; // GL 3.0 + GLSL 130
    glfwSetErrorCallback(glfwErrorCallback);
    if (!glfwInit())
    {
        AIAC_CLI_CRITICAL("Failed to initialize glfw");
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CLI_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow* window = glfwCreateWindow(1280, 720, "augmented_carpentry", nullptr, nullptr);
    if (window == NULL)
    {
        AIAC_CLI_CRITICAL("Failed to create GLFW window");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync


    AIAC_CLI_INFO("Starting ImGUI...");
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    AIAC_CLI_INFO("Starting main loop...");
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // >>>>>>>>>>>> OUR CODE GOES HERE >>>>>>>>>>>>
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);
        // <<<<<<<<<<<< OUR CODE ENDS HERE <<<<<<<<<<<<

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    AIAC_CLI_INFO("Cleaning up ImGui. Glfw, Opengl3...");
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    AIAC::Log::Shutdown();

    return 0;
}
