#pragma once

#include "AIAC/Layer.h"

#include "AIAC/Image.h"
#include "AIAC/Log.h"
#include "Config.h"

#include "tslam.h"
#include "GlHeader.h"
#include "AIAC/UI/ImGuiFileDialog.h"

#define PATH_BUF_SIZE 200

namespace AIAC {

    class PaneUI {
    public:
        typedef std::function<void()> Func;

        PaneUI(const char *label, bool isCollapsed, Func func)
                : m_Label(label), m_IsCollapsed(isCollapsed), m_func(std::move(func)) {}

        template<typename... Args>
        void Show(Args &&... args) {
            if (ImGui::CollapsingHeader(m_Label, m_IsCollapsed ? ImGuiTreeNodeFlags_DefaultOpen : 0)) {
                m_func(std::forward<Args>(args)...);
            }
        }

    private:
        Func m_func;
        const char *m_Label;
        bool m_IsCollapsed;
    };

    class LayerUI : public AIAC::Layer {
    public:
        LayerUI() = default;
        virtual ~LayerUI() = default;

        virtual void OnAttach() override;
        virtual void OnFrameStart() override;
        void OnUIRender();
        virtual void OnDetach() override;

        void ShowMenuBar();
        void ShowMainUI();
        void ShowSceneViewport();
        void ShowFileSelectDialog();
        void OpenFileSelectDialog(const char* title, const char* fileExt, char *path, std::function<void()> callback=[]{});

        void ShowCombineMapPopup();
        void ShowMappingPopup();
        void ShowSaveMapFileDialog();
        void ShowMapFileDialog(char *path);

        void ShowReconstruct3DPopup();
        void ShowReconExportFilePathDialog();

        void ShowCamCalibPopup();
        void ShowSaveCamCalibFileDialog();
        void LoadReconstructParams();
        void ShowSaveVideoRecorderFileDialog();

        void ShowLogRecorderUI();

        inline void StackPane(PaneUI pane) { m_PaneUIStack.push_back(std::make_shared<PaneUI>(pane)); }
        void SetPaneUICamera();
        void SetPaneUISlam();
        void SetPaneUIToolhead();
        void SetPaneUIACIM();
        void SetPaneUIUtils();

    private:
        void SetGlobalViewUI(ImVec2 viewportSize);

    private:
        AIAC::Image m_LogoBlack;
        AIAC::Image m_LogoLightClr;

        AIAC::ImTexture m_SceneViewportImTexture;
        AIAC::ImTexture m_MappingViewImTexture;
        AIAC::ImTexture m_CamCalibViewImTexture;
        AIAC::ImTexture m_ARCameraViewportImTexture;

        ImVec2 m_LastMouseLPos, m_LastMouseRPos;
        bool m_IsMouseLDown = false, m_IsMouseRDown = false;

        enum class AdjustTarget {
            SCALE,
            ROTATION,
            TRANSLATION
        } m_AdjustTarget = AdjustTarget::SCALE;

        bool *m_IsOpen = nullptr;

        std::vector<std::shared_ptr<PaneUI>> m_PaneUIStack;
        
        // UI File Selection
        std::string m_FileSelectDefaultPath = ".";
        char m_TmpPathBuf[PATH_BUF_SIZE] = {0};
        char *m_FileSelectionTargetBuf = nullptr;
        std::function<void()> m_FileSelectionCallback = []{};
        std::string m_VideoRecorderPathName;

        bool m_IsCombiningMap = false;
        bool m_IsReconstructing3D = false;

        struct CombineMapParams{
            char MapPathA[PATH_BUF_SIZE] = {0},
                 MapPathB[PATH_BUF_SIZE] = {0},
                 OutputPath[PATH_BUF_SIZE] = {0};
            char *FilePathTarget;
        } m_CombMapParams;

        struct MappingParams{
            bool ToOptimizeMap = true;
            bool ToSaveMap = true;
            char MapSavingPath[PATH_BUF_SIZE] = "./scanned_map/test.map";
        } m_MappingParams;
        
        struct ReconstructParams {
            char TagMapPath[PATH_BUF_SIZE] = {0};
            char ExportPath[PATH_BUF_SIZE] = {0};
            float RadiusSearch = 2.0f;
            double CreaseAngleThreshold = 5.0f;
            int MinClusterSize = 1;
            double AABBScaleFactor = 1.1f;
            double MaxPolyDist = 1.0f;
            double MaxPlnDist = 1.0f;
            double MaxPlnAngle = 5.0f;
            double Eps = 1e-5f;
        } m_ReconstructParams;
        void LoadReconstructParamsFromFile(const char *filePath);

        // Cam Calib
        bool m_IsChoosingCamCalibFileSavePath = false;
    };
}