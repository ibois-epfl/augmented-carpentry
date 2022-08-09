#pragma once

#include "AIAC/Layer.h"

namespace AIAC
{
    class LayerUI : public AIAC::Layer
    {
    public:
        LayerUI() = default;
        virtual ~LayerUI() = default;

        // virtual void OnAttach() override;
        virtual void OnUIRender() override;
        // virtual void OnDetach() override;
    };
}