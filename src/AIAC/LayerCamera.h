#pragma once

#include "AIAC/Layer.h"
#include "AIAC/Image.h"
#include "AIAC/Camera.h"

namespace AIAC
{
    class LayerCamera : public AIAC::Layer
    {
    public:
        LayerCamera() = default;
        virtual ~LayerCamera() = default;

        virtual void OnAttach() override;
        virtual void OnFrameStart() override;

        // const AIAC::Image GetCurrentFrame() { return m_CurrentFrame; }

    public:
        AIAC::Camera MainCamera;

    // private:
    //     AIAC::Image m_CurrentFrame;
    };
}