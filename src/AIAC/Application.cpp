#include "AIAC/Application.hpp"


inline static void glfwErrorCallback(int error, const char* description) {
    AIAC_CLI_ERROR("GLFW Error ({0}): {1}", error, description);
}


namespace AIAC
{
    Application::Application()
    {
        Init();
    }

    Application::~Application()
    {
        Shutdown();
    }


    void Application::Init()
    {
        // Init AIAC LOGGER ---------------------------------------------------------
        AIAC::Log::Init();

        // Init GLFW ----------------------------------------------------------------
        AIAC_CLI_INFO("Setting up GL+GLSW window");
        glfwSetErrorCallback(glfwErrorCallback);
            if (!glfwInit()) {
                AIAC_CLI_CRITICAL("Failed to initialize glfw");
                exit(EXIT_FAILURE);
            }

        AIAC_CLI_INFO("Decide GL+GLSL versions");
#if defined(IMGUI_IMPL_OPENGL_ES2)
        // GL ES 2.0 + GLSL 100
        const char* glsl_version = "#version 100";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
        // GL 3.2 + GLSL 150
        const char* glsl_version = "#version 150";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
        // GL 3.0 + GLSL 130
        const char* glsl_version = "#version 130";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);  // GL_FALSE to set the full screen
#endif

        AIAC_CLI_INFO("Creating window with graphic content");
        _Window = glfwCreateWindow(1280, 720, "augmented_carpentry", nullptr, nullptr);
        if (_Window == NULL) {
            AIAC_CLI_CRITICAL("Failed to create GLFW window");
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
        glfwMakeContextCurrent(_Window);
        glfwSwapInterval(1);  // Enable vsync

        // Init IMGUI ---------------------------------------------------------------
        AIAC_CLI_INFO("Starting ImGUI...");
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(_Window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        _WindowBackColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        _IsRunning = true;
    }

    void Application::Run()
    {
        AIAC_CLI_INFO("Starting main loop...");
        while (!glfwWindowShouldClose(_Window))
        {
            glfwPollEvents();
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            

            // >>>>>>>>>>>> OUR CODE GOES HERE >>>>>>>>>>>>
            if (_IsRunning)
                ImGui::ShowDemoWindow(&_IsRunning);
                // AIAC::UI::ShowUI(&showDemoWindow);





            // <<<<<<<<<<<< OUR CODE ENDS HERE <<<<<<<<<<<<

            ImGui::Render();
            int displayW, displayH;
            glfwGetFramebufferSize(_Window, &displayW, &displayH);
            glViewport(0, 0, displayW, displayH);
            glClearColor(_WindowBackColor.x * _WindowBackColor.w,
                         _WindowBackColor.y * _WindowBackColor.w,
                         _WindowBackColor.z * _WindowBackColor.w,
                         _WindowBackColor.w);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(_Window);
        }
    }

    void Application::Shutdown()
    {
        // Shutdown IMGUI ---------------------------------------------------------------
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        // Shutdown GLFW/GL -------------------------------------------------------------
        glfwDestroyWindow(_Window);
        glfwTerminate();

        // Shutdown AIAC LOGGER ---------------------------------------------------------
        AIAC::Log::Shutdown();
    }

}
