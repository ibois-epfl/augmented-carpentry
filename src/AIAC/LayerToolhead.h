#pragma once

#include "AIAC/Layer.h"
#include "ttool.hh"

namespace AIAC
{
    class LayerToolhead : public AIAC::Layer
    {
    public:
        LayerToolhead();
        virtual ~LayerToolhead() = default;

        virtual void OnAttach() override;
        virtual void OnFrameStart() override;
    };
}