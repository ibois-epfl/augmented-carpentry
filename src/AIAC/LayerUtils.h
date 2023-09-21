//
// Created by zholmaga on 11.09.23.
//

#pragma once
#pragma once

#include "AIAC/Layer.h"
#include "../utils/VideoRecorder.h"

namespace AIAC {

    class LayerUtils : public AIAC::Layer {
    public:


        virtual void OnFrameEnd() override;

    };

}

