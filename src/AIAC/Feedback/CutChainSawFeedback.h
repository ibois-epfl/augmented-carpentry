//
// Created by ibois on 7/28/23.
//

#ifndef AC_CUTCHAINSAWFEEDBACK_H
#define AC_CUTCHAINSAWFEEDBACK_H

#include "AIAC/GOSys/GOPrimitive.h"
#include "AIAC/ACInfoModel.h"
#include "FeedbackVisualizer.h"
#include "FabFeedback.h"
#include "utils/GeometryUtils.h"

#include <vector>

namespace AIAC {
    class CutChainSawAngleFeedVisualizer : public FeedbackVisualizer {
    public:
        CutChainSawAngleFeedVisualizer();

    private:
        std::shared_ptr<GOLine> m_LineEnd;
        std::shared_ptr<GOLine> m_LineChainBase;
        std::shared_ptr<GOLine> m_LineChainEnd;

    friend class CutChainSawFeedback;
    };

    class CutChainSawDepthFeedVisualizer : public FeedbackVisualizer {
    public:
        CutChainSawDepthFeedVisualizer();

    private:
        std::shared_ptr<GOLine> m_LineIntersect;
        std::shared_ptr<GOLine> m_LineDepthFaceEdge1;
        std::shared_ptr<GOLine> m_LineDepthFaceEdge2;

    friend class CutChainSawFeedback;
    };

    class CutChainSawFeedVisualizer : public FeedbackVisualizer {
    public:
        CutChainSawFeedVisualizer();

        CutChainSawAngleFeedVisualizer& GetAngleFeedVisualizer() { return m_AngleFeedVisualizer; }
        CutChainSawDepthFeedVisualizer& GetDepthFeedVisualizer() { return m_DepthFeedVisualizer; }

    private:
        CutChainSawAngleFeedVisualizer m_AngleFeedVisualizer;
        CutChainSawDepthFeedVisualizer m_DepthFeedVisualizer;

        std::shared_ptr<GOText> m_GuideTxtEnd;
        std::shared_ptr<GOText> m_GuideTxtChainBase;
        std::shared_ptr<GOText> m_GuideTxtChainEnd;

        std::shared_ptr<GOText> m_GuideTxtFaceEdgeDepth1;
        std::shared_ptr<GOText> m_GuideTxtFaceEdgeDepth2;

        friend class CutChainSawFeedback;
    };

    class CutChainSawFeedback : public FabFeedback {
    public:
        FabFeedback() = default;
        virtual void Update();
        virtual void Activate();
        virtual void Deactivate();
    private:
        CutChainSawFeedVisualizer m_Visualizer;
    };
}

#endif //AC_CUTCHAINSAWFEEDBACK_H
