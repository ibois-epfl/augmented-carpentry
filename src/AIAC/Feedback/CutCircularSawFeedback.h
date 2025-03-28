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

#ifndef AC_CUTCIRCULARSAWFEEDBACK_H
#define AC_CUTCIRCULARSAWFEEDBACK_H

#include "AIAC/GOSys/GOPrimitive.h"
#include "AIAC/ACInfoModel.h"
#include "FeedbackVisualizer.h"
#include "CutPlaneVisualizer.h"
#include "CutBladeThicknessVisualizer.h"
#include "FabFeedback.h"
#include "utils/GeometryUtils.h"

namespace AIAC
{
    /**
     * @brief Visualizer for showing the depth of the cut.
     * 
     */
    class CutCircularSawDepthVisualizer : public FeedbackVisualizer
    {
    public:
        CutCircularSawDepthVisualizer();

    private:
        std::shared_ptr<GOLine> m_LineDepth;
        std::shared_ptr<GOPoint> m_PtBlade2ThicknessLineA;
        std::shared_ptr<GOPoint> m_PtBlade2ThicknessLineB;
        std::shared_ptr<GOText> m_TxtDepth;
        float m_ToleranceDepthThreshold = 0.1f;



    friend class CutCircularSawFeedback;
    };
    
    /**
     * @brief This visualizer gives guidance on the start position of the lateral cuts for the circular saw.
    */
    class CutCircularSawPositionStartVisualizer : public FeedbackVisualizer
    {
        public:
            CutCircularSawPositionStartVisualizer();

        private:
            std::shared_ptr<GOLine> m_LineDistStart;
            std::shared_ptr<GOText> m_TxtDistStart;
            std::shared_ptr<GOLine> m_LineToBottomPt;

        public:
            float ToleranceStartThreshold = 0.2f;

        friend class CutCircularSawFeedback;
    };

    /**
     * @brief This visualizer ggdb  ives a bit of guidance on the cut orientation. Although it is not possible
     * to determine the exact orientation of the cut, this visualizer gives a rough idea of the pitch and roll.
     * The way this is done is by projecting the blade normal onto the face normal, and then projecting the
     * resulting vector onto the face normal. If we close the triangle of these two lines we can monitor the angle
     * that must be 45*. This way we can also have the direction towards which the blade needs to be tilted.
     *
    */
    class CutCircularOrientationVisualizer : public FeedbackVisualizer
    {
        public:
            CutCircularOrientationVisualizer();

        private:
            std::shared_ptr<GOLine> m_LineFaceNormal;  // BLUE (face_z)
            std::shared_ptr<GOLine> m_LineBladeNormal;  // MAGENTA

            std::shared_ptr<GOLine> m_LineDebugA;  // ORANGE
            std::shared_ptr<GOLine> m_LineDebugB;  // GREEN (face_y)
            std::shared_ptr<GOLine> m_LineDebugC;  // RED (face_x)
            std::shared_ptr<GOLine> m_LineDebugD;  // YELLOW
            std::shared_ptr<GOLine> m_LineDebugE;  // WHITE

            std::shared_ptr<GOLine> m_LinePitchFeed;  // RED or MAGENTA

            std::shared_ptr<GOText> m_GuideTxtRollPitch;  // WHITE

        private:
            /// @brief The angle acceptance for the cut orientation, under this value is conside correct
            float m_tolAangleAcceptance = 0.4f;  // decimal fraction of a degree
        
        friend class CutCircularSawFeedback;
    };

    class CircularSawCutPlaneVisualizer : public CutPlaneVisualizer
    {
    public:
        CircularSawCutPlaneVisualizer() = default;

    friend class CutCircularSawFeedback;
    };

    /**
     * @brief This is an inherited class to show the thickness of the blade
     * on circular saws.
     * 
     */
    class CircularSawCutBladeThicknessVisualizer : public CutBladeThicknessVisualizer
    {
    public:
        CircularSawCutBladeThicknessVisualizer() = default;

    public:
        void UpdateToolheadsData() override;
        bool IntersectBladeWithNeighbours(
            TimberInfo::Cut* cut,
            TimberInfo::Cut::Face& face,
            bool isTowardsCamera,
            bool isDetectToolPlane,
            std::shared_ptr<GOLine>& lineIntersection) override;

    friend class CutCircularSawFeedback;
    };

    class CutCircularSawFeedback : public FabFeedback
    {
    public:
        CutCircularSawFeedback() = default;
        ~CutCircularSawFeedback() = default;

        void Update() override;
        void Activate() override;
        void Deactivate() override;

        inline void EnableCutPlane(bool enable) {
            m_ToShowCutPlane = enable;
            if(enable) m_CutPlaneVisualizer.Activate();
            else m_CutPlaneVisualizer.Deactivate();
        };

        /**
         * Manually select the reference face (the nearest parallel face)
         * @param scrollDirection when > 0, goes to next; <= 0, goes back.
         */
        void ManuallyScrollRefFace(int scrollDirection);

    public:
        // config exposed to UI
        bool IsRefFacesSelectedManually = false;
        
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

    private:  ///< @brief the important faces
        ///< @brief the face that is going to be updated
        std::string m_NearestParallelFaceID;
        ///< @brief the closest neighbour face to the highlighted face and to the blade
        std::string m_NearestNeighbourFaceIDToParallelFace;
        ///< @brief the second closest neighbour face to the highlighted face and to the blade
        std::string m_SecondNearestNeighbourFaceIDToParallelFace;

        // config
        bool m_ToShowCutPlane = false;

    private:
        void UpdateToolPosition();
        void UpdateRefFaces();

        void UpdateFeedback();
        /**
        * @brief The "General" situation means that we have a perpendicular face that served as 
        * the "bottom" face, where the bottom of the saw blade should be placed on. Therefore, the
        * m_DownVec, which indicate the direction from the center to the bottom of the saw blade,
        * is calculated based on the perpendicular face.
        * 
        */
        void UpdateOrientationFeedback();
        void UpdateCutPlaneFeedback();
        void UpdateThicknessFeedback();
        void UpdateStartPosFeedback();
        void UpdateDepthFeedback();

        CircularSawCutPlaneVisualizer m_CutPlaneVisualizer;
        CutCircularOrientationVisualizer m_OrientationVisualizer;
        CutCircularSawPositionStartVisualizer m_PositionStartVisualizer;
        CircularSawCutBladeThicknessVisualizer m_ThicknessVisualizer;
        CutCircularSawDepthVisualizer m_DepthVisualizer;
    };
}
#endif //AC_CUTCIRCULARSAWFEEDBACK_H
