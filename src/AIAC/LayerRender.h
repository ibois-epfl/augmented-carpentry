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
        virtual void OnUIRender() override;
    };
}