#pragma once

#include "AIAC/ACInfoToolheadManager.h"
#include "AIAC/ACInfoToolhead.h"
#include "AIAC/ACInfoModel.h"

///< timber components
#define AC_FF_COMP AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().GetCurrentComponent()
// #define AC_FF_HOLE dynamic_cast<TimberInfo::Hole*>(AC_FF_COMP)
///< toolhead
#define AC_FF_TOOL AIAC_APP.GetLayer<LayerToolhead>()->ACInfoToolheadManager->GetActiveToolhead()
// #define AC_FF_TOOL_DRILLBIT_D AC_FF_TOOL->GetData<DrillBitData>()
// #define AC_FF_TOOL_CIRCULARSAW_D AC_FF_TOOL->GetData<CircularSawData>()
// #define AC_FF_TOOL_SABERSAW_D AC_FF_TOOL->GetData<SaberSawData>()
// #define AC_FF_TOOL_CHAINSAW_D AC_FF_TOOL->GetData<ChainSawData>()

namespace AIAC
{
    class FabFeed
    {
        public:
            FabFeed()
            {
                
            };

        public:
            /**
             * @brief The main function to produce the feedback based on the current toolhead and 
             *        model component (hole or cut).
             * 
             * @return true if the feedback is produced
             */
            bool Compute();
            bool ComputeHoleFeed();
            bool ComputeCutSaberSawFeed();
            bool ComputeCutChainSawFeed();
            bool ComputeCutCircularSawFeed();

        private:


        // private:
        //     std::shared_ptr<ACInfoToolhead> m_CurrentToolhead;
        //     std::shared_ptr<ACInfoModel> m_CurrentModel;
    };
}