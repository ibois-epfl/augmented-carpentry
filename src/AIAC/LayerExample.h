#pragma once

#include "AIAC/Layer.h"

namespace AIAC
{
    class LayerExample : public AIAC::Layer
    {
    public:
        LayerExample() = default;
        virtual ~LayerExample() = default;

        virtual void OnAttach() override;
        virtual void OnFrameAwake() override;
        virtual void OnFrameStart() override;
        virtual void OnFrameEnd() override;
        virtual void OnUIRender() override;
        virtual void OnFrameFall() override;
        virtual void OnDetach() override;
    };
}