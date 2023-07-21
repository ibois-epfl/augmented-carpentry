#include "aiacpch.h"

#include "AIAC/LayerUI.h"
#include "AIAC/Application.h"

#include "AIAC/Image.h"
#include "AIAC/Render/Renderer.h"

#include "AIAC/UI/ImGuiFileDialog.h"

#include "AIAC/UI/ClrPalette.h"
#include "AIAC/UI/CustomLogos.h"
#include "LayerCameraCalib.h"

#include "ttool.hh"


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

        // Load images from memory
        m_LogoBlack = AIAC::Image(AIAC_LOGO_BLACK);
        m_LogoLightClr = AIAC::Image(AIAC_LOGO_COLOR);

        // Set panes UI for layers
        //                 Label       Collapse             PaneContent
        StackPane(PaneUI("Camera",       true,      AIAC_BIND_EVENT_FN(SetPaneUICamera)    ));
        StackPane(PaneUI("Slam",         true,      AIAC_BIND_EVENT_FN(SetPaneUISlam)      ));
        StackPane(PaneUI("Render",       true,      AIAC_BIND_EVENT_FN(SetPaneUIRender)    ));
        StackPane(PaneUI("ACIM",         true,      AIAC_BIND_EVENT_FN(SetPaneUIACIM)      ));
        StackPane(PaneUI("Toolhead",     true,      AIAC_BIND_EVENT_FN(SetPaneUIToolhead)  ));

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
            if (m_IsSavingMap) {
                ShowSaveMapFileDialog();
            }
        } else if (AIAC_APP.GetLayer<LayerCameraCalib>()->IsCalibrating()){
            ShowCamCalibPopup();
            if (m_IsChoosingCamCalibFileSavePath){
                ShowSaveCamCalibFileDialog();
            }
        } else {
            ShowMenuBar();
            ShowMainUI();
            ShowSceneViewport();

            if(m_IsCombiningMap){
                ShowCombineMapPopup();
                if(m_CombMapParams.IsSelectingFile){
                    ShowMapFileDialog(m_CombMapParams.FilePathTarget);
                }
            }

            if(m_IsReconstructing3D){
                ShowReconstruct3DPopup();
                if (m_ReconstructParams.IsSelectingTagMapPath) {
                    ShowFileSelectDialog("Select map path", ".yml",
                                         m_ReconstructParams.TagMapPath,
                                         m_ReconstructParams.IsSelectingTagMapPath);
                } else if(m_ReconstructParams.IsSelectingExportPath){
                    ShowFileSelectDialog("Select export path", ".ply",
                                         m_ReconstructParams.ExportPath,
                                         m_ReconstructParams.IsSelectingExportPath);
                } else if(m_ReconstructParams.IsSelectingParamPath){
                    ShowFileSelectDialog("Select camera calibration path", ".yml",
                                         m_ReconstructParams.ParamPath,
                                         m_ReconstructParams.IsSelectingParamPath);
                }
            }
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
        if (ImGui::BeginMainMenuBar())
        {
            ImGui::Image(m_LogoBlack.GetImTexture().ID, ImVec2(18, 18), ImVec2(0, 1), ImVec2(1, 0));
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
        ImGui::Image(m_LogoLightClr.GetImTexture().ID, ImVec2(60, 60), ImVec2(0, 1), ImVec2(1, 0));
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

        AIAC::Camera& camera = AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera;
        ImGui::Text("Resolution: (%d x %d) > (%d x %d)", camera.GetRawWidth(), camera.GetRawHeight(), camera.GetWidth(), camera.GetHeight());

        ImGui::BeginChild("camera_function_child", ImVec2(0, 50), true, ImGuiWindowFlags_HorizontalScrollbar);
            ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_LIGHT_GREY);
            if(ImGui::Button("Start Calibration")){
                AIAC_APP.GetRenderer()->StartCamCalib();
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
        ImGui::PushStyleColor(ImGuiCol_Button, AIAC_UI_LIGHT_GREY);
        ImGui::Text("Import files:");
        ImGui::BeginChild("slam_info_child", ImVec2(0, 36), true, ImGuiWindowFlags_HorizontalScrollbar);
            if (ImGui::Button("Open SLAM map"))
                ImGuiFileDialog::Instance()->OpenDialog("ChooseSLAMmap", "Open SLAM map", ".map", ".");

            if (ImGuiFileDialog::Instance()->Display("ChooseSLAMmap"))
            {
                if (ImGuiFileDialog::Instance()->IsOk())
                {
                    std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                    //                std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
                    // action
                    //                AIAC_APP.GetLayer<LayerSlam>()->Slam.setMap(filePathName, true);
                    AIAC_EBUS->EnqueueEvent(std::make_shared<SLAMMapLoadedEvent>(filePathName));
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
                AIAC_EBUS->EnqueueEvent(std::make_shared<SLAMVocabularyLoadedEvent>(filePathName));
                }
                ImGuiFileDialog::Instance()->Close();
            }
        ImGui::EndChild();
        ImGui::Text("Mapping Functions:");
        ImGui::BeginChild("mapping_function_child", ImVec2(0, 36), true, ImGuiWindowFlags_HorizontalScrollbar);
            if(ImGui::Button("Start Mapping")){
                AIAC_EBUS->EnqueueEvent(std::make_shared<SLAMStartMappingEvent>());
            }
            ImGui::SameLine();
            if(ImGui::Button("Combine Map")){
                m_IsCombiningMap = true;
            }
            ImGui::SameLine();
            if(ImGui::Button("Reconstruct 3D")){
                m_IsReconstructing3D = true;
            }
            ImGui::PopStyleColor();
        ImGui::EndChild();

        ImGui::Checkbox("Show Tag", &AIAC_APP.GetLayer<AIAC::LayerSlam>()->ToShowTag);
        ImGui::Checkbox("Process Frames", &AIAC_APP.GetLayer<AIAC::LayerSlam>()->ToProcess);
        ImGui::Checkbox("Enhance Photo", &AIAC_APP.GetLayer<AIAC::LayerSlam>()->ToEnhance);

        ImGui::Text("Tracked: %s", AIAC_APP.GetLayer<AIAC::LayerSlam>()->IsTracked() ? "Yes" : "No");

        std::string camPoseStr; camPoseStr << AIAC_APP.GetLayer<AIAC::LayerSlam>()->GetCamPoseCv();
        ImGui::Text("Estimated Camera Pose: \n%s", camPoseStr.c_str());
    }

    void LayerUI::SetPaneUIRender()
    {
        // ImGui::Checkbox("Point Cloud Map", &AIAC_APP.GetRenderer()->ShowPointCloudMap);
//         ImGui::Checkbox("Digital Model", &AIAC_APP.GetRenderer()->ShowDigitalModel);
//         if(ImGui::Button("Load Digital Model")){
//             ImGuiFileDialog::Instance()->OpenDialog("ChooseDigitalModel", "Open Digital Model", ".ply", ".");
//         }
//         if (ImGuiFileDialog::Instance()->Display("ChooseDigitalModel"))
//         {
//             if (ImGuiFileDialog::Instance()->IsOk())
//             {
//                 std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
//                 // TODO: Add ply to renderer
//                 AIAC_INFO("Loading Digital Model: {}", filePathName);
//                 AIAC_APP.GetRenderer()->Meshes.emplace_back(filePathName);
// //                AIAC_EBUS->EnqueueEvent(std::make_shared<CameraCalibrationLoadedEvent>(filePathName));
//             }
//             ImGuiFileDialog::Instance()->Close();
//         }
    }

    void LayerUI::SetPaneUIACIM()
    {
        // ACIM Loader
        if(ImGui::Button("Load ACIM")){
            ImGuiFileDialog::Instance()->OpenDialog("ChooseACIM", "Open ACIM file", ".acim", ".");
        }
        if (ImGuiFileDialog::Instance()->Display("ChooseACIM"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                AIAC_APP.GetLayer<AIAC::LayerModel>()->LoadACInfoModel(filePathName);
            }
            ImGuiFileDialog::Instance()->Close();
        }

        // Scanned Model Loader
        ImGui::SameLine();
        if(ImGui::Button("Load Scanned Model")){
            ImGuiFileDialog::Instance()->OpenDialog("ChooseScannedModel", "Open Scanned Model", ".ply", ".");
        }
        if (ImGuiFileDialog::Instance()->Display("ChooseScannedModel"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                AIAC_APP.GetLayer<AIAC::LayerModel>()->LoadScannedModel(filePathName);
            }
            ImGuiFileDialog::Instance()->Close();
        }

        // Re-position the ACIM model
        ImGui::Text("Adjust model alignment:");
        ImGui::BeginChild("Adjust model alignment", ImVec2(0, 84), true, ImGuiWindowFlags_HorizontalScrollbar);
            float sliderVal = 0.f;
            ImGui::SliderFloat("## Model Offset", &sliderVal, -1.0f, 1.0f, "Model Offset", ImGuiSliderFlags_AlwaysClamp);
                if (sliderVal != 0.f) AIAC_APP.GetLayer<AIAC::LayerModel>()->AddAlignOffset(sliderVal);
                sliderVal = 0.f;
            
            if(ImGui::Button("Align Center")){
                AIAC_APP.GetLayer<AIAC::LayerModel>()->ResetAlignOffset();
            }
            ImGui::SameLine();
            if(ImGui::Button("Align End 1")){
                AIAC_APP.GetLayer<AIAC::LayerModel>()->ForceAlignToEnd(1);
            }
            ImGui::SameLine();
            if(ImGui::Button("Align End 2")){
                AIAC_APP.GetLayer<AIAC::LayerModel>()->ForceAlignToEnd(0);
            }
            
            if(ImGui::Button("Rotate +")){
                AIAC_APP.GetLayer<AIAC::LayerModel>()->ChangeAlignRotation(1);
            }
            ImGui::SameLine();
            if(ImGui::Button("Rotate -")){
                AIAC_APP.GetLayer<AIAC::LayerModel>()->ChangeAlignRotation(-1);
            }
            ImGui::SameLine();
            if(ImGui::Button("Reset Rotation")){
                AIAC_APP.GetLayer<AIAC::LayerModel>()->ResetAlignRotation();
            }
            ImGui::SameLine();
            if(ImGui::Button("Flip")){
                AIAC_APP.GetLayer<AIAC::LayerModel>()->FlipAlign();
            }
        ImGui::EndChild();

        ImGui::Text("Components Control:");
        ImGui::BeginChild("Components Control Panel", ImVec2(0, 80), true, ImGuiWindowFlags_HorizontalScrollbar);
            ImGui::Text("Current Component:");
            string currentCompoID = AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().GetCurrentComponentID();
            static const char* previewValue = currentCompoID.c_str();
            if(ImGui::BeginCombo("##AvailableDevices", previewValue)){
                for (auto& componentID : AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().GetAllComponentsIDs()) {
                    bool isSelected = (currentCompoID == componentID);
                    if (ImGui::Selectable(componentID.c_str(), isSelected)){
                        AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().SetCurrentComponentTo(componentID.c_str());
                    }
                    if (isSelected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
            if(ImGui::Checkbox("Mark as Done", &AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().GetCurrentComponent()->IsMarkedDone));
        ImGui::EndChild();
    }

    void LayerUI::SetPaneUIToolhead()
    {
        if(ImGui::Checkbox("Draw Silhouette", &AIAC_APP.GetLayer<AIAC::LayerToolhead>()->IsShowSilouhette));
        if(ImGui::Checkbox("Draw Toolhead GOData", &AIAC_APP.GetLayer<AIAC::LayerToolhead>()->IsShowToolheadGOInfo))
            AIAC_APP.GetLayer<AIAC::LayerToolhead>()->ACInfoToolheadManager->GetActiveToolhead()->SetVisibility(AIAC_APP.GetLayer<AIAC::LayerToolhead>()->IsShowToolheadGOInfo);

        ImGui::Text("Toolhead Classifier:");
        ImGui::BeginChild("toolhead_control", ImVec2(0, 37), true, ImGuiWindowFlags_HorizontalScrollbar);
        if(ImGui::Button("Detect Toolhead", ImVec2(-1, 40)))
            AIAC_APP.GetLayer<AIAC::LayerToolhead>()->DetectToolhead();
        ImGui::EndChild();

        ImGui::Text("TTool control:");
        ImGui::BeginChild("ttool_control", ImVec2(0, 37), true, ImGuiWindowFlags_HorizontalScrollbar);
        ImGui::RadioButton("None", &AIAC_APP.GetLayer<AIAC::LayerToolhead>()->ToolheadStateUI, -1);
        ImGui::SameLine();
        ImGui::RadioButton("Track", &AIAC_APP.GetLayer<AIAC::LayerToolhead>()->ToolheadStateUI, 0);
        ImGui::SameLine();
        ImGui::RadioButton("Input Pose", &AIAC_APP.GetLayer<AIAC::LayerToolhead>()->ToolheadStateUI, 1);
        ImGui::EndChild();

        std::stringstream toolheadPose; toolheadPose << AIAC_APP.GetLayer<AIAC::LayerToolhead>()->GetPose();
        ImGui::Text("Estimated Toolhead Pose: \n%s", toolheadPose.str().c_str());
        ImGui::Text("Tracking Status: %s", AIAC_APP.GetLayer<AIAC::LayerToolhead>()->ToolheadStateUI == 0 ? AIAC_APP.GetLayer<AIAC::LayerToolhead>()->GetTrackingStatus().c_str() : "Not Tracking");

        if (AIAC_APP.GetLayer<AIAC::LayerToolhead>()->ToolheadStateUI != -1)
        {
            ImGui::Text("Toolhead pose inputs:");
            ImGui::BeginChild("toolhead_pose_inputs", ImVec2(0, 350), true, ImGuiWindowFlags_HorizontalScrollbar);
            
            if(ImGui::Button("save pose", ImVec2(-1, 40)))
                AIAC_APP.GetLayer<AIAC::LayerToolhead>()->TTool->ManipulateModel('y');

            if(ImGui::Button("reset pose", ImVec2(-1, 40)))
                AIAC_APP.GetLayer<AIAC::LayerToolhead>()->ResetPoseFromConfig();
            
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(200, 15));
            ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 100);
            ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 5);
            ImGui::PushItemWidth(-30);
            float sliderF = 0.f;
            ImGui::SliderFloat("Teq", &sliderF, -1.0f, 1.0f, "<backward T forward>", ImGuiSliderFlags_AlwaysClamp);
            if (sliderF != 0.f)
                if (sliderF > 0.f)
                    AIAC_APP.GetLayer<AIAC::LayerToolhead>()->TTool->ManipulateModel('e');
                else
                    AIAC_APP.GetLayer<AIAC::LayerToolhead>()->TTool->ManipulateModel('q');
            sliderF = 0.f;
            ImGui::SliderFloat("Tda", &sliderF, -1.0f, 1.0f, "<left T right>", ImGuiSliderFlags_AlwaysClamp);
            if (sliderF != 0.f)
                if (sliderF > 0.f)
                    AIAC_APP.GetLayer<AIAC::LayerToolhead>()->TTool->ManipulateModel('d');
                else
                    AIAC_APP.GetLayer<AIAC::LayerToolhead>()->TTool->ManipulateModel('a');
            sliderF = 0.f;
            ImGui::SliderFloat("Tws", &sliderF, -1.0f, 1.0f, "<down T up>", ImGuiSliderFlags_AlwaysClamp);
            if (sliderF != 0.f)
                if (sliderF > 0.f)
                    AIAC_APP.GetLayer<AIAC::LayerToolhead>()->TTool->ManipulateModel('w');
                else
                    AIAC_APP.GetLayer<AIAC::LayerToolhead>()->TTool->ManipulateModel('s');
            sliderF = 0.f;
            ImGui::SliderFloat("Rjl", &sliderF, -1.0f, 1.0f, "<left R right>", ImGuiSliderFlags_AlwaysClamp);
            if (sliderF != 0.f)
                if (sliderF > 0.f)
                    AIAC_APP.GetLayer<AIAC::LayerToolhead>()->TTool->ManipulateModel('j');
                else
                    AIAC_APP.GetLayer<AIAC::LayerToolhead>()->TTool->ManipulateModel('l');
            sliderF = 0.f;
            ImGui::SliderFloat("Rik", &sliderF, -1.0f, 1.0f, "<down R up>", ImGuiSliderFlags_AlwaysClamp);
            if (sliderF != 0.f)
                if (sliderF > 0.f)
                    AIAC_APP.GetLayer<AIAC::LayerToolhead>()->TTool->ManipulateModel('i');
                else
                    AIAC_APP.GetLayer<AIAC::LayerToolhead>()->TTool->ManipulateModel('k');
            sliderF = 0.f;
            ImGui::SliderFloat("Ruo", &sliderF, -1.0f, 1.0f, "<backward R forward>", ImGuiSliderFlags_AlwaysClamp);
            if (sliderF != 0.f)
                if (sliderF > 0.f)
                    AIAC_APP.GetLayer<AIAC::LayerToolhead>()->TTool->ManipulateModel('u');
                else
                    AIAC_APP.GetLayer<AIAC::LayerToolhead>()->TTool->ManipulateModel('o');
            ImGui::PopStyleVar(3);
            ImGui::PopItemWidth();
            ImGui::EndChild();
        }

        std::string toolheadName = AIAC_APP.GetLayer<AIAC::LayerToolhead>()->ACInfoToolheadManager->GetActiveToolheadName();
        ImGui::Text("Toolhead active: %s", toolheadName.c_str());
        ImGui::BeginChild("toolhead_selection", ImVec2(0, 70), true, ImGuiWindowFlags_HorizontalScrollbar);
        std::vector<std::string> toolheadNames;
        for (auto& toolhead : AIAC_APP.GetLayer<AIAC::LayerToolhead>()->ACInfoToolheadManager->GetToolheadNames())
            toolheadNames.emplace_back(toolhead);
        for (int i = 0; i < toolheadNames.size(); i++)
        {
            auto toolNameButton = ImGui::Button(toolheadNames[i].c_str());
            if (toolNameButton)
            {
                AIAC_APP.GetLayer<AIAC::LayerToolhead>()->SetCurrentObject(toolheadNames[i]);
            }
        }
        ImGui::EndChild();
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
                        m_IsSavingMap = true;
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
                if(ImGui::Button("Done & Exit", ImVec2(ImGui::GetContentRegionAvail().x, 40))){
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
                    AIAC_APP.GetRenderer()->StopCamCalib();
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
                m_CombMapParams.IsSelectingFile = true;
                m_CombMapParams.FilePathTarget = m_CombMapParams.MapPathA;
            }
            ImGui::SameLine();
            ImGui::InputText("In Map 1", m_CombMapParams.MapPathA, PATH_BUF_SIZE, ImGuiInputTextFlags_AutoSelectAll);

            if(ImGui::Button("Map 2", ImVec2(60, 0))){
                m_CombMapParams.IsSelectingFile = true;
                m_CombMapParams.FilePathTarget = m_CombMapParams.MapPathB;
            }
            ImGui::SameLine();
            ImGui::InputText("In Map 2", m_CombMapParams.MapPathB, PATH_BUF_SIZE, ImGuiInputTextFlags_AutoSelectAll);

            if(ImGui::Button("Output", ImVec2(60, 0))){
                m_CombMapParams.IsSelectingFile = true;
                m_CombMapParams.FilePathTarget = m_CombMapParams.OutputPath;
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
                if(strlen(m_CombMapParams.MapPathA) == 0 || strlen(m_CombMapParams.MapPathB) == 0 || strlen(m_CombMapParams.OutputPath) == 0){
                    AIAC_ERROR("Path not selected.");

                } else {
                    AIAC_APP.GetLayer<LayerSlam>()->Slam.CombineMap(
                            m_CombMapParams.MapPathA, m_CombMapParams.MapPathB, m_CombMapParams.OutputPath,
                            true, true, nullptr, 2);
                    memset(m_CombMapParams.MapPathA, 0, PATH_BUF_SIZE * 3);
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
                m_ReconstructParams.IsSelectingTagMapPath = true;
            }
            ImGui::SameLine();
            ImGui::InputText("## Export Path", m_ReconstructParams.TagMapPath, PATH_BUF_SIZE, ImGuiInputTextFlags_AutoSelectAll);
            if(ImGui::Button("Export .ply", ImVec2(84, 0))){
                m_ReconstructParams.IsSelectingExportPath = true;
            }
            ImGui::SameLine();
            ImGui::InputText("## Export Path", m_ReconstructParams.ExportPath, PATH_BUF_SIZE, ImGuiInputTextFlags_AutoSelectAll);
            

            ImGui::PushItemWidth(-54);

            ImGui::Text("Reconstruct Params");
            ImGui::SameLine();
            if(ImGui::Button("Load Param File", ImVec2(84, 0))){
                m_ReconstructParams.IsSelectingParamPath = true;
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
                if(strlen(m_ReconstructParams.TagMapPath) == 0 || strlen(m_ReconstructParams.TagMapPath) == 0){
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
    void LayerUI::ShowSaveMapFileDialog()
    {
        ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x * 0.8, ImGui::GetIO().DisplaySize.y * 0.75));
        ImGuiFileDialog::Instance()->OpenDialog("ChooseSaveMapPath", "Choose Save Map Path", ".map", ".");
        if (ImGuiFileDialog::Instance()->Display("ChooseSaveMapPath"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                ImGuiFileDialog::Instance()->GetFilePathName().copy(m_MappingParams.MapSavingPath, PATH_BUF_SIZE);
                // std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                // std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();

                // AIAC_INFO("Saving map to {0}", filePathName.c_str());
                // AIAC_APP.GetLayer<AIAC::LayerSlam>()->Slam.getMap()->optimize();
                // AIAC_APP.GetLayer<AIAC::LayerSlam>()->Slam.getMap()->saveToFile(filePathName);

            }
            ImGuiFileDialog::Instance()->Close();
            // AIAC_APP.GetLayer<AIAC::LayerSlam>()->StopMapping();
            // AIAC_APP.GetRenderer()->StopMapping();
            m_IsSavingMap = false;
        }
    }
    void LayerUI::ShowFileSelectDialog(const char* title, const char* fileExt, char *path, bool &controlFlag)
    {
        ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x * 0.8, ImGui::GetIO().DisplaySize.y * 0.75));
        ImGuiFileDialog::Instance()->OpenDialog("SelectFileDialog", title, fileExt, ".");
        if (ImGuiFileDialog::Instance()->Display("SelectFileDialog"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                // std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();

                AIAC_INFO("Select: {0}", filePathName.c_str());
                memset(path, 0, PATH_BUF_SIZE);
                memcpy(path, filePathName.c_str(), filePathName.length());
            }
            ImGuiFileDialog::Instance()->Close();
            controlFlag = false;
        }
    }
    
    // TODO: Replace this with ShowFileSelectDialog
    void LayerUI::ShowMapFileDialog(char *path)
    {
        ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x * 0.8, ImGui::GetIO().DisplaySize.y * 0.75));
        ImGuiFileDialog::Instance()->OpenDialog("ChooseMapPath", "Choose Map Path", ".map", ".");
        if (ImGuiFileDialog::Instance()->Display("ChooseMapPath"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();

                AIAC_INFO("Select: {0}", filePathName.c_str());
                memset(path, 0, PATH_BUF_SIZE);
                memcpy(path, filePathName.c_str(), filePathName.length());
            }
            ImGuiFileDialog::Instance()->Close();
            m_CombMapParams.IsSelectingFile = false;
        }
    }
    // void LayerUI::ShowReconExportFilePathDialog(){
    //     auto path = m_ReconstructParams.ExportPath;
    //     ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x * 0.8, ImGui::GetIO().DisplaySize.y * 0.75));
    //     ImGuiFileDialog::Instance()->OpenDialog("Choose Export Path", "Choose export ply path", ".ply", ".");
    //     if (ImGuiFileDialog::Instance()->Display("Choose Export Path"))
    //     {
    //         if (ImGuiFileDialog::Instance()->IsOk())
    //         {
    //             std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
    //             std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();

    //             AIAC_INFO("Select: {0}", filePathName.c_str());
    //             memset(path, 0, PATH_BUF_SIZE);
    //             memcpy(path, filePathName.c_str(), filePathName.length());
    //         }
    //         ImGuiFileDialog::Instance()->Close();
    //         m_ReconstructParams.IsSelectingExportPath = false;
    //     }
    // }
}