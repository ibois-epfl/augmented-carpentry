#pragma once

#include "AIAC/Layer.h"
#include "AIAC/ACInfoToolheadManager.h"
#include "AIAC/ACInfoToolhead.h"
#include "AIAC/ACInfoModel.h"
#include "AIAC/Feedback/CutChainSawFeedback.h"

namespace AIAC
{
    class LayerFeedback : public AIAC::Layer
    {
        public:
            LayerFeedback();
            virtual ~LayerFeedback() = default;

            virtual void OnAttach() override;
            virtual void OnFrameStart() override;


        private:  ///< IN
            // FabFeed m_FabFeed;
            // ACInfoModel& m_CurrentModel; I need the current component / not model
            CutChainSawFeedback m_CutChainSawFeedback;

        // private:  ///< OUT


    };
}