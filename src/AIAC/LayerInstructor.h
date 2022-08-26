#pragma once

#include "AIAC/Layer.h"


namespace AIAC
{
    class LayerInstructor : public AIAC::Layer
    {
    public:
        LayerInstructor();
        virtual ~LayerInstructor() = default;

        virtual void OnAttach() override;
        virtual void OnFrameStart() override;
    };
}