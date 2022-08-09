#pragma once

#include "AIAC/Layer.h"

namespace AIAC
{
    class LayerCamera : public AIAC::Layer
    {
    public:
        LayerCamera() = default;
        virtual ~LayerCamera() = default;

        virtual void OnAttach();
        virtual void OnFrameAwake() override;
        virtual void OnFrameStart() override;
        virtual void OnFrameEnd() override;
        virtual void OnUIRender() override;
        virtual void OnFrameFall() override;
        virtual void OnDetach() override;

        int test_a = 333;  // TEST
    };
}