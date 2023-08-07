//
// Created by ibois on 7/28/23.
//

#pragma once

#include "AIAC/Feedback/CutPlaneVisualizer.h"
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

    class ChainSawCutPlaneVisualizer: public CutPlaneVisualizer {
    public:
        ChainSawCutPlaneVisualizer() = default;

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

        void Update() override;
        void Activate() override;
        void Deactivate() override;

        // FIXME: maybe we can have a "CutFeedback" class for such fuctions
        void EnableCutPlane(bool enable) { m_ToShowCutPlane = enable; }
    
    private:
        void updateCutPlane();

        glm::vec3 m_NormStart;
        glm::vec3 m_NormEnd;
        glm::vec3 m_NormalVec;
        glm::vec3 m_ChainBase;
        glm::vec3 m_ChainMid;
        glm::vec3 m_ChainEnd;

        bool m_ToShowCutPlane = true;


    private:
        CutChainSawFeedVisualizer m_Visualizer;
        ChainSawCutPlaneVisualizer m_CutPlaneVisualizer;
    };
}