#include "aiacpch.h"

#include "AIAC/LayerUI.h"
#include "AIAC/Application.h"

#include "AIAC/Image.h"
#include "AIAC/Renderer.h"

#include "AIAC/UI/ImGuiFileDialog.h"

#include "AIAC/UI/ClrPalette.h"
#include "AIAC/UI/CustomLogos.h"

#include "eventpp/callbacklist.h"

namespace AIAC
{

    void LayerUI::OnAttach()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImGui::StyleColorsLight();
        ImGuiStyle& style = ImGui::GetStyle();
        style.Colors[ImGuiCol_MenuBarBg] = ImVec4(1.0f, 1.0f, 1.0f, 0.05f);
        style.Colors[ImGuiCol_WindowBg] = ImVec4(1.0f, 1.0f, 1.0f, 0.70f);
        style.ScrollbarSize = 20.0f;

        style.WindowRounding = 4.0f;
        style.ChildRounding = 4.0f;
        style.FrameRounding = 4.0f;
        style.PopupRounding = 4.0f;
        style.ScrollbarRounding = 4.0f;
        style.GrabRounding = 4.0f;
        style.TabRounding = 4.0f;

        ImGui_ImplGlfw_InitForOpenGL(AIAC_APP.GetWindow()->GetGLFWWindow(), true);
        ImGui_ImplOpenGL3_Init(AIAC_APP.GetWindow()->GetGlslVersion());

        io.Fonts->AddFontFromFileTTF("assets/fonts/UbuntuMono-R.ttf", 14.0f);  // default

        m_IsOpen = new bool(true);

        // Load images from memory
        m_LogoBlack = AIAC::Image(AIAC_LOGO_BLACK);
        m_LogoLightGray = AIAC::Image(AIAC_LOGO_LIGHT_GRAY);

        // Set panes UI for layers
        //                 Label       Collapse             PaneContent
        StackPane(PaneUI("Camera",       true,      AIAC_BIND_EVENT_FN(SetPaneUICamera)    ));
        StackPane(PaneUI("Slam",         true,      AIAC_BIND_EVENT_FN(SetPaneUISlam)      ));

        // TODO: add config for file dialog widget
        //TODO: add vertical menu bar

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

        ShowMenuBar();

        ShowMainUI();

        ShowSceneViewport();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void LayerUI::OnDetach()
    {
        ImGui::EndMainMenuBar();

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void LayerUI::ShowMenuBar()
    {
        // set menu bar as transparent

        if (ImGui::BeginMainMenuBar())
        {
            ImGui::Image(m_LogoBlack.GetImTexture().ID, ImVec2(18, 18), ImVec2(0, 1), ImVec2(1, 0));
            ImGui::SameLine();

            if (ImGui::BeginMenu("App"))
            {
                if (ImGui::MenuItem("Close"))
                {
                    *m_IsOpen = false;
                    AIAC_APP.Close();
                }
            }
            ImGui::EndMenu();
        }
    }

    void LayerUI::ShowMainUI()
    {
        ImGui::Begin("augmented_carpentry", m_IsOpen);
        ImGui::Image(m_LogoLightGray.GetImTexture().ID, ImVec2(60, 60), ImVec2(0, 1), ImVec2(1, 0));
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
        ImGui::Image(m_LogoLightGray.GetImTexture().ID, viewportSize, ImVec2(0, 1), ImVec2(1, 0), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
        
        ImGui::EndChild();
        
        ImGui::End();
    }


    void LayerUI::SetPaneUICamera()
    {
        ImGui::Text("This layer is responsible for the physical camera.");
        AIAC::Camera& camera = AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera;
        ImGui::Text("Camera is %s", camera.IsOpened() ? "open" : "closed");
        ImGui::Text("Camera resolution: %d x %d", camera.GetWidth(), camera.GetHeight());

        Image frame = AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetCurrentFrame();
        AIAC::ImTexture frameImTexture = frame.GetImTexture();
        ImGui::Image(frameImTexture.ID, ImVec2(frame.GetImTexture().Size.x * 0.5f, frame.GetImTexture().Size.y * 0.5f));
    }

    void LayerUI::SetPaneUISlam()
    {
        ImGui::Text("Import files:");
        ImGui::BeginChild("slam_info_child", ImVec2(0, 50), true, ImGuiWindowFlags_HorizontalScrollbar);
        ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_LIGHT_GREY);
        if (ImGui::Button("Open SLAM map"))
            ImGuiFileDialog::Instance()->OpenDialog("ChooseSLAMmap", "Open SLAM map", ".map", ".");

        if (ImGuiFileDialog::Instance()->Display("ChooseSLAMmap")) 
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
            std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
            // action
            /* write here what to do with the file path */
            // TODO: Raise event to restart SLAM
            }
            ImGuiFileDialog::Instance()->Close();
        }
        ImGui::SameLine();
        if (ImGui::Button("Open Vocab"))
            ImGuiFileDialog::Instance()->OpenDialog("ChooseVocab", "Open Vocab", ".fbow", ".");

        if (ImGuiFileDialog::Instance()->Display("ChooseVocab")) 
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
            std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
            // action
            /* write here what to do with the file path */
            // TODO: Raise event for SLAM to restart
            }
            ImGuiFileDialog::Instance()->Close();
        }
        ImGui::SameLine();
        if (ImGui::Button("Open camera calib"))
            ImGuiFileDialog::Instance()->OpenDialog("ChooseCameraCalib", "Open calib", ".yml", ".");

        if (ImGuiFileDialog::Instance()->Display("ChooseCameraCalib")) 
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
            std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
            // action
            /* write here what to do with the file path */
            // TODO: Raise event for SLAM to restart
            }
            ImGuiFileDialog::Instance()->Close();
        }
        // FIXME: 3Dmodel import is this decoupled from SLAM layer?
        // ImGui::SameLine();
        // if (ImGui::Button("Open 3dModel"))
        //     ImGuiFileDialog::Instance()->OpenDialog("Choose3dModel", "Open 3dModel", ".ply", ".");

        // if (ImGuiFileDialog::Instance()->Display("Choose3dModel")) 
        // {
        //     if (ImGuiFileDialog::Instance()->IsOk())
        //     {
        //     std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
        //     std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
        //     // action
        //     /* write here what to do with the file path */
        //     // TODO: Raise event for SLAM to restart
        //     }
        //     ImGuiFileDialog::Instance()->Close();
        // }
        ImGui::PopStyleColor();
        ImGui::EndChild();

        ImGui::Text("Tracked: %s", AIAC_APP.GetLayer<AIAC::LayerSlam>()->IsTracked() ? "Yes" : "No");

        std::string camPoseStr; camPoseStr << AIAC_APP.GetLayer<AIAC::LayerSlam>()->GetCamPoseCv();
        ImGui::Text("Estimated Camera Pose: \n%s", camPoseStr.c_str());
    }



}