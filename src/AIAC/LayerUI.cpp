// #####################################################################
// >>>>>>>>>>>>>>>>>>>>> BEGINNING OF LEGAL NOTICE >>>>>>>>>>>>>>>>>>>>>
//######################################################################
//
// This source file, along with its associated content, was authored by
// Andrea Settimi, Hong-Bin Yang, Naravich Chutisilp, and numerous other
// contributors. The code was originally developed at the Laboratory for
// Timber Construction (IBOIS, director: Prof. Yves Weinand) at the School of 
// Architecture, Civil and Environmental Engineering (ENAC) at the Swiss
// Federal Institute of Technology in Lausanne (EPFL) for the Doctoral
// Research "Augmented Carpentry" (PhD researcher: Andrea Settimi,
// co-director: Dr. Julien Gamerro, director: Prof. Yves Weinand).
//
// Although the entire repository is distributed under the GPL license,
// these particular source files may also be used under the terms of the
// MIT license. By accessing or using this file, you agree to the following:
//
// 1. You may reproduce, modify, and distribute this file in accordance
//    with the terms of the MIT license.
// 2. You must retain this legal notice in all copies or substantial
//    portions of this file.
// 3. This file is provided "AS IS," without any express or implied
//    warranties, including but not limited to the implied warranties of
//    merchantability and fitness for a particular purpose.
//
// If you cannot or will not comply with the above conditions, you are
// not permitted to use this file. By proceeding, you acknowledge and
// accept all terms and conditions herein.
//
//######################################################################
// <<<<<<<<<<<<<<<<<<<<<<< END OF LEGAL NOTICE <<<<<<<<<<<<<<<<<<<<<<<<
// #####################################################################
//
#include "aiacpch.h"

#include "AIAC/LayerUI.h"
#include "AIAC/Application.h"

#include "AIAC/Image.h"
#include "AIAC/Render/Renderer.h"

#include "AIAC/UI/ImGuiFileDialog.h"

#include "AIAC/UI/ClrPalette.h"
#include "AIAC/UI/CustomLogos.h"
#include "LayerCameraCalib.h"
#include "LayerLogRecorder.h"

#include "ttool.hh"

#include "utils/utils.h"
#include "LayerUtils.h"

#include <filesystem>
#include <optional>
#include <string>

std::optional<std::string> GetLatestFilePath(const std::string& directoryPath, const std::string& extension);
std::optional<std::string> GetLatestFilePath(const std::string& directoryPath, const std::string& extension) {
    std::optional<std::filesystem::path> latestFilePath;
    std::filesystem::file_time_type latestModificationTime;

    for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
        if (entry.is_regular_file() && entry.path().extension() == extension) {
            auto currentFileModificationTime = std::filesystem::last_write_time(entry);
            if (!latestFilePath || currentFileModificationTime > latestModificationTime) {
                latestFilePath = entry.path();
                latestModificationTime = currentFileModificationTime;
            }
        }
    }

    if (latestFilePath) {
        return latestFilePath->string();
    } else {
        return std::nullopt;
    }
}


namespace AIAC
{
    void LayerUI::OnAttach()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        //---------------------------------------------------------------------------------
        // styling of the main window
        ImGui::StyleColorsDark();
        ImGuiStyle& style = ImGui::GetStyle();

