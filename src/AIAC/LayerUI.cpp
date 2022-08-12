#include "AIAC/LayerUI.h"
#include "AIAC/Application.h"

#include "stb/stb_image.h"
#include "stb/stb_image_write.h"

#include <iostream>

namespace AIAC
{

    void LayerUI::OnAttach()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImGui::StyleColorsLight();
        ImGuiStyle& style = ImGui::GetStyle();
        style.Colors[ImGuiCol_WindowBg] = ImVec4(1.0f, 1.0f, 1.0f, 0.70f);

        style.WindowRounding = 4.0f;
        style.ChildRounding = 4.0f;
        style.FrameRounding = 4.0f;
        style.PopupRounding = 4.0f;
        style.ScrollbarRounding = 4.0f;
        style.GrabRounding = 4.0f;
        style.TabRounding = 4.0f;

        ImGui_ImplGlfw_InitForOpenGL(AIAC_APP.GetWindow(), true);
        ImGui_ImplOpenGL3_Init(AIAC_APP.GetGlslVersion());

        io.Fonts->AddFontFromFileTTF("assets/fonts/UbuntuMono-R.ttf", 16.0f);  //TODO: add to config

        m_IsOpen = new bool(true);

        // Load images from memory
        m_Logo = AIAC::Image("assets/images/logo_linux_gray_light.png", AIAC::ImageType::IM_TEXTURE, ImVec2(60, 60));
        m_DebugImgPlaceHolder = AIAC::Image("assets/images/placeholder_3d_scene.png", AIAC::ImageType::IM_TEXTURE);

        // Set panes UI for layers
        //                 Label    Collapse          PaneContent
        StackPane(PaneUI("Example",   true,   std::bind(&SetPaneUIExample)   ));
        StackPane(PaneUI("Camera",    true,   std::bind(&SetPaneUICamera)    ));
        StackPane(PaneUI("Slam",      true,   std::bind(&SetPaneUISlam)      ));
    }

    void LayerUI::OnFrameStart()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void LayerUI::OnUIRender()
    {
        IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing dear imgui context. Refer to examples app!");
        
        ShowMainUI();
        ShowSceneViewport();


        RenderUI();
    }

    void LayerUI::OnDetach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void LayerUI::RenderUI()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }


    void LayerUI::ShowMainUI()
    {
        ImGui::Begin("augmented_carpentry", m_IsOpen);
        ImGui::Image(m_Logo.GetImTexture().ID, m_Logo.GetImTexture().Size, ImVec2(0, 1), ImVec2(1, 0), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
        ImGui::SameLine();
        ImGui::Text("This is a prototype for augmented_carpentry \n Version 01.00.00 \n Build 2021-01-01 00:00:00 \n IBOIS, EPFL");
        
        for (auto& pane : m_PaneUIStack) pane->Show();
        
        ImGui::End();
    }

    void LayerUI::ShowSceneViewport()
    {
        ImGui::Begin("scene_viewport", m_IsOpen);

        ImGui::Text("PLACEHOLDER for importer UI");

        ImGui::Dummy(ImVec2(0.0f, 10.0f));

        ImGui::Text("3D viewer with fix camera");

        ImGui::BeginChild("scene_viewport_child", ImVec2(0, 0), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
        ImVec2 viewportSize = ImGui::GetContentRegionAvail();
        m_SceneViewportImTexture = m_DebugImgPlaceHolder.GetImTexture();  // DEBUG
        ImGui::Image(m_SceneViewportImTexture.ID, viewportSize, ImVec2(0, 1), ImVec2(1, 0), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
        ImGui::EndChild();
        
        ImGui::End();
    }

    void LayerUI::SetPaneUIExample()
    {
        ImGui::Text("This is a test message for the example layer");
    }

    void LayerUI::SetPaneUICamera()
    {
        ImGui::Text("This layer is responsible for the physical camera.");
        AIAC::Camera& camera = AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera;
        ImGui::Text("Camera is %s", camera.IsOpened() ? "open" : "closed");
        ImGui::Text("Camera resolution: %d x %d", camera.GetWidth(), camera.GetHeight());

        Image frame = AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetCurrentFrame();
        frame.CvtCvMat2ImTexture();
        AIAC::ImTexture frameImTexture = frame.GetImTexture();
        ImGui::Image(frameImTexture.ID, ImVec2(frame.GetImTexture().Size.x * 0.5f, frame.GetImTexture().Size.y * 0.5f));
    }

    void LayerUI::SetPaneUISlam()
    {
        ImGui::Text("Tracked: %s", AIAC_APP.GetLayer<AIAC::LayerSlam>()->IsTracked() ? "Yes" : "No");
        std::string camPoseStr; camPoseStr << AIAC_APP.GetLayer<AIAC::LayerSlam>()->GetCamPoseCv();
        ImGui::Text("Estimated Camera Pose: \n%s", camPoseStr.c_str());
    }

}