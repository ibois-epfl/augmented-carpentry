//
// Created by ibois on 7/28/23.
//

#ifndef AC_CUTCIRCULARSAWFEEDBACK_H
#define AC_CUTCIRCULARSAWFEEDBACK_H

#include "AIAC/GOSys/GOPrimitive.h"
#include "AIAC/ACInfoModel.h"
#include "FeedbackVisualizer.h"
#include "CutPlaneVisualizer.h"
#include "FabFeedback.h"
#include "utils/GeometryUtils.h"

namespace AIAC{
    class CutCircularSawFeedbackVisualizer : public FeedbackVisualizer {
    public:
        CutCircularSawFeedbackVisualizer();

    private:
        std::shared_ptr<GOPoint> m_BottomPoint;
        std::shared_ptr<GOLine> m_LineToBottomPt;
        std::shared_ptr<GOLine> m_ProjLineOnFace;
        std::shared_ptr<GOLine> m_ProjLineOfBlade;

        std::shared_ptr<GOText> m_TxtBottomDist;

    friend class CutCircularSawFeedback;
    };

    class CircularSawCutPlaneVisualizer : public CutPlaneVisualizer {
    public:
        CircularSawCutPlaneVisualizer() = default;

    friend class CutCircularSawFeedback;
    };

    class CutCircularSawFeedback : public FabFeedback {
    public:
        CutCircularSawFeedback() = default;
        ~CutCircularSawFeedback() = default;

        void Update() override;
        void Activate() override;
        void Deactivate() override;
        
    private:
        // data
        TimberInfo::Cut* m_Cut;
        float m_Radius;
        glm::vec3 m_Center;
        glm::vec3 m_NormalStart;
        glm::vec3 m_NormalEnd;

        // derived
        glm::vec3 m_Normal;
        glm::vec3 m_DownVec;
        glm::vec3 m_BottomPoint;

        std::string m_NearestParallelFaceID;
        std::string m_NearestPerpendicularFaceID;

        void updateToolPosition();
        void updateRefFaces();
        void updateFeedback();
        void updateGeneralFeedback();
        void updateCutPlaneFeedback();

        CutCircularSawFeedbackVisualizer m_GeneralVisualizer;
        CircularSawCutPlaneVisualizer m_CutPlaneVisualizer;
    };
}


#endif //AC_CUTCIRCULARSAWFEEDBACK_H
