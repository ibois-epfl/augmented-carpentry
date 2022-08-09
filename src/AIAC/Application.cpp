#include "AIAC/Application.h"

#include "AIAC/Log.h"


inline static void glfwErrorCallback(int error, const char* description) {
    AIAC_ERROR("GLFW Error ({0}): {1}", error, description);
}


namespace AIAC
{
    Application* Application::s_Instance = nullptr;
    Application::Application(const ApplicationSpecification& appSpec)
        : m_AppSpec(appSpec)
    {
        AIAC_ASSERT(!s_Instance, "Application already exists!");
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
        AIAC_INFO("Log System initialised");

        // Init GLFW ----------------------------------------------------------------
        AIAC_INFO("Setting up GL+GLSW window");
        glfwSetErrorCallback(glfwErrorCallback);
            if (!glfwInit()) {
                AIAC_CRITICAL("Failed to initialize glfw");
                exit(EXIT_FAILURE);
            }

        AIAC_INFO("Decide GL+GLSL versions");
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
        glfwWindowHint(GLFW_RESIZABLE, m_AppSpec.IsFullscreen);  // GL_FALSE to set the full screen
#endif

        AIAC_INFO("Creating window with graphic content");
        m_Window = glfwCreateWindow(m_AppSpec.WinWidth, m_AppSpec.WinHeight, m_AppSpec.Name, nullptr, nullptr);
        if (m_Window == NULL) {
            AIAC_CRITICAL("Failed to create GLFW window");
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
        glfwMakeContextCurrent(m_Window);
        glfwSwapInterval(1);  // Enable vsync

        // Init IMGUI ---------------------------------------------------------------
        AIAC_INFO("Starting ImGUI...");
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        io.Fonts->AddFontFromFileTTF("assets/fonts/UbuntuMono-R.ttf", 16.0f);

        m_WindowBackColor = ImVec4(1.00f, 0.00f, 1.00f, 1.00f);
    }

    void Application::Run()
    {
        m_IsRunning = true;

        while (!glfwWindowShouldClose(m_Window))
        {
            for (auto& layer : m_LayerStack)
                layer->OnFrameAwake();


            glfwPollEvents();
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();


            for (auto& layer : m_LayerStack)
                layer->OnFrameStart();


            for (auto& layer : m_LayerStack)
                layer->OnUIRender();


            for (auto& layer : m_LayerStack)
                layer->OnFrameEnd();


            ImGui::Render();
            int displayW, displayH;
            glfwGetFramebufferSize(m_Window, &displayW, &displayH);
            glViewport(0, 0, displayW, displayH);
            glClearColor(m_WindowBackColor.x * m_WindowBackColor.w,
                         m_WindowBackColor.y * m_WindowBackColor.w,
                         m_WindowBackColor.z * m_WindowBackColor.w,
                         m_WindowBackColor.w);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(m_Window);


            for (auto& layer : m_LayerStack)
                layer->OnFrameFall();
        }
    }

    void Application::Close()
    {
        m_IsRunning = false;
    }

    void Application::Shutdown()
    {
        for (auto& layer : m_LayerStack)
            layer->OnDetach();

        m_LayerStack.clear();

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(m_Window);
        glfwTerminate();

        AIAC::Log::Shutdown();
    }

}