        style.Colors[ImGuiCol_MenuBarBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.20f);
        style.Colors[ImGuiCol_WindowBg]              = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);
        style.Colors[ImGuiCol_Border]                = AIAC_UI_DARK_GREY;
        style.Colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

        style.Colors[ImGuiCol_FrameBg]               = AIAC_UI_LIGHT_GREY;
        style.Colors[ImGuiCol_FrameBgHovered]        = AIAC_UI_DARK_GREY;
        style.Colors[ImGuiCol_FrameBgActive]         = AIAC_UI_SPARK_ORANGE;

        style.Colors[ImGuiCol_CheckMark]             = AIAC_UI_SPARK_ORANGE;
        style.Colors[ImGuiCol_SliderGrab]            = AIAC_UI_SPARK_ORANGE;
        style.Colors[ImGuiCol_SliderGrabActive]      = AIAC_UI_SPARK_ORANGE;
        
        style.Colors[ImGuiCol_ResizeGrip]            = AIAC_UI_DARK_GREY;
        style.Colors[ImGuiCol_ResizeGripHovered]     = AIAC_UI_LIGHT_GREY;
        style.Colors[ImGuiCol_ResizeGripActive]      = AIAC_UI_SPARK_ORANGE;
        
        style.Colors[ImGuiCol_PlotHistogramHovered]  = AIAC_UI_DARK_GREY;
        style.Colors[ImGuiCol_TextSelectedBg]        = AIAC_UI_SPARK_ORANGE;
        
        style.Colors[ImGuiCol_TitleBg]               = AIAC_UI_DARK_GREY;
        style.Colors[ImGuiCol_TitleBgCollapsed]      = AIAC_UI_DARK_GREY;
        style.Colors[ImGuiCol_TitleBgActive]         = AIAC_UI_SPARK_ORANGE;

        style.Colors[ImGuiCol_Header]                = AIAC_UI_DARK_GREY;
        style.Colors[ImGuiCol_HeaderHovered]         = AIAC_UI_SPARK_ORANGE;
        style.Colors[ImGuiCol_HeaderActive]          = AIAC_UI_SPARK_ORANGE;

        style.Colors[ImGuiCol_Button]                = AIAC_UI_DARK_GREY;
        style.Colors[ImGuiCol_ButtonHovered]         = AIAC_UI_SPARK_ORANGE;
        style.Colors[ImGuiCol_ButtonActive]          = AIAC_UI_SPARK_ORANGE;
        style.Colors[ImGuiCol_FrameBg]               = AIAC_UI_DARK_GREY;

        style.Colors[ImGuiCol_ScrollbarBg]           = AIAC_UI_LIGHT_GREY;
        style.Colors[ImGuiCol_ScrollbarGrab]         = AIAC_UI_DARK_GREY;
        style.Colors[ImGuiCol_ScrollbarGrabHovered]  = AIAC_UI_SPARK_ORANGE;
        style.Colors[ImGuiCol_ScrollbarGrabActive]   = AIAC_UI_SPARK_ORANGE;

        style.ScrollbarSize = 30.0f;
        style.WindowRounding = 4.0f;
        style.ChildRounding = 4.0f;
        style.FrameRounding = 4.0f;
        style.PopupRounding = 4.0f;
        style.ScrollbarRounding = 4.0f;
        style.GrabRounding = 4.0f;
        style.TabRounding = 4.0f;
        style.FramePadding = ImVec2(6, 6);

        //---------------------------------------------------------------------------------

        ImGui_ImplGlfw_InitForOpenGL(AIAC_APP.GetWindow()->GetGLFWWindow(), true);
        ImGui_ImplOpenGL3_Init(AIAC_APP.GetWindow()->GetGlslVersion());

        io.Fonts->AddFontFromFileTTF("assets/fonts/UbuntuMono-R.ttf", 14.0f);  // default

        // Load images from memory
        m_LogoLightClr = AIAC::Image(AIAC_LOGO_COLOR);

        // Set panes UI for layers
        //                Label                    Collapse  PaneContent
        StackPane(PaneUI("Camera",                 false,    AIAC_BIND_EVENT_FN(SetPaneUICamera)    ));
        StackPane(PaneUI("Mapping",                false,    AIAC_BIND_EVENT_FN(SetPaneUISlam)      ));
        StackPane(PaneUI("ACIM (Execution model)", false,    AIAC_BIND_EVENT_FN(SetPaneUIACIM)      ));
        StackPane(PaneUI("Toolhead",               false,    AIAC_BIND_EVENT_FN(SetPaneUIToolhead), AIAC_BIND_EVENT_FN(OnCollapsingPaneUIToolhead)));
        StackPane(PaneUI("Utils",                  false,    AIAC_BIND_EVENT_FN(SetPaneUIUtils)     ));

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

        if (AIAC_APP.GetLayer<LayerSlam>()->IsMapping()) {
            ShowMappingPopup();
        } else if (AIAC_APP.GetLayer<LayerCameraCalib>()->IsCalibrating()){
            ShowCamCalibPopup();
            if (m_IsChoosingCamCalibFileSavePath){
                ShowSaveCamCalibFileDialog();
            }
        } else {
            ShowMenuBar();
            ShowMainUI();
            ShowSceneViewport();
            ShowLogRecorderUI();

            if(m_IsCombiningMap){
                ShowCombineMapPopup();
            }

            if(m_IsReconstructing3D){
                ShowReconstruct3DPopup();
            }
        }
        ShowFileSelectDialog();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void LayerUI::OnDetach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    template<typename... Args>
    void PaneUI::Show(Args &&... args) {
        bool isOpened = ImGui::CollapsingHeader(m_Label, m_IsCollapsed ? ImGuiTreeNodeFlags_DefaultOpen : 0);
        if (isOpened) {
            // if this one is not opened yet, close the previously opened one
            if (m_CollapseState != CollapseState::OPEN) {
                auto lastOpenedPaneUI = AIAC_APP.GetLayer<LayerUI>()->GetOpenedPaneUI();
                if (lastOpenedPaneUI != nullptr && lastOpenedPaneUI->m_Label != m_Label) {
                    ImGui::GetStateStorage()->SetInt(ImGui::GetID(lastOpenedPaneUI->m_Label), 0);
                    lastOpenedPaneUI->Show();
                }
                AIAC_APP.GetLayer<LayerUI>()->SetOpenedPaneUI(this);
            }
            m_CollapseState = CollapseState::OPEN;
            m_func(std::forward<Args>(args)...);
        }

        // check if it's just collapsed
        if (!isOpened) {
            if (m_CollapseState == CollapseState::OPEN) {
                m_CollapseState = CollapseState::ON_COLLAPSING;
            }
        }
    }

    template<typename... Args>
    void PaneUI::CheckOnCollapsing(Args &&... args) {
        if (m_CollapseState == CollapseState::ON_COLLAPSING) {
            m_onCollapseCallback(std::forward<Args>(args)...);
            m_CollapseState = CollapseState::COLLAPSE;
        }
    }

    void LayerUI::ShowMenuBar()
    {
        if (ImGui::BeginMainMenuBar())
        {
            ImGui::Image(m_LogoLightClr.GetImTexture().ID, ImVec2(18, 18), ImVec2(0, 1), ImVec2(1, 0));
            ImGui::SameLine();

            if (ImGui::BeginMenu("App"))
            {
                if (ImGui::MenuItem("Close"))
                {
                    *m_IsOpen = false;
                    AIAC_EBUS->EnqueueEvent(std::make_shared<AppCloseEvent>());
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

    void LayerUI::ShowMainUI()
    {
        ImGui::Begin("augmented_carpentry", m_IsOpen);
#ifdef ENABLE_DEV_UI
        ImGui::Image(m_LogoLightClr.GetImTexture().ID, ImVec2(60, 60), ImVec2(0, 1), ImVec2(1, 0));
        ImGui::SameLine();
        ImGui::Text("This is a prototype for augmented_carpentry \n Version 01.00.00 \n Build 2021-01-01 00:00:00 \n IBOIS, EPFL");
#endif

        for (auto& pane : m_PaneUIStack) {
            pane.Show();
            pane.CheckOnCollapsing();
        }

        ImGui::End();
    }

    void LayerUI::ShowSceneViewport()
    {
        ImGui::Begin("Scene Viewport", m_IsOpen);

        ImVec2 viewportSize = ImGui::GetContentRegionAvail();
        viewportSize.y -= (ImGui::GetTextLineHeight() + 16);
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

        CvtGlTextureObj2ImTexture(AIAC_APP.GetRenderer()->GetGlobalView(), m_SceneViewportImTexture, viewportSize);

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
        ImGui::SameLine();
        if(ImGui::Button("NW")){
            AIAC_APP.GetRenderer()->SetGlobalViewToActivatedComponent(Renderer::StandardView::NW);
        }
        ImGui::SameLine();
        if(ImGui::Button("NE")){
            AIAC_APP.GetRenderer()->SetGlobalViewToActivatedComponent(Renderer::StandardView::NE);
        }
        ImGui::SameLine();
        if(ImGui::Button("SW")){
            AIAC_APP.GetRenderer()->SetGlobalViewToActivatedComponent(Renderer::StandardView::SW);
        }
        ImGui::SameLine();
        if(ImGui::Button("SE")){
            AIAC_APP.GetRenderer()->SetGlobalViewToActivatedComponent(Renderer::StandardView::SE);
        }
        ImGui::PopStyleColor();
    }


    void LayerUI::SetPaneUICamera()
    {
        string currentItem = AIAC_APP.GetLayer<LayerCamera>()->GetCurrentDevice();
        static const char* previewValue = currentItem.c_str();
        if(ImGui::BeginCombo("##AvailableDevices", previewValue)){
            for (auto& devicePath : AIAC_APP.GetLayer<LayerCamera>()->AvailableDevices) {
                bool isSelected = (currentItem == devicePath);
                if (ImGui::Selectable(devicePath.c_str(), isSelected)){
                    AIAC_APP.GetLayer<LayerCamera>()->SetCurrentDevice(devicePath);
                }
                if (isSelected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
        ImGui::SameLine();
        if(ImGui::Button("Refresh")){
            AIAC_APP.GetLayer<LayerCamera>()->UpdateAvailableDevices();
        }

        ImGui::Text("Flip ");
        ImGui::SameLine();
        if(ImGui::Checkbox("Horizontal", &AIAC_APP.GetLayer<LayerCamera>()->MainCamera.FlipHorizontal)){
            AIAC::Config::UpdateEntry(AIAC::Config::SEC_AIAC, AIAC::Config::CAM_FLIP_HORIZONTAL, AIAC_APP.GetLayer<LayerCamera>()->MainCamera.FlipHorizontal);
        }
        ImGui::SameLine();
        if(ImGui::Checkbox("Vertical", &AIAC_APP.GetLayer<LayerCamera>()->MainCamera.FlipVertical)){
            AIAC::Config::UpdateEntry(AIAC::Config::SEC_AIAC, AIAC::Config::CAM_FLIP_VERTICAL, AIAC_APP.GetLayer<LayerCamera>()->MainCamera.FlipVertical);
        };

        AIAC::Camera& camera = AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera;
        ImGui::Text("Resolution: (%d x %d) > (%d x %d)", camera.GetRawWidth(), camera.GetRawHeight(), camera.GetWidth(), camera.GetHeight());

        ImGui::BeginChild("camera_function_child", ImVec2(0, 50), true, ImGuiWindowFlags_HorizontalScrollbar);
            ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_LIGHT_GREY);
            if(ImGui::Button("Start Calibration")){
                AIAC_APP.GetLayer<LayerCameraCalib>()->StartCalibration();
            }
            ImGui::SameLine();
            if (ImGui::Button("Open Calib File")) {
                ImGuiFileDialog::Instance()->OpenDialog("ChooseCameraCalib", "Open calib", ".yml", ".");
            }
            if (ImGuiFileDialog::Instance()->Display("ChooseCameraCalib"))
            {
                if (ImGuiFileDialog::Instance()->IsOk())
                {
                    std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                    AIAC_EBUS->EnqueueEvent(std::make_shared<CameraCalibrationLoadedEvent>(filePathName));
                }
                ImGuiFileDialog::Instance()->Close();
            }

            ImGui::PopStyleColor();
        ImGui::EndChild();
    }

    void LayerUI::SetPaneUISlam()
    {
        ImVec2 sizeButtons = ImVec2(110, 50);
        ImGui::Text("Import files:");
        ImGui::BeginChild("slam_info_child", ImVec2(0, 95), true, ImGuiWindowFlags_HorizontalScrollbar);
            std::string currentSLAMMap = AIAC::Config::Get<std::string>(AIAC::Config::SEC_TSLAM, AIAC::Config::MAP_FILE, ".");
            size_t lastSlashPos = currentSLAMMap.find_last_of("/\\");
            if (lastSlashPos != std::string::npos) {
                currentSLAMMap = currentSLAMMap.substr(lastSlashPos + 1);
            }
            ImGui::Text("Current SLAM Map: %s", currentSLAMMap.c_str());
            
            ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_BRONZE_ORANGE);
            if (ImGui::Button("Open SLAM map", sizeButtons))
            {
                std::string mapFolderDefault = AIAC::Config::Get<std::string>(AIAC::Config::SEC_TSLAM, AIAC::Config::SAVE_DIR_MAPS, ".");
                ImGuiFileDialog::Instance()->OpenDialog("ChooseSLAMmap", "Open SLAM map", ".map", mapFolderDefault.c_str());
            }
            if (ImGuiFileDialog::Instance()->Display("ChooseSLAMmap"))
            {
                if (ImGuiFileDialog::Instance()->IsOk())
                {
                    std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                    AIAC_EBUS->EnqueueEvent(std::make_shared<SLAMMapLoadedEvent>(filePathName));
                }
                ImGuiFileDialog::Instance()->Close();
            }
            ImGui::SameLine();
            ImGui::PopStyleColor();

            ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_GRAPE_PURPLE);
            if (ImGui::Button("Open Vocab", sizeButtons))
                ImGuiFileDialog::Instance()->OpenDialog("ChooseVocab", "Open Vocab", ".fbow", ".");

            if (ImGuiFileDialog::Instance()->Display("ChooseVocab"))
            {
                if (ImGuiFileDialog::Instance()->IsOk())
                {
                std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                AIAC_EBUS->EnqueueEvent(std::make_shared<SLAMVocabularyLoadedEvent>(filePathName));
                }
                ImGuiFileDialog::Instance()->Close();
            }
            ImGui::PopStyleColor();

            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_PLUM_PURPLE);
            if (ImGui::Button("Open latest Map", sizeButtons))
            {
                std::string mapFolderDefault = AIAC::Config::Get<std::string>(AIAC::Config::SEC_TSLAM, AIAC::Config::SAVE_DIR_MAPS, ".");
                auto latestMapFilePathOpt = GetLatestFilePath(mapFolderDefault, ".map");

                if (latestMapFilePathOpt.has_value())
                {
                    std::string latestMapFilePath = latestMapFilePathOpt.value();
                    AIAC_EBUS->EnqueueEvent(std::make_shared<SLAMMapLoadedEvent>(latestMapFilePath));
                } else {
                    AIAC_INFO("No latest map file found in the directory: {0}", mapFolderDefault);
                }
            }
            ImGui::PopStyleColor();

        ImGui::EndChild();

        ImGui::Text("Mapping Functions:");
        ImGui::BeginChild("mapping_function_child", ImVec2(0, 80), true, ImGuiWindowFlags_HorizontalScrollbar);
            ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_BRONZE_ORANGE);
            if(ImGui::Button("Start Mapping", sizeButtons)){
                std::string defaultPath = "";
                defaultPath += "./scanned_map/map-";
                defaultPath += GetCurrentDateTime();
                defaultPath += ".map";
                strncpy(m_MappingParams.MapSavingPath, defaultPath.c_str(), defaultPath.size());
                AIAC_EBUS->EnqueueEvent(std::make_shared<SLAMStartMappingEvent>());
            }
            ImGui::SameLine();
            ImGui::PopStyleColor();

            ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_PRUSSIAN_BLUE);
            if(ImGui::Button("Combine Map", sizeButtons)){
                m_IsCombiningMap = true;
            }
            ImGui::SameLine();
            if(ImGui::Button("Reconstruct 3D", sizeButtons)){
                m_IsReconstructing3D = true;
            }
            ImGui::PopStyleColor();
        ImGui::EndChild();

#ifdef ENABLE_DEV_UI
        ImGui::Checkbox("Show Tag", &AIAC_APP.GetLayer<AIAC::LayerSlam>()->ToShowTag);
        ImGui::Checkbox("Process Frames", &AIAC_APP.GetLayer<AIAC::LayerSlam>()->ToProcess);
        ImGui::Checkbox("Enhance Photo", &AIAC_APP.GetLayer<AIAC::LayerSlam>()->ToEnhance);

        ImGui::Text("Tracked: %s", AIAC_APP.GetLayer<AIAC::LayerSlam>()->IsTracked() ? "Yes" : "No");
#endif

#ifdef ENABLE_DEV_UI
        std::string camPoseStr; camPoseStr << AIAC_APP.GetLayer<AIAC::LayerSlam>()->GetCamPoseCv();
        ImGui::Text("Estimated Camera Pose: \n%s", camPoseStr.c_str());
#endif
    }

    void LayerUI::SetPaneUIACIM()
    {
        // ACIM file manager (ACIM Loader, Scanned model re/loader)
        ImGui::Text("ACIM File Manager:");
        ImGui::BeginChild("ACIM File Manager", ImVec2(0, 60), true, ImGuiWindowFlags_HorizontalScrollbar);
            std::string currentACIMFileEntry = "Current ACIM:  " + AIAC_APP.GetLayer<LayerModel>()->GetACInfoModelName();
            ImGui::Text("%s", currentACIMFileEntry.c_str());
            if(ImGui::Button("Load ACIM")){
                OpenFileSelectDialog("Open ACIM file", ".acim", m_TmpPathBuf, [&]{
                    AIAC_APP.GetLayer<AIAC::LayerModel>()->LoadACInfoModel(m_TmpPathBuf);
                });
            }
            ImGui::SameLine();
            if(ImGui::Button("Reload ACIM")){
                AIAC_APP.GetLayer<AIAC::LayerModel>()->ReloadACInfoModel();
            }
            ImGui::SameLine();
            if(ImGui::Button("Load Scanned Model")){
                std::string saveDirMap = AIAC::Config::Get<std::string>(AIAC::Config::SEC_TSLAM, AIAC::Config::SAVE_DIR_MAPS, ".");
                const char* saveDirMapCStr = saveDirMap.c_str();
                this->m_TmpPathBuf[0] = '\0';
                strcpy(this->m_TmpPathBuf, saveDirMapCStr);
                OpenFileSelectDialog("Open Scanned Model", ".ply", this->m_TmpPathBuf, [&]{
                    AIAC_APP.GetLayer<AIAC::LayerModel>()->LoadScannedModel(this->m_TmpPathBuf);
                });
            }
        ImGui::EndChild();
        
        // Re-position the ACIM model
        ImGui::Text("ACIM position:");
        ImGui::BeginChild("adjust_model_alignment", ImVec2(0, 110), true, ImGuiWindowFlags_HorizontalScrollbar);
            float sliderVal = 0.f;
            ImGui::SliderFloat("## Model Offset", &sliderVal, -1.0f, 1.0f, "Model Offset", ImGuiSliderFlags_AlwaysClamp);
                if (sliderVal != 0.f) AIAC_APP.GetLayer<AIAC::LayerModel>()->AddAlignOffset(sliderVal);
                sliderVal = 0.f;
            ImGui::SameLine();
            ImGui::Text("%s", std::to_string(AIAC_APP.GetLayer<AIAC::LayerModel>()->GetAlignOffset()).c_str());
            
            ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_ROYAL_PURPLE);
            if(ImGui::Button("Align Center")){
                AIAC_APP.GetLayer<AIAC::LayerModel>()->ResetAlignOffset();
            }
            ImGui::PopStyleColor();
            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_LOLLIPOP_PURPLE);
            if(ImGui::Button("Align End 1")){
                AIAC_APP.GetLayer<AIAC::LayerModel>()->ForceAlignToEnd(1);
            }
            ImGui::PopStyleColor();
            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_PLUM_PURPLE);
            if(ImGui::Button("Align End 2")){
                AIAC_APP.GetLayer<AIAC::LayerModel>()->ForceAlignToEnd(0);
            }
            ImGui::PopStyleColor();
            
            ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_EGYPTIAN_BLUE);
            if(ImGui::Button("Rotate +")){
                AIAC_APP.GetLayer<AIAC::LayerModel>()->ChangeAlignRotation(1);
            }
            ImGui::PopStyleColor();
            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_EGYPTIAN_BLUE);
            if(ImGui::Button("Rotate -")){
                AIAC_APP.GetLayer<AIAC::LayerModel>()->ChangeAlignRotation(-1);
            }
            ImGui::PopStyleColor();
            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_SAPPHIRE_BLUE);
            if(ImGui::Button("Reset Rotation")){
                AIAC_APP.GetLayer<AIAC::LayerModel>()->ResetAlignRotation();
            }
            ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_CINNAMON_RED);
            ImGui::PopStyleColor();
            ImGui::SameLine();
            if(ImGui::Button("Flip")){
                AIAC_APP.GetLayer<AIAC::LayerModel>()->FlipAlign();
            }
            ImGui::PopStyleColor();
        ImGui::EndChild();

        // current component to execute
        std::string isCurrentDone = AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().GetCurrentComponent()->IsMarkedDone ? "Done" : "Not done";
        if (AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().GetCurrentComponent()->IsMarkedDone)
            ImGui::PushStyleColor(ImGuiCol_Text, AIAC_UI_GREEN);
        else
            ImGui::PushStyleColor(ImGuiCol_Text, AIAC_UI_RED);
        ImGui::Text("Current Execution: %s", isCurrentDone.c_str());
        ImGui::PopStyleColor();
        ImGui::BeginChild("components_control_panel", ImVec2(0, 216), true, ImGuiWindowFlags_HorizontalScrollbar);
            // print the progress
            ImGui::Text("Progress: %d / %d ( %.2f%% )", AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().GetFabricatedComponents(),
                                                        AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().GetTotalComponents(),
                                                        AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().GetFabricationProgress());

            // control the component to fabricate
            string currentCompoID = AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().GetCurrentComponentID();
            static const char* previewValue = currentCompoID.c_str();
            ImGui::SetNextItemWidth(300);
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(7, 7));
            if(ImGui::BeginCombo("##ACIMComponents", previewValue))
            {
                for (auto& componentID : AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().GetAllComponentsIDs()) {
                    bool isSelected = (currentCompoID == componentID);
                    if (AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().GetComponent(componentID)->IsMarkedDone)
                        ImGui::PushStyleColor(ImGuiCol_Text, AIAC_UI_GREEN);
                    else
                        ImGui::PushStyleColor(ImGuiCol_Text, AIAC_UI_RED);
                    if (ImGui::Selectable(componentID.c_str(), isSelected)){
                        AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().SetCurrentComponentTo(componentID.c_str());
                        AIAC_APP.GetLayer<LayerFeedback>()->ActivateCurrentFeedbackVisibility();
                    }
                    if (isSelected)
                        ImGui::SetItemDefaultFocus();
                    ImGui::PopStyleColor();
                }
                ImGui::EndCombo();
            }

            // go to next or previous component (<,>)
            float halfWidth = ImGui::GetWindowWidth() / 2;
            if(ImGui::Button("<", ImVec2(halfWidth-30, 0)))
            {
                AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().SetPrevComponentAsCurrent();
                AIAC_APP.GetLayer<LayerFeedback>()->ActivateCurrentFeedbackVisibility();
            }
            ImGui::SameLine();
            if (ImGui::Button(">", ImVec2(halfWidth-30, 0)))
            {
                AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().SetNextComponentAsCurrent();
                AIAC_APP.GetLayer<LayerFeedback>()->ActivateCurrentFeedbackVisibility();
            }

            // swap ends for holes only
            auto currentComp = AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().GetCurrentComponent();
            if (auto hole = dynamic_cast<TimberInfo::Hole*>(currentComp)){
                if(ImGui::Button("Swap S/E")) hole->SwapStartEnd();
                ImGui::SameLine();
                ImGui::Text("Diameter: %.f mm", hole->GetRadius()*2000);
            }
            ImGui::PopStyleVar();

            // this is a button for enable the plane visualizer
            // for cutting tools show the red plane for cutting guidance
            if (auto cut = dynamic_cast<TimberInfo::Cut*>(currentComp)){
                if(ImGui::Checkbox("Show Cut Plane", &AIAC_APP.GetLayer<AIAC::LayerFeedback>()->ToShowCutPlane)){
                    if(AIAC_APP.GetLayer<AIAC::LayerFeedback>()->ToShowCutPlane){
                        AIAC_APP.GetLayer<AIAC::LayerFeedback>()->EnableCutPlane(true);
                    } else {
                        AIAC_APP.GetLayer<AIAC::LayerFeedback>()->EnableCutPlane(false);
                    }
                };
            }
            ImGui::SameLine();
            if(ImGui::Checkbox("Show Cotas", &AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().IsShowingCotas)){
                if(AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().IsShowingCotas){
                    AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().UpdateCotasVisibility(true);
                } else {
                    AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().UpdateCotasVisibility(false);
                }
            }

            if (auto feedback = dynamic_cast<CutCircularSawFeedback*>(AIAC_APP.GetLayer<LayerFeedback>()->GetCurrentFabFeedback())){
                ImGui::Checkbox("Manually Select Face", &feedback->IsRefFacesSelectedManually);
                if (feedback->IsRefFacesSelectedManually) {
                    if(ImGui::Button("<##FaceSelect", ImVec2(halfWidth-30, 0)))
                    {
                        feedback->ManuallyScrollRefFace(-1);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button(">##FaceSelect", ImVec2(halfWidth-30, 0)))
                    {
                        feedback->ManuallyScrollRefFace(1);
                    }
                }
            }

            if (auto feedback = dynamic_cast<CutChainSawFeedback*>(AIAC_APP.GetLayer<LayerFeedback>()->GetCurrentFabFeedback())){
                ImGui::Checkbox("Manually Select Face", &feedback->IsRefFacesSelectedManually);
                if (feedback->IsRefFacesSelectedManually) {
                    if(ImGui::Button("<##FaceSelect", ImVec2(halfWidth-30, 0)))
                    {
                        feedback->ManuallyScrollRefFace(-1);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button(">##FaceSelect", ImVec2(halfWidth-30, 0)))
                    {
                        feedback->ManuallyScrollRefFace(1);
                    }
                }
            }


            ImGui::PushStyleColor(ImGuiCol_CheckMark, AIAC_UI_LIGHT_GREEN);
            if(ImGui::Checkbox("Mark as Done", &AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().GetCurrentComponent()->IsMarkedDone));
            ImGui::PopStyleColor();
            ImGui::SameLine();
            if(ImGui::Checkbox("Show All Components", &AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().IsShowingAllComponents)){
                if(AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().IsShowingAllComponents){
                    AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().ShowAllComponents();
                    AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().SetBboxVisibility(true);
                    AIAC_APP.GetLayer<LayerFeedback>()->DeactivateCurrentFeedbackVisibility();
                } else {
                    AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().HideAllComponentsExceptCurrent();
                    AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().SetBboxVisibility(false);
                    AIAC_APP.GetLayer<LayerFeedback>()->ActivateCurrentFeedbackVisibility();
                }
            }
        ImGui::EndChild();

        ImGui::Text("Scaling Factor Adjustment:");
        ImGui::BeginChild("adjust_model_scale_factor", ImVec2(0, 90), true, ImGuiWindowFlags_HorizontalScrollbar);
            ImGui::Text("ACIM BBox Length: %.2f", AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetRealWorldLength() * 1000);
            ImGui::SameLine();
            ImGui::Text("/ Measured Length: %.2f", AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetMeasuredBboxLength() * 1000);
            sliderVal = 0.f;
            ImGui::SliderFloat("## Adjust measured length", &sliderVal, -1e-3f, 1e-3f, "Adjust measured length", ImGuiSliderFlags_AlwaysClamp);
            if (sliderVal != 0.f) AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().AddMeasuredBboxLength(sliderVal);

            if(ImGui::Button("Confirm & Close APP")){
                // restart APP
                AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().AdjustScale();
                *m_IsOpen = false;
                AIAC_EBUS->EnqueueEvent(std::make_shared<AppCloseEvent>());
            }
        ImGui::EndChild();
    }

    void LayerUI::ShowSaveVideoRecorderFileDialog(){
         ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x * 0.8, ImGui::GetIO().DisplaySize.y * 0.75));
         if (ImGui::Button("Select Save Directory")) {
             ImGuiFileDialog::Instance()->OpenDialog("ChooseDirectoryDialog", "Choose Directory", nullptr, ".");
         }

         if (ImGuiFileDialog::Instance()->Display("ChooseDirectoryDialog")) {
             if (ImGuiFileDialog::Instance()->IsOk()) {
                 std::string filePathName  = ImGuiFileDialog::Instance()->GetFilePathName();
                 std::string filePath  = ImGuiFileDialog::Instance()->GetCurrentPath();
                 AIAC_APP.GetLayer<AIAC::LayerUtils>()->SetSaveFolderPath(filePathName);
             }
             ImGuiFileDialog::Instance()->Close();
         }
    }
    void LayerUI::SetPaneUIUtils(){
         ImGui::Text("Set Utils Folder:");
         ImGui::BeginChild("Set Utils Folder", ImVec2(0, 60), true);
             ShowSaveVideoRecorderFileDialog();
             std::string displayedPath = AIAC_APP.GetLayer<AIAC::LayerUtils>()->GetSaveFolderPath();
             ImGui::Text("Selected Path: %s", displayedPath.c_str());
         ImGui::EndChild();

         ImGui::Text("Video Recorder:");
         ImGui::BeginChild("Video Recorder", ImVec2(0, 100), true);
             static bool isRecordingInProgress = false;
             ImGui::Text("Recording: ");
             ImGui::SameLine();
             if(isRecordingInProgress){
                 ImGui::TextColored(AIAC_UI_GREEN, "Yes");
             } else {
                 ImGui::TextColored(AIAC_UI_RED, "No");
             }

             ImGui::Text("Video is being processed: ");
             ImGui::SameLine();
             if(AIAC_APP.GetLayer<LayerUtils>()->IsProcessing()){
                 ImGui::TextColored(AIAC_UI_GREEN, "Yes");
             } else {
                 ImGui::TextColored(AIAC_UI_RED, "No");
             }

             ImGui::Text("Video Recorder Controls: ");
             if (ImGui::Button("Start Recording"))
             {
                 if (!isRecordingInProgress && !AIAC_APP.GetLayer<LayerUtils>()->IsProcessing())
                 {
                     isRecordingInProgress = true;
                     AIAC_APP.GetLayer<LayerUtils>()->StartRecording();
                 }
             }
             ImGui::SameLine();
             if (ImGui::Button("Stop Recording"))
             {
                 if (isRecordingInProgress && !AIAC_APP.GetLayer<LayerUtils>()->IsProcessing())
                 {
                     isRecordingInProgress = false;
                     AIAC_APP.GetLayer<LayerUtils>()->StopRecording();
                 }
             };
         ImGui::EndChild();

         ImGui::Text("Hole Toolhead Axis Exporter:");
         ImGui::BeginChild("Hole Toolhead Axis Exporter", ImVec2(0, 42), true);
             if (ImGui::Button("Export Hole Toolhead Coordinates"))
             {
                 AIAC_APP.GetLayer<LayerUtils>()->ExportHoleToolheadAxis();
             }
         ImGui::EndChild();

         ImGui::Text("Window Photo:");
         ImGui::BeginChild("Window Photo", ImVec2(0, 42), true);
         if (ImGui::Button("Take a window photo"))
         {
             AIAC_APP.GetLayer<LayerUtils>()->SetWindowScreenshot(true);
         }
         ImGui::SameLine();
         if (ImGui::Button("Take a colored buffer photo"))
         {
             AIAC_APP.GetLayer<LayerUtils>()->TakeBufferScreenshot();
         }
         ImGui::EndChild();

    }

    void LayerUI::SetPaneUIToolhead()
    {
        ImGui::Text("Toolhead control:");
        ImGui::BeginChild("toolhead_pose_inputs", ImVec2(0, 470), true, ImGuiWindowFlags_HorizontalScrollbar);
            
            ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.5, 0.5));

            ImVec2 sizeShowToolHeadVisualsButton = ImVec2(-1, 60);
            static bool isButtonVisualsPress = false;
            std::string buttonVisualLabel = isButtonVisualsPress ? "Show Silhouette" : "Hide Silhouette";
            if (!isButtonVisualsPress) 
            {
                ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_HIBISCUS_RED);
                ImGui::PushStyleColor(ImGuiCol_HeaderHovered, AIAC_UI_HIBISCUS_RED);
                AIAC_APP.GetLayer<AIAC::LayerToolhead>()->IsShowSilouhette = true;
            }
            else
            {
                ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_YALE_BLUE);
                ImGui::PushStyleColor(ImGuiCol_HeaderHovered, AIAC_UI_YALE_BLUE);
                AIAC_APP.GetLayer<AIAC::LayerToolhead>()->IsShowSilouhette = false;
            }
            if (ImGui::Button(buttonVisualLabel.c_str(), sizeShowToolHeadVisualsButton))
                isButtonVisualsPress = !isButtonVisualsPress;
            ImGui::PopStyleColor(2);

            ImVec2 sizeSquareButton = ImVec2(70, 70);

            ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_SEA_GREEN);
            ImGui::PushStyleColor(ImGuiCol_HeaderHovered, AIAC_UI_GREEN);
            if(ImGui::Button("save \npose", sizeSquareButton))
                AIAC_APP.GetLayer<AIAC::LayerToolhead>()->TTool->ManipulateModel('y');
            ImGui::SameLine();
            ImGui::PopStyleColor(2);

            static bool isButtonPressed = false;
            std::string buttonLabel = isButtonPressed ? "Stop \nrefine" : "Start \nrefine";
            if (!isButtonPressed) 
            {
                ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_GRAPE_PURPLE);
                ImGui::PushStyleColor(ImGuiCol_HeaderHovered, AIAC_UI_GRAPE_PURPLE);
                AIAC_APP.GetLayer<AIAC::LayerToolhead>()->ToolheadStateUI = -1;
            }
            else
            {
                ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_CARMINE_RED);
                ImGui::PushStyleColor(ImGuiCol_HeaderHovered, AIAC_UI_CARMINE_RED);
                AIAC_APP.GetLayer<AIAC::LayerToolhead>()->ToolheadStateUI = 0;
            }
            if (ImGui::Button(buttonLabel.c_str(), sizeSquareButton))
                isButtonPressed = !isButtonPressed;
            ImGui::SameLine();
            ImGui::PopStyleColor(2);

            ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_LIGHT_GREY);
            ImGui::PushStyleColor(ImGuiCol_HeaderHovered, AIAC_UI_LIGHT_GREY);
            if(ImGui::Button("reset \nlast \npose", sizeSquareButton))
                AIAC_APP.GetLayer<AIAC::LayerToolhead>()->ResetToLastSavedPose();
            ImGui::SameLine();
            ImGui::PopStyleColor(2);

            ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_LIGHT_GREY);
            ImGui::PushStyleColor(ImGuiCol_HeaderHovered, AIAC_UI_LIGHT_GREY);
            if(ImGui::Button("reset \nconfig \npose", sizeSquareButton))
                AIAC_APP.GetLayer<AIAC::LayerToolhead>()->ResetPoseFromConfig();
            ImGui::PopStyleColor(2);

            ImGui::PopStyleVar();
            
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(200, 15));
            ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 100);
            ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 5);
            ImGui::PushItemWidth(-30);
            float sliderF = 0.f;
            ImGui::SliderFloat("Teq", &sliderF, -0.01f, 0.01f, "<backward T forward>", ImGuiSliderFlags_AlwaysClamp);
            if (sliderF != 0.f)
            {
                AIAC_APP.GetLayer<AIAC::LayerToolhead>()->TTool->SetModelManipulationTranslationScale(abs(sliderF));
                if (sliderF > 0.f)
                    AIAC_APP.GetLayer<AIAC::LayerToolhead>()->TTool->ManipulateModel('e');
                else
                    AIAC_APP.GetLayer<AIAC::LayerToolhead>()->TTool->ManipulateModel('q');
            }
            sliderF = 0.f;
            ImGui::SliderFloat("Tda", &sliderF, -0.01f, 0.01f, "<left T right>", ImGuiSliderFlags_AlwaysClamp);
            if (sliderF != 0.f)
            {
                AIAC_APP.GetLayer<AIAC::LayerToolhead>()->TTool->SetModelManipulationTranslationScale(abs(sliderF));
                if (sliderF > 0.f)
                    AIAC_APP.GetLayer<AIAC::LayerToolhead>()->TTool->ManipulateModel('d');
                else
                    AIAC_APP.GetLayer<AIAC::LayerToolhead>()->TTool->ManipulateModel('a');
            }
            sliderF = 0.f;
            ImGui::SliderFloat("Tws", &sliderF, -0.01f, 0.01f, "<down T up>", ImGuiSliderFlags_AlwaysClamp);
            if (sliderF != 0.f)
            {
                AIAC_APP.GetLayer<AIAC::LayerToolhead>()->TTool->SetModelManipulationTranslationScale(abs(sliderF));
                if (sliderF > 0.f)
                    AIAC_APP.GetLayer<AIAC::LayerToolhead>()->TTool->ManipulateModel('w');
                else
                    AIAC_APP.GetLayer<AIAC::LayerToolhead>()->TTool->ManipulateModel('s');
            }
            sliderF = 0.f;
            ImGui::SliderFloat("Rjl", &sliderF, -3.0f, 3.0f, "<left R right>", ImGuiSliderFlags_AlwaysClamp);
            if (sliderF != 0.f)
            {
                AIAC_APP.GetLayer<AIAC::LayerToolhead>()->TTool->SetModelManipulationRotationScale(abs(sliderF));
                if (sliderF > 0.f)
                    AIAC_APP.GetLayer<AIAC::LayerToolhead>()->TTool->ManipulateModel('j');
                else
                    AIAC_APP.GetLayer<AIAC::LayerToolhead>()->TTool->ManipulateModel('l');
            }
            sliderF = 0.f;
            ImGui::SliderFloat("Rik", &sliderF, -3.0f, 3.0f, "<down R up>", ImGuiSliderFlags_AlwaysClamp);
            if (sliderF != 0.f)
            {
                AIAC_APP.GetLayer<AIAC::LayerToolhead>()->TTool->SetModelManipulationRotationScale(abs(sliderF));
                if (sliderF > 0.f)
                    AIAC_APP.GetLayer<AIAC::LayerToolhead>()->TTool->ManipulateModel('i');
                else
                    AIAC_APP.GetLayer<AIAC::LayerToolhead>()->TTool->ManipulateModel('k');
            }
            sliderF = 0.f;
            ImGui::SliderFloat("Ruo", &sliderF, -3.0f, 3.0f, "<backward R forward>", ImGuiSliderFlags_AlwaysClamp);
            if (sliderF != 0.f)
            {
                AIAC_APP.GetLayer<AIAC::LayerToolhead>()->TTool->SetModelManipulationRotationScale(abs(sliderF));
                if (sliderF > 0.f)
                    AIAC_APP.GetLayer<AIAC::LayerToolhead>()->TTool->ManipulateModel('u');
                else
                    AIAC_APP.GetLayer<AIAC::LayerToolhead>()->TTool->ManipulateModel('o');
            }
            ImGui::PopStyleVar(3);
            ImGui::PopItemWidth();
        ImGui::EndChild();

        ImGui::Text("Tools graphics:");
            ImGui::BeginChild("toolhead_graphics", ImVec2(-1, 40));

