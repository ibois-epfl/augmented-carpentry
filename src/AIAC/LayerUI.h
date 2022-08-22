#pragma once

#include "AIAC/Layer.h"

#include "AIAC/Image.h"
#include "AIAC/Log.h"

#include "GlHeader.h"
#include "AIAC/UI/ImGuiFileDialog.h"



namespace AIAC {

    
    class PaneUI
    {
    public:
        typedef std::function<void()> Func;

        PaneUI( const char* label, bool isCollapsed, Func func)
            : m_Label(label), m_IsCollapsed(isCollapsed), m_func( std::move(func) )
            {}

        template< typename... Args > void Show(Args &&... args)
        {
            if(ImGui::CollapsingHeader(m_Label, m_IsCollapsed ? ImGuiTreeNodeFlags_DefaultOpen : 0 ))
            {
                m_func( std::forward<Args>(args)... );
            }
        }

    private:
        Func m_func;
        const char* m_Label;
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
        void ShowSceneViewport();  //TODO: set fix camera in 3d scene and pass buffer

        inline void StackPane(PaneUI pane) { m_PaneUIStack.push_back(std::make_shared<PaneUI>(pane)); }
        static void SetPaneUICamera();
        static void SetPaneUISlam();
        static void SetPaneUIRender();
    
    private:
        int m_testSlider = 0;

        AIAC::Image m_LogoBlack;
        AIAC::Image m_LogoLightGray;

        AIAC::ImTexture m_SceneViewportImTexture;
        AIAC::ImTexture m_ARCameraViewportImTexture;

        bool* m_IsOpen = nullptr;

        std::vector<std::shared_ptr<PaneUI>> m_PaneUIStack;


    };
}