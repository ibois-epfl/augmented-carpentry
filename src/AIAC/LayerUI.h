#pragma once

#include <memory>
#include <opencv2/opencv.hpp>

#include "AIAC/Layer.h"

#include "AIAC/Image.h"
#include "AIAC/Log.h"

#include "GlHeader.h"

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
        virtual void OnUIRender() override;
        virtual void OnDetach() override;

        void ShowIntroUI();

        inline void StackPane(PaneUI pane) { m_PaneUIStack.push_back(std::make_shared<PaneUI>(pane)); }
        static void SetPaneUIExample();
        static void SetPaneUICamera();
        static void SetPaneUISlam();



    private:
        ImVec4 m_WindowBackColor;
        AIAC::Image m_Logo;

        bool* m_IsOpen = nullptr;

        // make a vector of PaneUI objects
        std::vector<std::shared_ptr<PaneUI>> m_PaneUIStack;

        // std::vector<std::shared_ptr<PaneUI<std::function<void()>>>> m_PaneUIs;
    };
}