//
// Created by ibois on 7/28/23.
//

#ifndef AC_FABFEEDBACK_H
#define AC_FABFEEDBACK_H

#define AC_FF_COMP AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().GetCurrentComponent()
#define AC_FF_TOOL AIAC_APP.GetLayer<LayerToolhead>()->ACInfoToolheadManager->GetActiveToolhead()

namespace AIAC {
    class FabFeedback {
    public:
        virtual void Update();
        virtual void Activate();
        virtual void Deactivate();
    };

}

#endif //AC_FABFEEDBACK_H
