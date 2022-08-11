#pragma once

#include "AIAC/Layer.h"

namespace AIAC
{
    class LayerRender : public AIAC::Layer
    {
    public:
        LayerRender() = default;
        virtual ~LayerRender() = default;

        void OnAttach() override;
        virtual void OnFrameAwake() override;
        virtual void OnFrameStart() override;
        virtual void OnFrameEnd() override;
        virtual void OnUIRender() override;
        virtual void OnFrameFall() override;
        virtual void OnDetach() override;
    };
}