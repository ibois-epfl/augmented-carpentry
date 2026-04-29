

# File LayerUI.h

[**File List**](files.md) **>** [**AIAC**](dir_21da83368f7816722f2b707a7b03c84f.md) **>** [**LayerUI.h**](LayerUI_8h.md)

[Go to the documentation of this file](LayerUI_8h.md)


```C++
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
#pragma once

#include <utility>

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
        enum CollapseState {
            OPEN,
            ON_COLLAPSING,
            COLLAPSE
        };

        typedef std::function<void()> Func;

        PaneUI(const char *label, bool isCollapsed, Func func, Func onCollapseCallback=[]{})
                : m_Label(label), m_IsCollapsed(isCollapsed), m_func(std::move(func)), m_onCollapseCallback(std::move(onCollapseCallback)) {
            if (m_IsCollapsed) m_CollapseState = CollapseState::COLLAPSE;
            else m_CollapseState = CollapseState::OPEN;
        }

        template<typename... Args>
        void Show(Args &&... args);

        template<typename... Args>
        void CheckOnCollapsing(Args &&... args);

    private:
        CollapseState m_CollapseState;
        Func m_func;
        Func m_onCollapseCallback;
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

        inline void StackPane(PaneUI pane) { m_PaneUIStack.emplace_back(std::move(pane)); }
        void SetPaneUICamera();
        void SetPaneUISlam();
        void SetPaneUIToolhead();
        void OnCollapsingPaneUIToolhead();
        void SetPaneUIACIM();
        void SetPaneUIUtils();
        PaneUI* GetOpenedPaneUI() { return m_OpenedPaneUI; }
        void SetOpenedPaneUI(PaneUI* paneUI) { m_OpenedPaneUI = paneUI; }

    private:
        void SetGlobalViewUI(ImVec2 viewportSize);

    private:
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

        std::vector<PaneUI> m_PaneUIStack;
        PaneUI* m_OpenedPaneUI = nullptr;
        
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
```


