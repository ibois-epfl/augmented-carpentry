//
// Created by ibois on 7/28/23.
//

#ifndef AC_CUTCIRCULARSAWFEEDBACK_H
#define AC_CUTCIRCULARSAWFEEDBACK_H

#include "AIAC/GOSys/GOPrimitive.h"
#include "AIAC/ACInfoModel.h"
#include "FeedbackVisualizer.h"
#include "FabFeedback.h"
#include "utils/GeometryUtils.h"

namespace AIAC{
    class CutCircularSawFeedbackVisualizer : public FeedbackVisualizer {
    public:
        CutCircularSawFeedbackVisualizer();

    private:
        std::shared_ptr<GOLine> m_LineBottom;
        std::shared_ptr<GOLine> m_LineSide1;
        std::shared_ptr<GOLine> m_LineSide2;

    friend class CutCircularSawFeedback;
    };

    class CutCircularSawFeedback : public FabFeedback {
    public:
        CutCircularSawFeedback();

        void Update() override;
        void Activate() override;
        void Deactivate() override;
        
    private:
        float m_Radius;
        glm::vec3 m_Center;
        glm::vec3 m_Normal;
        glm::vec3 m_NormalStart;
        glm::vec3 m_NormalEnd;

        std:;string m_NearestParallelFaceID;
        std::string m_NearestPerpendicularFaceID;

        void updatePosition();
        void updateRefFaces();

        CutCircularSawFeedbackVisualizer m_Visualizer;
    };
}


#endif //AC_CUTCIRCULARSAWFEEDBACK_H
