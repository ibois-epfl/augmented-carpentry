#pragma once

#include "AIAC/Layer.h"


namespace AIAC
{
    class LayerFeedback : public AIAC::Layer
    {
    public:
        LayerFeedback();
        virtual ~LayerFeedback() = default;

        virtual void OnAttach() override;
        virtual void OnFrameStart() override;
    };
}