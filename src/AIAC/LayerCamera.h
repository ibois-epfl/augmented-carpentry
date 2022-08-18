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

    public:
        AIAC::Camera MainCamera;
    };
}