#ifdef ENABLE_DEV_UI
            if(ImGui::Checkbox("Draw Shaded", &AIAC_APP.GetLayer<AIAC::LayerToolhead>()->IsShowShaded));
            if(ImGui::Checkbox("Draw Toolhead GOData", &AIAC_APP.GetLayer<AIAC::LayerToolhead>()->IsShowToolheadGOInfo))
                AIAC_APP.GetLayer<AIAC::LayerToolhead>()->ACInfoToolheadManager->GetActiveToolhead()->SetVisibility(AIAC_APP.GetLayer<AIAC::LayerToolhead>()->IsShowToolheadGOInfo);
#endif
        ImGui::EndChild();

#ifdef ENABLE_DEV_UI
        ImGui::Text("Toolhead Classifier:");
        ImGui::BeginChild("toolhead_classifier", ImVec2(0, 300), true, ImGuiWindowFlags_HorizontalScrollbar);
            if(ImGui::Button("Detect Toolhead", ImVec2(-1, 40)))
                AIAC_APP.GetLayer<AIAC::LayerToolhead>()->DetectToolhead();
            std::string classifierLog = AIAC_APP.GetLayer<AIAC::LayerToolhead>()->GetClassifierLog();
            ImGui::BeginChild("toolhead_selection_ml", ImVec2(0, 150), true, ImGuiWindowFlags_HorizontalScrollbar);
                std::vector<std::string> toolheadNamesML;
                for (auto& toolhead : AIAC_APP.GetLayer<AIAC::LayerToolhead>()->GetClassifierToolheadList())
                    toolheadNamesML.emplace_back(toolhead);
                for (int i = 0; i < toolheadNamesML.size(); i++)
                {
                    auto toolNameButton = ImGui::Button(toolheadNamesML[i].c_str());
                    if (toolNameButton)
                    {
                        AIAC_APP.GetLayer<AIAC::LayerToolhead>()->SetCurrentObject(toolheadNamesML[i]);
                    }
                }
            ImGui::EndChild();
            ImGui::Text("Classifier Log: \n%s", classifierLog.c_str());
        ImGui::EndChild();
