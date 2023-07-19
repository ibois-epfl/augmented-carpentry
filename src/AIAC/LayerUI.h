#pragma once

#include "AIAC/Layer.h"

#include "AIAC/Image.h"
#include "AIAC/Log.h"

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
        void ShowFileSelectDialog(const char* title, const char* fileExt, char *path, bool &controlFlag);

        void ShowCombineMapPopup();
        void ShowMappingPopup();
        void ShowSaveMapFileDialog();
        void ShowMapFileDialog(char *path);

        void ShowReconstruct3DPopup();
        void ShowReconExportFilePathDialog();

        void ShowCamCalibPopup();
        void ShowSaveCamCalibFileDialog();

        inline void StackPane(PaneUI pane) { m_PaneUIStack.push_back(std::make_shared<PaneUI>(pane)); }
        void SetPaneUICamera();
        void SetPaneUISlam();
        void SetPaneUIRender();
        void SetPaneUIToolhead();
        void SetPaneUIACIM();

    private:
        void SetGlobalViewUI(ImVec2 viewportSize);

    private:
        int m_testSlider = 0;

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

        bool m_IsSavingMap = false;
        bool m_IsCombiningMap = false;
        bool m_IsReconstructing3D = false;

        struct CombineMapParams{
            char MapPathA[PATH_BUF_SIZE] = {0},
                 MapPathB[PATH_BUF_SIZE] = {0},
                 OutputPath[PATH_BUF_SIZE] = {0};
            bool IsSelectingFile = false;
            char *FilePathTarget;
        } m_CombMapParams;

        struct MappingParams{
            bool ToOptimizeMap = true;
            bool ToSaveMap = true;
            char MapSavingPath[PATH_BUF_SIZE] = "/tmp/test.map";
        } m_MappingParams;
        
        struct ReconstructParams {
            char TagMapPath[PATH_BUF_SIZE] = {0};
            char ExportPath[PATH_BUF_SIZE] = {0};
            bool IsSelectingTagMapPath = false;
            bool IsSelectingExportPath = false;
            float RadiusSearch = 15.0f;
            double CreaseAngleThreshold = 50.0f;
            int MinClusterSize = 1;
            double AABBScaleFactor = 6.0f;
            double MaxPolyDist = 20.0f;
            double MaxPlnDist = 4.0f;
            double MaxPlnAngle = 45.0f;
            double Eps = 1e-5f;
        } m_ReconstructParams;

        // Cam Calib
        bool m_IsChoosingCamCalibFileSavePath = false;
    };
}