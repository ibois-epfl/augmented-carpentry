#pragma once

// #include <TTool/ttool.hh>
#include "AIAC/Layer.h"
#include "ttool.hh"

namespace AIAC
{
    class LayerToolhead : public AIAC::Layer
    {
    public:
        LayerToolhead() {};
        virtual ~LayerToolhead() = default;

        virtual void OnAttach() override;
        virtual void OnFrameStart() override;

        bool NeedsContextReleased() const { return true; }
    
    protected:
        std::shared_ptr<ttool::TTool> ttool;
    };
}