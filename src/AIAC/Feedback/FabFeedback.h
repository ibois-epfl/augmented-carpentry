#pragma once

#define AC_FF_COMP AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().GetCurrentComponent()
#define AC_FF_TOOL AIAC_APP.GetLayer<LayerToolhead>()->ACInfoToolheadManager->GetActiveToolhead()

namespace AIAC {
    class FabFeedback {
    public:
        FabFeedback() = default;
        ~FabFeedback() = default;

        virtual void Update() {};
        virtual void Activate() {};
        virtual void Deactivate() {};
    };
}