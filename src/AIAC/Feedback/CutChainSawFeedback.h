//
// Created by ibois on 7/28/23.
//

#pragma once

#include "AIAC/Feedback/FeedbackVisualizer.h"
#include "AIAC/Feedback/FabFeedback.h"

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
        CutChainSawFeedback() = default;

        virtual void Update();
        virtual void Activate();
        virtual void Deactivate();
    private:
        CutChainSawFeedVisualizer m_Visualizer;
    };
}