#endif

#ifdef ENABLE_DEV_UI
        std::string poseLogButtonText = "Log TTool Pose";
        bool deferPoseLogUI = false;
        if(AIAC_APP.GetLayer<AIAC::LayerToolhead>()->IsSavePoseLog)
        {
            deferPoseLogUI = true;
            poseLogButtonText = "Stop Log TTool Pose";
            ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_LIGHT_GREEN);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, AIAC_UI_GREEN);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, AIAC_UI_GREEN);
        }
        if (ImGui::Button(poseLogButtonText.c_str(), ImVec2(-1, 40)))
            AIAC_APP.GetLayer<AIAC::LayerToolhead>()->IsSavePoseLog = !AIAC_APP.GetLayer<AIAC::LayerToolhead>()->IsSavePoseLog;
        if (deferPoseLogUI)
        {
            ImGui::PopStyleColor(3);
        }
#endif

        // selection of toolhead
        float windowHeigh = ImGui::GetWindowHeight();
        float availableHeight = ImGui::GetContentRegionAvail().y;
        std::string toolheadNameActive = AIAC_APP.GetLayer<AIAC::LayerToolhead>()->ACInfoToolheadManager->GetActiveToolheadName();
        std::vector<std::string> toolheadNames;
        for (auto& toolhead : AIAC_APP.GetLayer<AIAC::LayerToolhead>()->ACInfoToolheadManager->GetToolheadNames())
            toolheadNames.emplace_back(toolhead);
        int numbButtonPerRow = 4;
        ImVec2 sizeButton = ImVec2(80, 80);
        int totalHeight = toolheadNames.size() / numbButtonPerRow * sizeButton.y;

        ImGui::Text("Active toolhead: %s", toolheadNameActive.c_str());
        ImGui::BeginChild(
            "toolhead_selection",
            ImVec2(0, totalHeight+sizeButton.y+30),
            false,
            ImGuiWindowFlags_NoScrollbar
        );
            for (int i = 0; i < toolheadNames.size(); i++)
            {
                if (i % numbButtonPerRow != 0)
                    ImGui::SameLine();

                std::string label = toolheadNames[i];
                int charPerLine = sizeButton.x / 10;
                for (int j = label.length() - 1; j > 0; j--)
                {
                    if (j % charPerLine == 0)
                    {
                        label.insert(j, "\n");
                    }
                }

                ImVec4 buttonClr = AIAC_UI_DARK_GREY;
                ACToolHeadType toolheadType = AIAC_APP.GetLayer<AIAC::LayerToolhead>()->ACInfoToolheadManager->GetToolheadType(toolheadNames[i]);
                if (toolheadType == ACToolHeadType::DRILLBIT)
                    ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_PURPLE);
                else if (toolheadType == ACToolHeadType::CIRCULARSAW)
                    ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_DARK_GREEN);
                else if (toolheadType == ACToolHeadType::SABERSAW)
                    ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_LIGHT_GREY);
                else if (toolheadType == ACToolHeadType::CHAINSAW)
                    ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_LIGHT_BLUE);
                else if (label == toolheadNameActive)
                    ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_SPARK_ORANGE);
                else
                    ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_DARK_GREY);

                if (ImGui::Button(label.c_str(), sizeButton))
                    AIAC_APP.GetLayer<AIAC::LayerToolhead>()->SetCurrentObject(toolheadNames[i]);

                ImGui::PopStyleColor();
            }
        ImGui::EndChild();
    }

    void LayerUI::OnCollapsingPaneUIToolhead(){
        AIAC_APP.GetLayer<AIAC::LayerToolhead>()->IsShowSilouhette = false;
    }

    void LayerUI::ShowMappingPopup()
    {
        ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y));
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::Begin("Mapping", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

            CvtGlTextureObj2ImTexture(AIAC_APP.GetRenderer()->GetMappingView(), m_MappingViewImTexture);
            // TODO: use config to store the size, and set glViewPort before rendering
            ImGui::ImageButton(m_MappingViewImTexture.ID, ImVec2(600, 442), ImVec2(0, 1), ImVec2(1, 0), 0, ImColor(255, 255, 255, 128));

            ImGui::SameLine();
            ImGui::BeginChild("mapping_info_child", ImVec2(0, 0), false);
                // First part - global view
                ImVec2 sideBarViewportSize = ImGui::GetContentRegionAvail();
                ImGui::BeginChild("global_view", ImVec2(sideBarViewportSize.x, sideBarViewportSize.x * 3 / 4 + 20), true);
                    ImVec2 viewportSize = ImGui::GetContentRegionAvail();
                    viewportSize = ImVec2(viewportSize.x, viewportSize.y - 24);
                    AIAC_APP.GetRenderer()->SetGlobalViewSize(viewportSize.x, viewportSize.y);
                    SetGlobalViewUI(viewportSize);
                ImGui::EndChild();

                // Second part - mapping info
                // sideBarViewportSize = ImGui::GetContentRegionAvail();
                // ImGui::BeginChild("mapping_info", ImVec2(sideBarViewportSize.x, 0), true);
                //     ImGui::Text("Map Points: %u", AIAC_APP.GetLayer<LayerSlam>()->Slam.getMap()->map_points.size());
                //     ImGui::Text("Map Markers: %lu", AIAC_APP.GetLayer<LayerSlam>()->Slam.getMap()->map_markers.size());
                // ImGui::EndChild();

                // Third part - mapping menu for adjusting params
                sideBarViewportSize = ImGui::GetContentRegionAvail();
                ImGui::BeginChild("mapping_menu", ImVec2(sideBarViewportSize.x, sideBarViewportSize.y - 48), true);
                    ImGui::Text("Save Path:");
                    ImGui::InputText("## Map Saving Path", m_MappingParams.MapSavingPath, PATH_BUF_SIZE, ImGuiInputTextFlags_AutoSelectAll);
                    ImGui::SameLine();
                    if(ImGui::Button(".", ImVec2(0, 0))){
                        // m_IsSavingMap = true;
                        OpenFileSelectDialog("Choose Save Map Path", ".map", m_MappingParams.MapSavingPath);
                    }
                    ImGui::Checkbox("Optimize Map", &m_MappingParams.ToOptimizeMap);
                    ImGui::Checkbox("Save Map", &m_MappingParams.ToSaveMap);
                    
                    ImGui::Text("--------------------");
                    ImGui::Text("Reconstruct Params:");
                    float sliderValFloat = 0.f;
                    int sliderValInt = 0;

                    sliderValFloat = 0.f;
                    ImGui::SliderFloat("## Radius Search", &sliderValFloat, -1.0f, 1.0f, "Radius Search", ImGuiSliderFlags_AlwaysClamp);
                    if (sliderValFloat != 0.f) m_ReconstructParams.RadiusSearch += sliderValFloat;
                    ImGui::SameLine();
                    ImGui::Text("%.1f", m_ReconstructParams.RadiusSearch);

                    sliderValFloat = 0.f;
                    ImGui::SliderFloat("## Crease Angle Threshold", &sliderValFloat, -1.0f, 1.0f, "Crease Angle Threshold", ImGuiSliderFlags_AlwaysClamp);
                    if (sliderValFloat != 0.f) m_ReconstructParams.CreaseAngleThreshold += sliderValFloat;
                    ImGui::SameLine();
                    ImGui::Text("%.1f", m_ReconstructParams.CreaseAngleThreshold);

                    sliderValInt = 0;
                    ImGui::SliderInt("## Min Cluster Size", &sliderValInt, -3, 3, "Min Cluster Size", ImGuiSliderFlags_AlwaysClamp);
                    if (sliderValInt != 0) m_ReconstructParams.MinClusterSize += sliderValInt;
                    ImGui::SameLine();
                    ImGui::Text("%d", m_ReconstructParams.MinClusterSize);

                    sliderValFloat = 0.f;
                    ImGui::SliderFloat("## Max Pln Dist", &sliderValFloat, -1.0f, 1.0f, "Max Pln Dist", ImGuiSliderFlags_AlwaysClamp);
                    if (sliderValFloat != 0.f) m_ReconstructParams.MaxPlnDist += sliderValFloat;
                    ImGui::SameLine();
                    ImGui::Text("%.1f", m_ReconstructParams.MaxPlnDist);

                    sliderValFloat = 0.f;
                    ImGui::SliderFloat("## Max Pln Angle", &sliderValFloat, -1.0f, 1.0f, "Max Pln Angle", ImGuiSliderFlags_AlwaysClamp);
                    if (sliderValFloat != 0.f) m_ReconstructParams.MaxPlnAngle += sliderValFloat;
                    ImGui::SameLine();
                    ImGui::Text("%.1f", m_ReconstructParams.MaxPlnAngle);

                    sliderValFloat = 0.f;
                    ImGui::SliderFloat("## AABB Scale Factor", &sliderValFloat, -1.0f, 1.0f, "AABB Scale Factor", ImGuiSliderFlags_AlwaysClamp);
                    if (sliderValFloat != 0.f) m_ReconstructParams.AABBScaleFactor += sliderValFloat;
                    ImGui::SameLine();
                    ImGui::Text("%.1f", m_ReconstructParams.AABBScaleFactor);

                    sliderValFloat = 0.f;
                    ImGui::SliderFloat("## Max Poly Dist", &sliderValFloat, -1.0f, 1.0f, "Max Poly Dist", ImGuiSliderFlags_AlwaysClamp);
                    if (sliderValFloat != 0.f) m_ReconstructParams.MaxPolyDist += sliderValFloat;
                    ImGui::SameLine();
                    ImGui::Text("%.1f", m_ReconstructParams.MaxPolyDist);

                    sliderValFloat = 0.f;
                    ImGui::PushItemWidth(-54);
                    ImGui::SliderFloat("## Eps", &sliderValFloat, -1.0f, 1.0f, "Eps", ImGuiSliderFlags_AlwaysClamp);
                    ImGui::PopItemWidth();
                    if (sliderValFloat > 0.f) m_ReconstructParams.Eps *= 2;
                    else if (sliderValFloat < 0.f) m_ReconstructParams.Eps /= 2;
                    ImGui::SameLine();
                    ImGui::Text("%.1e", m_ReconstructParams.Eps);

                ImGui::EndChild();
                if(ImGui::Button("Discard", ImVec2(ImGui::GetContentRegionAvail().x, 40))){
                    AIAC_EBUS->EnqueueEvent(std::make_shared<SLAMStopMappingEvent>(
                        false,
                        m_MappingParams.MapSavingPath,
                        false,
                        m_ReconstructParams.RadiusSearch,
                        m_ReconstructParams.CreaseAngleThreshold,
                        m_ReconstructParams.MinClusterSize,
                        m_ReconstructParams.AABBScaleFactor,
                        m_ReconstructParams.MaxPolyDist,
                        m_ReconstructParams.MaxPlnDist,
                        m_ReconstructParams.MaxPlnAngle,
                        m_ReconstructParams.Eps
                    ));
                }
                if(ImGui::Button("Save & Exit", ImVec2(ImGui::GetContentRegionAvail().x, 40))){
                    AIAC_EBUS->EnqueueEvent(std::make_shared<SLAMStopMappingEvent>(
                        m_MappingParams.ToSaveMap,
                        m_MappingParams.MapSavingPath,
                        m_MappingParams.ToOptimizeMap,
                        m_ReconstructParams.RadiusSearch,
                        m_ReconstructParams.CreaseAngleThreshold,
                        m_ReconstructParams.MinClusterSize,
                        m_ReconstructParams.AABBScaleFactor,
                        m_ReconstructParams.MaxPolyDist,
                        m_ReconstructParams.MaxPlnDist,
                        m_ReconstructParams.MaxPlnAngle,
                        m_ReconstructParams.Eps
                    ));
                }
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

    void LayerUI::ShowCamCalibPopup()
    {
        ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y));
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::Begin("Camera Calibration", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

        CvtGlTextureObj2ImTexture(AIAC_APP.GetRenderer()->GetCamCalibView(), m_CamCalibViewImTexture);
        ImGui::ImageButton(m_CamCalibViewImTexture.ID, ImVec2(600, 442), ImVec2(0, 1), ImVec2(1, 0), 0, ImColor(255, 255, 255, 128));

        ImGui::SameLine();
        ImGui::BeginChild("cam_calib_info_child", ImVec2(0, 0), false); {
            ImVec2 sideBarViewportSize = ImGui::GetContentRegionAvail();
            ImGui::BeginChild("calib_param", ImVec2(sideBarViewportSize.x, 132), true);
            {
                ImGui::Text("Board Size:");

                ImGui::Text("Width");
                ImGui::SameLine();
                ImGui::InputInt("Board Width",
                                &AIAC_APP.GetLayer<AIAC::LayerCameraCalib>()->GetCameraCalibrator().boardSize.width);

                ImGui::Text("Height");
                ImGui::SameLine();
                ImGui::InputInt("Board Height",
                                &AIAC_APP.GetLayer<AIAC::LayerCameraCalib>()->GetCameraCalibrator().boardSize.height);

                ImGui::Text("Square Size");
                ImGui::SameLine();
                ImGui::InputFloat(" Square Size",
                                  &AIAC_APP.GetLayer<AIAC::LayerCameraCalib>()->GetCameraCalibrator().squareSize);

                ImGui::Checkbox("Use Fisheye",
                                &AIAC_APP.GetLayer<AIAC::LayerCameraCalib>()->GetCameraCalibrator().useFisheye);

            } ImGui::EndChild();
            ImGui::BeginChild("capture_setting", ImVec2(sideBarViewportSize.x, 108), true);
            {
                ImGui::Checkbox("Auto Capture", &AIAC_APP.GetLayer<AIAC::LayerCameraCalib>()->AutoCapture);

                ImGui::Text("Delay");
                ImGui::SameLine();
                ImGui::InputInt("Delay", &AIAC_APP.GetLayer<AIAC::LayerCameraCalib>()->Delay);

                ImGui::Text("Num of Frames");
                ImGui::SameLine();
                ImGui::InputInt("Num Of Frame", &AIAC_APP.GetLayer<AIAC::LayerCameraCalib>()->NumOfFrame);

                stringstream ss;
                if (AIAC_APP.GetLayer<AIAC::LayerCameraCalib>()->IsCapturing()) {
                    ss << "Capturing: "
                        << AIAC_APP.GetLayer<AIAC::LayerCameraCalib>()->GetCameraCalibrator().GetImageAmount() << "/"
                        << AIAC_APP.GetLayer<AIAC::LayerCameraCalib>()->NumOfFrame;
                } else {
                    ss << "Click Start to Capture";
                }
                ImGui::Text("%s", ss.str().c_str());

            }ImGui::EndChild();
            sideBarViewportSize = ImGui::GetContentRegionAvail();
            ImGui::BeginChild("menu", sideBarViewportSize, true);
            {
                // Save Path
                if(ImGui::Button(">")){
                    m_IsChoosingCamCalibFileSavePath = true;
                }
                ImGui::SameLine();
                char tmpSavePath[PATH_BUF_SIZE];
                strcpy(tmpSavePath, AIAC_APP.GetLayer<AIAC::LayerCameraCalib>()->SaveFilename.c_str());
                ImGui::InputText("Save Path", tmpSavePath, PATH_BUF_SIZE);
                AIAC_APP.GetLayer<AIAC::LayerCameraCalib>()->SaveFilename = tmpSavePath;

                if(ImGui::Button("Start")){
                    AIAC_APP.GetLayer<AIAC::LayerCameraCalib>()->StartCapturing();
                }
                ImGui::SameLine();
                if(ImGui::Button("Exit")){
                    AIAC_APP.GetLayer<AIAC::LayerCameraCalib>()->StopCalibration();
                }
            } ImGui::EndChild();
        } ImGui::EndChild();

        ImGui::End();
    }

    void LayerUI::ShowCombineMapPopup()
    {
//        ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x * 0.3, ImGui::GetIO().DisplaySize.y * 0.3));

        ImGui::Begin("Combine map", nullptr);
            ImGui::PushItemWidth(-1);

            ImGui::Text("Select File:");
            if(ImGui::Button("Map 1", ImVec2(60, 0))){
                OpenFileSelectDialog("Select input map 1 path", ".map", m_CombMapParams.MapPathA);
            }
            ImGui::SameLine();
            ImGui::InputText("In Map 1", m_CombMapParams.MapPathA, PATH_BUF_SIZE, ImGuiInputTextFlags_AutoSelectAll);

            if(ImGui::Button("Map 2", ImVec2(60, 0))){
                OpenFileSelectDialog("Select input map 2 path", ".map", m_CombMapParams.MapPathB);
            }
            ImGui::SameLine();
            ImGui::InputText("In Map 2", m_CombMapParams.MapPathB, PATH_BUF_SIZE, ImGuiInputTextFlags_AutoSelectAll);

            if(ImGui::Button("Output", ImVec2(60, 0))){
                OpenFileSelectDialog("Select export map path", ".map", m_CombMapParams.OutputPath);
            }
            ImGui::SameLine();
            ImGui::InputText("In Output Path", m_CombMapParams.OutputPath, PATH_BUF_SIZE, ImGuiInputTextFlags_AutoSelectAll);
            ImGui::PopItemWidth();

            ImGui::Text(" ");
            ImGui::Text(" ");
            ImGui::SameLine(ImGui::GetWindowWidth() - 176);
            if(ImGui::Button("Cancel", ImVec2(80, 0))){ m_IsCombiningMap = false; }
            ImGui::SameLine();
            if(ImGui::Button("Confirm", ImVec2(80, 0))){
                if(strlen(m_CombMapParams.MapPathA) == 0 || strlen(m_CombMapParams.MapPathB) == 0){
                    AIAC_ERROR("Path not selected.");
                } else {
                    AIAC_EBUS->EnqueueEvent(std::make_shared<SLAMCombineMapEvent>(
                            m_CombMapParams.MapPathA,
                            m_CombMapParams.MapPathB,
                            m_CombMapParams.OutputPath,
                            50,
                            m_ReconstructParams.RadiusSearch,
                            m_ReconstructParams.CreaseAngleThreshold,
                            m_ReconstructParams.MinClusterSize,
                            m_ReconstructParams.AABBScaleFactor,
                            m_ReconstructParams.MaxPolyDist,
                            m_ReconstructParams.MaxPlnDist,
                            m_ReconstructParams.MaxPlnAngle,
                            m_ReconstructParams.Eps
                    ));

                    memset(m_CombMapParams.MapPathA, 0, PATH_BUF_SIZE);
                    memset(m_CombMapParams.MapPathB, 0, PATH_BUF_SIZE);
                    memset(m_CombMapParams.OutputPath, 0, PATH_BUF_SIZE);
                    m_IsCombiningMap = false;
                }
            }

        ImGui::End();
    }

    void LayerUI::ShowReconstruct3DPopup()
    {
        ImGui::Begin("Reconstruct 3D", nullptr);
            ImGui::Text("Select Path:");
            if(ImGui::Button("Import .yml", ImVec2(84, 0))){
                OpenFileSelectDialog("Select map path", ".yml", m_ReconstructParams.TagMapPath);
            }
            ImGui::SameLine();
            ImGui::InputText("## Tag Map Path", m_ReconstructParams.TagMapPath, PATH_BUF_SIZE, ImGuiInputTextFlags_AutoSelectAll);
            if(ImGui::Button("Export .ply", ImVec2(84, 0))){
                OpenFileSelectDialog("Select export .ply path", ".ply", m_ReconstructParams.ExportPath);
            }
            ImGui::SameLine();
            ImGui::InputText("## Export Path", m_ReconstructParams.ExportPath, PATH_BUF_SIZE, ImGuiInputTextFlags_AutoSelectAll);

            ImGui::PushItemWidth(-54);

            ImGui::Text("Reconstruct Params");
            ImGui::SameLine();
            if(ImGui::Button("Load from file", ImVec2(106, 0)))
            {
                std::string defaultConfigDir = AIAC::Config::Get<std::string>(
                    AIAC::Config::SEC_TSLAM,
                    AIAC::Config::RECONSTRUCT_CONFIG_DEFAULT_FILE,
                    "assets/tslam/reconstruct_default.ini");
                if (!defaultConfigDir.empty()) {
                    AIAC_INFO("Default config for reconstruction dir: ");
                    AIAC_INFO(defaultConfigDir);
                    const char* defaultConfigDirCStr = defaultConfigDir.c_str();
                    this->m_TmpPathBuf[0] = '\0';
                    strcpy(this->m_TmpPathBuf, defaultConfigDirCStr);
                }
                else
                    AIAC_WARN("Default config for reconstruction dir is empty.");

                AIAC_INFO("TmpPathBuf1: ");
                AIAC_INFO(this->m_TmpPathBuf);
                
                OpenFileSelectDialog("Load Reconstruction Parameter", ".ini", m_TmpPathBuf, [&]
                {
                    AIAC_INFO("TmpPathBuf2: ");
                    AIAC_INFO(this->m_TmpPathBuf);

                    LoadReconstructParamsFromFile(m_TmpPathBuf);
                });
            }
            float sliderValFloat = 0.f;
            int sliderValInt = 0;

            sliderValFloat = 0.f;
            ImGui::Text(" (2.0)");
            ImGui::SameLine();
            ImGui::SliderFloat("## Radius Search", &sliderValFloat, -1.0f, 1.0f, "Radius Search", ImGuiSliderFlags_AlwaysClamp);
            if (sliderValFloat != 0.f) m_ReconstructParams.RadiusSearch += sliderValFloat;
            ImGui::SameLine();
            ImGui::Text("%.1f", m_ReconstructParams.RadiusSearch);

            sliderValFloat = 0.f;
            ImGui::Text(" (5.0)");
            ImGui::SameLine();
            ImGui::SliderFloat("## Crease Angle Threshold", &sliderValFloat, -1.0f, 1.0f, "Crease Angle Threshold", ImGuiSliderFlags_AlwaysClamp);
            if (sliderValFloat != 0.f) m_ReconstructParams.CreaseAngleThreshold += sliderValFloat;
            ImGui::SameLine();
            ImGui::Text("%.1f", m_ReconstructParams.CreaseAngleThreshold);

            sliderValInt = 0;
            ImGui::Text("  (1) ");
            ImGui::SameLine();
            ImGui::SliderInt("## Min Cluster Size", &sliderValInt, -3, 3, "Min Cluster Size", ImGuiSliderFlags_AlwaysClamp);
            if (sliderValInt != 0) m_ReconstructParams.MinClusterSize += sliderValInt;
            ImGui::SameLine();
            ImGui::Text("%d", m_ReconstructParams.MinClusterSize);

            sliderValFloat = 0.f;
            ImGui::Text(" (1.0)");
            ImGui::SameLine();
            ImGui::SliderFloat("## Max Pln Dist", &sliderValFloat, -1.0f, 1.0f, "Max Pln Dist", ImGuiSliderFlags_AlwaysClamp);
            if (sliderValFloat != 0.f) m_ReconstructParams.MaxPlnDist += sliderValFloat;
            ImGui::SameLine();
            ImGui::Text("%.1f", m_ReconstructParams.MaxPlnDist);

            sliderValFloat = 0.f;
            ImGui::Text(" (5.0)");
            ImGui::SameLine();
            ImGui::SliderFloat("## Max Pln Angle", &sliderValFloat, -1.0f, 1.0f, "Max Pln Angle", ImGuiSliderFlags_AlwaysClamp);
            if (sliderValFloat != 0.f) m_ReconstructParams.MaxPlnAngle += sliderValFloat;
            ImGui::SameLine();
            ImGui::Text("%.1f", m_ReconstructParams.MaxPlnAngle);

            sliderValFloat = 0.f;
            ImGui::Text(" (1.1)");
            ImGui::SameLine();
            ImGui::SliderFloat("## AABB Scale Factor", &sliderValFloat, -1.0f, 1.0f, "AABB Scale Factor", ImGuiSliderFlags_AlwaysClamp);
            if (sliderValFloat != 0.f) m_ReconstructParams.AABBScaleFactor += sliderValFloat;
            ImGui::SameLine();
            ImGui::Text("%.1f", m_ReconstructParams.AABBScaleFactor);

            sliderValFloat = 0.f;
            ImGui::Text(" (1.0)");
            ImGui::SameLine();
            ImGui::SliderFloat("## Max Poly Dist", &sliderValFloat, -1.0f, 1.0f, "Max Poly Dist", ImGuiSliderFlags_AlwaysClamp);
            if (sliderValFloat != 0.f) m_ReconstructParams.MaxPolyDist += sliderValFloat;
            ImGui::SameLine();
            ImGui::Text("%.1f", m_ReconstructParams.MaxPolyDist);

            sliderValFloat = 0.f;
            ImGui::Text("(1e-5)");
            ImGui::SameLine();
            ImGui::SliderFloat("## Eps", &sliderValFloat, -1.0f, 1.0f, "Eps", ImGuiSliderFlags_AlwaysClamp);
            ImGui::PopItemWidth();
            if (sliderValFloat > 0.f) m_ReconstructParams.Eps *= 2;
            else if (sliderValFloat < 0.f) m_ReconstructParams.Eps /= 2;
            ImGui::SameLine();
            ImGui::Text("%.1e", m_ReconstructParams.Eps);


            ImGui::Text(" ");
            ImGui::Text(" ");
            ImGui::SameLine(ImGui::GetWindowWidth() - 180);
            if(ImGui::Button("Cancel", ImVec2(80, 0))){ m_IsReconstructing3D = false; }
            ImGui::SameLine();
            if(ImGui::Button("Confirm", ImVec2(80, 0))){
                if(strlen(m_ReconstructParams.TagMapPath) == 0 || strlen(m_ReconstructParams.ExportPath) == 0){
                    AIAC_ERROR("Path not selected.");
                } else {                    
                    // Reconstruct 3D
                    bool isReconstructed = AIAC_APP.GetLayer<AIAC::LayerSlam>()->Slam.Reconstruct3DModelAndExportPly(
                        m_ReconstructParams.TagMapPath,
                        m_ReconstructParams.ExportPath,
                        m_ReconstructParams.RadiusSearch,
                        m_ReconstructParams.CreaseAngleThreshold,
                        m_ReconstructParams.MinClusterSize,
                        m_ReconstructParams.AABBScaleFactor,
                        m_ReconstructParams.MaxPolyDist,
                        m_ReconstructParams.MaxPlnDist,
                        m_ReconstructParams.MaxPlnAngle,
                        m_ReconstructParams.Eps
                    );

                    // Load reconstructed 3D model
                    if(isReconstructed) AIAC_APP.GetLayer<AIAC::LayerModel>()->LoadScannedModel(m_ReconstructParams.ExportPath);
                    else AIAC_WARN("Reconstruction failed, skip loading the model");
                    
                    // memset(m_ReconstructParams.TagMapPath, 0, PATH_BUF_SIZE);
                    // memset(m_ReconstructParams.ExportPath, 0, PATH_BUF_SIZE);
                    m_IsReconstructing3D = false;
                }
            }

        ImGui::End();
    }

    // FIXME: This should not be here, the LayerUI should only handle visualization, not logic
    void LayerUI::LoadReconstructParamsFromFile(const char *filePath){
        inih::INIReader reader(filePath);
        auto section = "Reconstruction Parameters";
        m_ReconstructParams.RadiusSearch = reader.Get<float>(section, "RadiusSearch");
        m_ReconstructParams.CreaseAngleThreshold = reader.Get<float>(section, "CreaseAngleThreshold");
        m_ReconstructParams.MinClusterSize = reader.Get<int>(section, "MinClusterSize");
        m_ReconstructParams.AABBScaleFactor = reader.Get<float>(section, "AABBScaleFactor");
        m_ReconstructParams.MaxPolyDist = reader.Get<float>(section, "MaxPolyDist");
        m_ReconstructParams.MaxPlnDist = reader.Get<float>(section, "MaxPlnDist");
        m_ReconstructParams.MaxPlnAngle = reader.Get<float>(section, "MaxPlnAngle");
        m_ReconstructParams.Eps = reader.Get<float>(section, "Eps");
    }

    void LayerUI::ShowSaveCamCalibFileDialog()
    {
        ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x * 0.8, ImGui::GetIO().DisplaySize.y * 0.75));
        ImGuiFileDialog::Instance()->OpenDialog("ChooseSaveCalibFilePath", "Choose calib file path", ".yml", ".");
        if (ImGuiFileDialog::Instance()->Display("ChooseSaveCalibFilePath"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();

                AIAC_INFO("Saving calib file to {0}", filePathName.c_str());
                AIAC_APP.GetLayer<AIAC::LayerCameraCalib>()->SetSaveFilename(filePathName);
            }
            ImGuiFileDialog::Instance()->Close();
            m_IsChoosingCamCalibFileSavePath = false;
        }
    }

    void LayerUI::OpenFileSelectDialog(const char* title, const char* fileExt, char *path, std::function<void()> callback) {
        ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x * 0.8, ImGui::GetIO().DisplaySize.y * 0.75));
        if (strlen(path) == 0) {
            ImGuiFileDialog::Instance()->OpenDialog("SelectFileDialog", title, fileExt, m_FileSelectDefaultPath);
        }
        else {
            char* pathBuf = new char[PATH_BUF_SIZE];
            memset(pathBuf, 0, PATH_BUF_SIZE);
            memcpy(pathBuf, path, strlen(path));
            ImGuiFileDialog::Instance()->OpenDialog("SelectFileDialog", title, fileExt, pathBuf);
            ImGuiFileDialog::Instance()->OpenDialog("SelectFileDialog", title, fileExt, path);
        }
        m_FileSelectionTargetBuf = path;
        m_FileSelectionCallback = callback;
    }

    void LayerUI::ShowFileSelectDialog(){
        if (ImGuiFileDialog::Instance()->Display("SelectFileDialog")) {
            if (ImGuiFileDialog::Instance()->IsOk()) {
                std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                AIAC_INFO("Select: {0}", filePathName.c_str());
                memset(m_FileSelectionTargetBuf, 0, PATH_BUF_SIZE);
                memcpy(m_FileSelectionTargetBuf, filePathName.c_str(), filePathName.length());

                if(m_FileSelectionCallback) m_FileSelectionCallback();
            }
            ImGuiFileDialog::Instance()->Close();
        }
        m_FileSelectDefaultPath = ImGuiFileDialog::Instance()->GetCurrentPath();
        if (m_FileSelectDefaultPath[m_FileSelectDefaultPath.length()-1] != '/') {
            m_FileSelectDefaultPath += "/";
        };
    }

    void LayerUI::ShowLogRecorderUI() {
        ImGui::Begin("Log Recorder", m_IsOpen);
        if (!AIAC_APP.GetLayer<AIAC::LayerLogRecorder>()->IsRecording()){
//            ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_GREEN);
            if(ImGui::Button("Start", ImVec2(-1, 40))){
                AIAC_APP.GetLayer<AIAC::LayerLogRecorder>()->StartRecording();
            }
//            ImGui::PopStyleColor();
        } else {
            ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_RED);
            if(ImGui::Button("Stop", ImVec2(-1, 40))){
                AIAC_APP.GetLayer<AIAC::LayerLogRecorder>()->StopRecording();
            }
            ImGui::PopStyleColor();

            if(AIAC_APP.GetLayer<AIAC::LayerLogRecorder>()->IsPaused()) {
                ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_YELLOW);
                if(ImGui::Button("Resume", ImVec2(-1, 40))){
                    AIAC_APP.GetLayer<AIAC::LayerLogRecorder>()->ResumeRecording();
                }
                ImGui::PopStyleColor();
            } else {
                ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_GREY);
                if(ImGui::Button("Pause", ImVec2(-1, 40))) {
                    AIAC_APP.GetLayer<AIAC::LayerLogRecorder>()->PauseRecording();
                }
                ImGui::PopStyleColor();
            }
        }
        ImGui::End();
    }
}