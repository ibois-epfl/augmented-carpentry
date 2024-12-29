// #####################################################################
// >>>>>>>>>>>>>>>>>>>>> BEGINNING OF LEGAL NOTICE >>>>>>>>>>>>>>>>>>>>>
//######################################################################
//
// This source file, along with its associated content, was authored by
// Andrea Settimi, Hong-Bin Yang, Naravich Chutisilp, and numerous other
// contributors. The code was originally developed at the Laboratory for
// Timber Construction (IBOIS, director: Prof. Yves Weinand) at the School of 
// Architecture, Civil and Environmental Engineering (ENAC) at the Swiss
// Federal Institute of Technology in Lausanne (EPFL) for the Doctoral
// Research "Augmented Carpentry" (PhD researcher: Andrea Settimi,
// co-director: Dr. Julien Gamerro, director: Prof. Yves Weinand).
//
// Although the entire repository is distributed under the GPL license,
// these particular source files may also be used under the terms of the
// MIT license. By accessing or using this file, you agree to the following:
//
// 1. You may reproduce, modify, and distribute this file in accordance
//    with the terms of the MIT license.
// 2. You must retain this legal notice in all copies or substantial
//    portions of this file.
// 3. This file is provided "AS IS," without any express or implied
//    warranties, including but not limited to the implied warranties of
//    merchantability and fitness for a particular purpose.
//
// If you cannot or will not comply with the above conditions, you are
// not permitted to use this file. By proceeding, you acknowledge and
// accept all terms and conditions herein.
//
//######################################################################
// <<<<<<<<<<<<<<<<<<<<<<< END OF LEGAL NOTICE <<<<<<<<<<<<<<<<<<<<<<<<
// #####################################################################
//
#ifndef CUTBLADETHICKNESSVISUALIZER_H
#define CUTBLADETHICKNESSVISUALIZER_H

#include "FeedbackVisualizer.h"
#include "utils/GeometryUtils.h"
#include "AIAC/ACInfoModel.h"

namespace AIAC
{
    /**
     * @brief The idea behind the CutBladeThicknessVisualizer is to give a visual feedback on the thickness of the blade.
     * We do this by intersecting the two neighbours faces of the current highlighted face.
     * 
     */
    class CutBladeThicknessVisualizer : public FeedbackVisualizer
    {
    public:
        CutBladeThicknessVisualizer();

    protected:
        /**
         * @brief Update the current toolhead's data: normalStart, normEnd and center, as well the thickness.
         * Since there could be multiple cutting toolheads (sawblade or chainsaw), we need
         * to get the correct toolhead's type.
         * 
         */
        virtual void UpdateToolheadsData() = 0;

        /**
         * @brief This function intersect the plane of the blade with the two(or one) neighbour faces.
         * 
         * @param cut the TimberInfo::Cut object
         * @param face the face belonging to the cut to intersect with
         * @param isTowardsCamera the boolean to indicate if we intersect the blade's edge close to the camera
         * @param isDetectToolPlane the intersection is for the reference toolhead's plane
         * @param lineIntersection the reference to the line intersection
         * 
         * @return bool true if the intersection is successful, false otherwise
         */
        virtual bool IntersectBladeWithNeighbours(
            AIAC::TimberInfo::Cut* cut, 
            AIAC::TimberInfo::Cut::Face& face,
            bool isTowardsCamera,
            bool isDetectToolPlane,
            std::shared_ptr<GOLine>& lineIntersection) = 0;

    public:
        ///< @brief if the segment of the detected blade is visible
        bool IsSegmenDetectToolPlaneVisible = false;

    protected:
        ///< @brief the segment where the blade is detected by the toolhead
        std::shared_ptr<GOLine> m_LongestIntersectSegmenDetectToolPlane;
        ///< @brief the thickness of the blade towards the camera on first neighbour side
        std::shared_ptr<GOLine> m_LongestIntersectSegmentTowardsCameraA;
        ///< @brief the thickness of the blade towards the camera on second neighbour side
        std::shared_ptr<GOLine> m_LongestIntersectSegmentTowardsCameraB;
        ///< @brief the thickness A of the blade away from the camera on first neighbour side
        std::shared_ptr<GOLine> m_LongestIntersectSegmentAwayFromCameraA;
        ///< @brief the thickness A of the blade away from the camera on second neighbour side
        std::shared_ptr<GOLine> m_LongestIntersectSegmentAwayFromCameraB;

        ///< @brief the scaled thickness of the blade towards the camera
        float m_BladeTotalThicknessScaled;
        ///< @brief the overhang distance of the blade's teeth from one side only
        float m_BladeOverhangScaled;

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