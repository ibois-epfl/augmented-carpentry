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
    bool m_IsSavingMap = false, m_IsSwitchedToMappging = false;

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


        // Load images from memory
        m_LogoBlack = AIAC::Image(AIAC_LOGO_BLACK);
        m_LogoLightGray = AIAC::Image(AIAC_LOGO_LIGHT_GRAY);

        // Set panes UI for layers
        //                 Label       Collapse             PaneContent
        StackPane(PaneUI("Camera",       true,      AIAC_BIND_EVENT_FN(SetPaneUICamera)    ));
        StackPane(PaneUI("Slam",         true,      AIAC_BIND_EVENT_FN(SetPaneUISlam)      ));
        StackPane(PaneUI("Render",       true,      AIAC_BIND_EVENT_FN(SetPaneUIRender)    ));

        // TODO: add config for file dialog widget
        // TODO: add vertical menu bar

        m_IsOpen = new bool(true);

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

        if(AIAC_APP.GetLayer<LayerSlam>()->IsMapping()){
            ShowMappingPopup();
            if(m_IsSavingMap){
                ShowSaveMapFileDialog();
            }
            if(m_IsSwitchedToMappging){
                m_IsSwitchedToMappging = false;
            }
        } else {
            ShowMenuBar();
            ShowMainUI();
            ShowSceneViewport();
        }




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
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
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
        ImGui::Begin("Scene Viewport", m_IsOpen);

        ImVec2 viewportSize = ImGui::GetContentRegionAvail();
        viewportSize.y -= (ImGui::GetTextLineHeight() + 10);
        AIAC_APP.GetRenderer()->SetGlobalViewSize(viewportSize.x, viewportSize.y);

        SetGlobalViewUI(viewportSize);

        ImGui::End();
    }

    void LayerUI::SetGlobalViewUI(ImVec2 viewportSize)
    {
        if(m_IsMouseLDown && ImGui::IsMouseDragging(0, 0.0f)) {
            ImVec2 mousePos = ImGui::GetMousePos();
            switch(m_AdjustTarget){
                case AdjustTarget::SCALE:
                    AIAC_APP.GetRenderer()->UpdateGlobalViewCameraScale(mousePos.x - m_LastMouseLPos.x - mousePos.y + m_LastMouseLPos.y);
                    break;
                case AdjustTarget::ROTATION:
                    AIAC_APP.GetRenderer()->UpdateGlobalViewCameraRotation(mousePos.x - m_LastMouseLPos.x, mousePos.y - m_LastMouseLPos.y);
                    break;
                case AdjustTarget::TRANSLATION:
                    AIAC_APP.GetRenderer()->UpdateGlobalViewCameraTranslation(mousePos.x - m_LastMouseLPos.x, mousePos.y - m_LastMouseLPos.y);
                    break;
            }
            m_LastMouseLPos = mousePos;
        }
        if(m_IsMouseRDown && ImGui::IsMouseDragging(1, 0.0f)) {
            ImVec2 mousePos = ImGui::GetMousePos();
            AIAC_APP.GetRenderer()->UpdateGlobalViewCameraTranslation(mousePos.x - m_LastMouseRPos.x, mousePos.y - m_LastMouseRPos.y);
            m_LastMouseRPos = mousePos;
        }

        CvtGlTextureObj2ImTexture(AIAC_APP.GetRenderer()->GetGlobalView(), m_SceneViewportImTexture);
        ImGui::ImageButton(m_SceneViewportImTexture.ID, viewportSize, ImVec2(0, 1), ImVec2(1, 0), 0, ImColor(255, 255, 255, 128));
        if(ImGui::IsItemHovered()) {
            if(ImGui::IsMouseDown(0) && !m_IsMouseLDown) {
                m_IsMouseLDown = true;
                m_AdjustTarget = AdjustTarget::ROTATION;
                m_LastMouseLPos = ImGui::GetMousePos();
            }
            if(ImGui::IsMouseDown(1) && !m_IsMouseRDown) {
                m_IsMouseRDown = true;
                m_AdjustTarget = AdjustTarget::TRANSLATION;
                m_LastMouseRPos = ImGui::GetMousePos();
            }
        }
        if(ImGui::IsMouseReleased(0)) { m_IsMouseLDown = false; }
        if(ImGui::IsMouseReleased(1)) { m_IsMouseRDown = false; }

        ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_LIGHT_GREY);
        ImGui::Button("Scale");
        if(ImGui::IsItemHovered() && ImGui::IsMouseDown(0) && !m_IsMouseLDown) {
            m_AdjustTarget = AdjustTarget::SCALE;
            m_IsMouseLDown = true;
            m_LastMouseLPos = ImGui::GetMousePos();
        }
        ImGui::SameLine();
        ImGui::Button("Move");
        if(ImGui::IsItemHovered() && ImGui::IsMouseDown(0) && !m_IsMouseLDown) {
            m_AdjustTarget = AdjustTarget::TRANSLATION;
            m_IsMouseLDown = true;
            m_LastMouseLPos = ImGui::GetMousePos();
        }
        ImGui::PopStyleColor();
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
        ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_LIGHT_GREY);
        ImGui::Text("Import files:");
        ImGui::BeginChild("slam_info_child", ImVec2(0, 56), true, ImGuiWindowFlags_HorizontalScrollbar);
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

        ImGui::EndChild();

        ImGui::Text("Mapping Functions:");
        ImGui::BeginChild("mapping_function_child", ImVec2(0, 36), true, ImGuiWindowFlags_HorizontalScrollbar);
            if(ImGui::Button("Start Mapping")){
                AIAC_APP.GetLayer<AIAC::LayerSlam>()->StartMapping();
                AIAC_APP.GetRenderer()->StartMapping();
                m_IsSwitchedToMappging = true;
            }
            ImGui::SameLine();
            if(ImGui::Button("Combine Map")){

            }
        ImGui::EndChild();


        ImGui::Text("Tracked: %s", AIAC_APP.GetLayer<AIAC::LayerSlam>()->IsTracked() ? "Yes" : "No");

        std::string camPoseStr; camPoseStr << AIAC_APP.GetLayer<AIAC::LayerSlam>()->GetCamPoseCv();
        ImGui::Text("Estimated Camera Pose: \n%s", camPoseStr.c_str());

        ImGui::PopStyleColor();
    }

    void LayerUI::SetPaneUIRender()
    {
        ImGui::Checkbox("Point Cloud Map", &AIAC_APP.GetRenderer()->ShowPointCloudMap);
        ImGui::Checkbox("Digital Model", &AIAC_APP.GetRenderer()->ShowDigitalModel);
    }

    void LayerUI::ShowMappingPopup()
    {
        ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y));
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::Begin("Mapping", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

            CvtGlTextureObj2ImTexture(AIAC_APP.GetRenderer()->GetMappingView(), m_MappingViewImTexture);
            ImGui::ImageButton(m_MappingViewImTexture.ID, ImVec2(600, 442), ImVec2(0, 1), ImVec2(1, 0), 0, ImColor(255, 255, 255, 128));

            ImGui::SameLine();
            ImGui::BeginChild("mapping_info_child", ImVec2(0, 0), false);
                ImVec2 sideBarViewportSize = ImGui::GetContentRegionAvail();
                ImGui::BeginChild("global_view", ImVec2(sideBarViewportSize.x, sideBarViewportSize.x * 3 / 4 + 20), true);
                    ImVec2 viewportSize = ImGui::GetContentRegionAvail();
                    viewportSize = ImVec2(viewportSize.x, viewportSize.y - 24);
                    AIAC_APP.GetRenderer()->SetGlobalViewSize(viewportSize.x, viewportSize.y);
                    SetGlobalViewUI(viewportSize);
                ImGui::EndChild();

                sideBarViewportSize = ImGui::GetContentRegionAvail();
                ImGui::BeginChild("mapping_menu", sideBarViewportSize, true);
                    ImGui::Text("Map Points: %u", AIAC_APP.GetLayer<LayerSlam>()->Slam.getMap()->map_points.size());
                    ImGui::Text("Map Markers: %lu", AIAC_APP.GetLayer<LayerSlam>()->Slam.getMap()->map_markers.size());
                    if(ImGui::Button("Save")){
                        m_IsSavingMap = true;
                    }
                    ImGui::SameLine();
                    if(ImGui::Button("Cancel")){
                        AIAC_APP.GetLayer<AIAC::LayerSlam>()->StopMapping();
                        AIAC_APP.GetRenderer()->StopMapping();
                        m_IsSavingMap = false;
                    }
                ImGui::EndChild();
            ImGui::EndChild();

            if (ImGui::BeginPopupContextWindow())
            {
                if (ImGui::Selectable("Clear"))
                {
                }
                ImGui::EndPopup();
            }
        ImGui::End();
    }
    void LayerUI::ShowSaveMapFileDialog()
    {
        ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x * 0.8, ImGui::GetIO().DisplaySize.y * 0.75));
        ImGuiFileDialog::Instance()->OpenDialog("ChooseSaveMapPath", "Choose Save Map Path", ".map", ".");
        if (ImGuiFileDialog::Instance()->Display("ChooseSaveMapPath"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();

                AIAC_INFO("Saving map to {0}", filePathName.c_str());
                AIAC_APP.GetLayer<AIAC::LayerSlam>()->Slam.getMap()->saveToFile(filePathName);

            }
            ImGuiFileDialog::Instance()->Close();
            m_IsSavingMap = false;
        }
    }


}