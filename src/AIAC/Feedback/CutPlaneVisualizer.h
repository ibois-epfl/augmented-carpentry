#ifndef CUTPLANEVISUALIZER_H
#define CUTPLANEVISUALIZER_H

#include "FeedbackVisualizer.h"
#include "utils/GeometryUtils.h"

namespace AIAC{
    class CutPlaneVisualizer : public FeedbackVisualizer {
    public:
        CutPlaneVisualizer();
        void Activate() override;
        void Deactivate() override;

        /**
         * @brief Update the intersection polyline and face, and return the intersection point
         * 
         * @param faceNorm the normal of the face
         * @param facePt the point on the face
         * @return std::vector<glm::vec3> the intersection point of the bbox and the face
         */
        std::vector<glm::vec3> Update(glm::vec3 faceNorm, glm::vec3 facePt);

    protected:
        std::shared_ptr<GOLine> m_LongestIntersectSegmentAppCenter;
        std::shared_ptr<GOLine> m_LongestIntersectSegment1;
        std::shared_ptr<GOLine> m_LongestIntersectSegment2;
    };
}

#endif // CUTPLANEVISUALIZER_H