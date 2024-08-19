#pragma once

#include "AIAC/Layer.h"
#include "AIAC/ACInfoToolheadManager.h"
#include "AIAC/ACInfoToolhead.h"
#include "AIAC/ACInfoModel.h"
#include "AIAC/Feedback/CutChainSawFeedback.h"
#include "AIAC/Feedback/CutCircularSawFeedback.h"
#include "AIAC/Feedback/HoleFeedback.h"

namespace AIAC
{
    class LayerFeedback : public AIAC::Layer
    {
    public:
        LayerFeedback();
        virtual ~LayerFeedback() = default;

        virtual void OnAttach() override;
        virtual void OnFrameStart() override;

    public:
        bool ToShowCutPlane = false;
        void EnableCutPlane(bool enable)
        {
            ToShowCutPlane = enable;
            m_CutChainSawFeedback.EnableCutPlane(enable);
            m_CutCircularSawFeedback.EnableCutPlane(enable);
        };

        inline void DeactivateCurrentFeedbackVisibility() { m_IsCurrentFabFeedbackVisible = false; }
        inline void ActivateCurrentFeedbackVisibility() { m_IsCurrentFabFeedbackVisible = true; }

    private:
        HoleFeedback m_HoleFeedback;
        CutChainSawFeedback m_CutChainSawFeedback;
        CutCircularSawFeedback m_CutCircularSawFeedback;

        FabFeedback* m_CurrentFabFeedbackPtr = nullptr;
        bool m_IsCurrentFabFeedbackVisible = true;
    };
}