#pragma once

#include "AIAC/Layer.h"

namespace AIAC
{
    class ExampleLayer : public AIAC::Layer
    {
    public:
        virtual void OnAttach() override {}
        virtual void OnFrameAwake() override {}
        virtual void OnFrameStart() override {}
        virtual void OnFrameEnd() override {}
        virtual void OnUIRender() override {}
        virtual void OnFrameFall() override {}
        virtual void OnDetach() override {}
    };
}