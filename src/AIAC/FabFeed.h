#pragma once

#include "AIAC/ACInfoToolheadManager.h"
#include "AIAC/ACInfoToolhead.h"
#include "AIAC/ACInfoModel.h"

#define AC_FABFEED_COMP AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().GetCurrentComponent()
#define AC_FABFEED_TOOL AIAC_APP.GetLayer<LayerToolhead>()->ACInfoToolheadManager->GetActiveToolhead()

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