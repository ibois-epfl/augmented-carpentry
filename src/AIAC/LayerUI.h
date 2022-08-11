#pragma once

#include <opencv2/opencv.hpp>

#include "AIAC/Layer.h"

#include "GlHeader.h"


namespace AIAC
{
    class LayerUI : public AIAC::Layer
    {
    public:
        LayerUI() = default;
        virtual ~LayerUI() = default;

        virtual void OnAttach() override;
        virtual void OnFrameStart() override;
        virtual void OnUIRender() override;
        virtual void OnFrameEnd() override;
        virtual void OnFrameFall() override;
        virtual void OnDetach() override;
    
    private:
        ImVec4 m_WindowBackColor;

    };
}