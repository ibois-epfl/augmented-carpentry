#pragma once

#include "AIAC/Config.h"

#define AC_FF_COMP AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().GetCurrentComponent()
#define AC_FF_TOOL AIAC_APP.GetLayer<LayerToolhead>()->ACInfoToolheadManager->GetActiveToolhead()

namespace AIAC {
    class FabFeedback {
    public:
        FabFeedback() {
            this->m_ScaleFactor = AIAC::Config::Get<float>(AIAC::Config::SEC_AIAC, AIAC::Config::SCALE_FACTOR, 1.0f);
        };
        ~FabFeedback() = default;

        virtual void Update() {};
        virtual void Activate() {};
        virtual void Deactivate() {};
    
    protected:
        float m_ScaleFactor = 0.0f;
    };
}