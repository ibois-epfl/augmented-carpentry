#include "aiacpch.h"

#include "AIAC/LayerUI.h"
#include "AIAC/Application.h"

#include "AIAC/Image.h"
#include "AIAC/Render/Renderer.h"

#include "AIAC/UI/ImGuiFileDialog.h"

#include "AIAC/UI/ClrPalette.h"
#include "AIAC/UI/CustomLogos.h"
#include "LayerCameraCalib.h"


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
        StackPane(PaneUI("Toolhead",     true,      AIAC_BIND_EVENT_FN(SetPaneUIToolhead)  ));

        // TODO: add config for file dialog widget
        //TODO: add vertical menu bar

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
                bool is_selected = (currentItem == devicePath);
                if (ImGui::Selectable(devicePath.c_str(), is_selected)){
                    AIAC_APP.GetLayer<LayerCamera>()->SetCurrentDevice(devicePath);
                }
                if (is_selected)
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

        ImGui::BeginChild("camera_function_child", ImVec2(0, 36), true, ImGuiWindowFlags_HorizontalScrollbar);
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

//        Image frame = AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetCurrentFrame();
//        AIAC::ImTexture frameImTexture = frame.GetImTexture(ImVec2(800, 480));
//        ImGui::Image(frameImTexture.ID, ImVec2(frame.GetImTexture().Size.x * 0.5f, frame.GetImTexture().Size.y * 0.5f));
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

//        ImGui::SameLine();
//        if (ImGui::Button("Open camera calib"))
//            ImGuiFileDialog::Instance()->OpenDialog("ChooseCameraCalib", "Open calib", ".yml", ".");
//
//        if (ImGuiFileDialog::Instance()->Display("ChooseCameraCalib"))
//        {
//            if (ImGuiFileDialog::Instance()->IsOk())
//            {
//            std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
//            AIAC_EBUS->EnqueueEvent(std::make_shared<CameraCalibrationLoadedEvent>(filePathName));
//            }
//            ImGuiFileDialog::Instance()->Close();
//        }

        ImGui::EndChild();

        ImGui::Text("Mapping Functions:");
        ImGui::BeginChild("mapping_function_child", ImVec2(0, 36), true, ImGuiWindowFlags_HorizontalScrollbar);
            if(ImGui::Button("Start Mapping")){
                AIAC_APP.GetLayer<AIAC::LayerSlam>()->StartMapping();
                AIAC_APP.GetRenderer()->StartMapping();
            }
            ImGui::SameLine();
            if(ImGui::Button("Combine Map")){
                m_IsCombiningMap = true;
            }
            ImGui::PopStyleColor();
        ImGui::EndChild();

        ImGui::Checkbox("Process Frames", &AIAC_APP.GetLayer<AIAC::LayerSlam>()->ToProcess);
        ImGui::Checkbox("Enhance Photo", &AIAC_APP.GetLayer<AIAC::LayerSlam>()->ToEnhance);

        ImGui::Text("Tracked: %s", AIAC_APP.GetLayer<AIAC::LayerSlam>()->IsTracked() ? "Yes" : "No");

        std::string camPoseStr; camPoseStr << AIAC_APP.GetLayer<AIAC::LayerSlam>()->GetCamPoseCv();
        ImGui::Text("Estimated Camera Pose: \n%s", camPoseStr.c_str());
    }

    void LayerUI::SetPaneUIRender()
    {
        ImGui::Checkbox("Point Cloud Map", &AIAC_APP.GetRenderer()->ShowPointCloudMap);
        ImGui::Checkbox("Digital Model", &AIAC_APP.GetRenderer()->ShowDigitalModel);
        if(ImGui::Button("Load Digital Model")){
            ImGuiFileDialog::Instance()->OpenDialog("ChooseDigitalModel", "Open Digital Model", ".ply", ".");
        }
        if (ImGuiFileDialog::Instance()->Display("ChooseDigitalModel"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                // TODO: Add ply to renderer
                AIAC_INFO("Loading Digital Model: {}", filePathName);
                AIAC_APP.GetRenderer()->Meshes.emplace_back(filePathName);
//                AIAC_EBUS->EnqueueEvent(std::make_shared<CameraCalibrationLoadedEvent>(filePathName));
            }
            ImGuiFileDialog::Instance()->Close();
        }

    }

    void LayerUI::SetPaneUIToolhead()
    {
        
        ImGui::PushID(0);
        ImGui::RadioButton("None", &AIAC_APP.GetLayer<AIAC::LayerToolhead>()->ToolheadStateUI, -1);
        ImGui::PopID();
        ImGui::SameLine();

        ImGui::PushID(1);
        ImGui::RadioButton("Track", &AIAC_APP.GetLayer<AIAC::LayerToolhead>()->ToolheadStateUI, 0);
        ImGui::PopID();
        ImGui::SameLine();
        
        ImGui::PushID(2);
        ImGui::RadioButton("Input Pose", &AIAC_APP.GetLayer<AIAC::LayerToolhead>()->ToolheadStateUI, 1);
        ImGui::PopID();
        // ImGui::Checkbox("Tracking", &AIAC_APP.GetLayer<AIAC::LayerToolhead>()->ToTrack);
        // ImGui::Checkbox("Tracking", &AIAC_APP.GetLayer<AIAC::LayerToolhead>()->ToTrack);
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
                    if(ImGui::Button("Exit")){
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
                std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();

                AIAC_INFO("Saving map to {0}", filePathName.c_str());
                AIAC_APP.GetLayer<AIAC::LayerSlam>()->Slam.getMap()->saveToFile(filePathName);

            }
            ImGuiFileDialog::Instance()->Close();
            m_IsSavingMap = false;
        }
    }
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


}