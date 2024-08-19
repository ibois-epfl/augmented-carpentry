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

    private:  ///< utility
        /**
         * @brief Reorder the intersections so that we obtain a romboid with the correct order of points¨
         * 
         * @param intersections the reference to the intersections to reorder
         * @param facePt the point on the face
         * 
         */
        void ReorderIntersectPoints(std::vector<glm::vec3>& intersectPts, const glm::vec3& facePt);


    protected:
        ///< @brief the intersection of the top plane of the blade from the closest side to the center of the blade
        std::shared_ptr<GOLine> m_LongestIntersectSegmentAppCenterA;
        ///< @brief the intersection of the top plane of the blade from the second closest side to the center of the blade
        std::shared_ptr<GOLine> m_LongestIntersectSegmentAppCenterB;
        ///< @brief the intersection line of the blade indicating the thickness towards the camera
        std::shared_ptr<GOLine> m_LongestIntersectSegmentA1;
        ///< @brief the intersection line of the blade indicating the thickness away from the camera
        std::shared_ptr<GOLine> m_LongestIntersectSegmentA2;
        ///< @brief the intersection line of the blade indicating the thickness towards the camera
        std::shared_ptr<GOLine> m_LongestIntersectSegmentB1;
        ///< @brief the intersection line of the blade indicating the thickness away from the camera
        std::shared_ptr<GOLine> m_LongestIntersectSegmentB2;
    };
}

#endif // CUTPLANEVISUALIZER_H