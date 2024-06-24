#ifndef CUTBLADETHICKNESSVISUALIZER_H
#define CUTBLADETHICKNESSVISUALIZER_H

#include "FeedbackVisualizer.h"
#include "utils/GeometryUtils.h"

namespace AIAC
{
    class CutBladeThicknessVisualizer : public FeedbackVisualizer
    {
    public:
        CutBladeThicknessVisualizer();
        void Activate() override;
        void Deactivate() override;

        /**
         * @brief Update the intersection polyline and face, and return the intersection point
         * 
         * @param activeFaceInfo the current active FaceInfo
         */
        void Update(AIAC::TimberInfo::Cut::Face activeFaceInfo);

    private:
        /**
         * @brief Update the current toolhead's data: normalStart, normEnd and center, as well the thickness.
         * Since there could be multiple cutting toolheads (sawblade or chainsaw), we need
         * to get the correct toolhead's type.
         * 
         */
        void UpdateToolheadsData();

    protected:
        ///< @brief the thickness of the blade towards the camera
        std::shared_ptr<GOLine> m_LongestIntersectSegmentTowardsCamera;
        ///< @brief the thickness of the blade away from the camera
        std::shared_ptr<GOLine> m_LongestIntersectSegmentAwayFromCamera;
        ///< @brief the axis of the plane detected by ttool
        std::shared_ptr<GOLine> m_LongestIntersectSegmentTToolPlane;

        ///< @brief the scaled thickness of the blade towards the camera
        float bladeTotalThicknessScaled;
        ///< @brief the overhang distance of the blade's teeth from one side only
        float bladeOverhangScaled;

    private:
        ///< @brief the reference to the current toolhead's normal start
        glm::vec3 m_ToolheadRefNormStart;
        ///< @brief the reference to the current toolhead's normal end
        glm::vec3 m_ToolheadRefNormEnd;
        ///< @brief the reference to the current toolhead's center
        glm::vec3 m_ToolheadRefCenter;

        ///< @brief the unitize value of the normal
        glm::vec3 m_NormalUnitized;
        ///< @brief the opposite unitize value of the normal
        glm::vec3 m_NormalOppositeUnitized;
        ///< @brief the displaced center of the face towards the camera
        glm::vec3 m_DisplacedCenterTowardsCamera;
        ///< @brief the displaced center of the face away from the camera
        glm::vec3 m_DisplacedCenterAwayFromCamera;
    };
} // namespace AIAC
#endif // CUTBLADETHICKNESSVISUALIZER_H