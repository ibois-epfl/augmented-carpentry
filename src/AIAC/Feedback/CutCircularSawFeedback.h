//
// Created by ibois on 7/28/23.
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
     * @brief This visualizer gives guidance on the start position of the lateral cuts for the circular saw.
    */
    class CutCircularSawPositionStartVisualizer : public FeedbackVisualizer
    {
        public:
            CutCircularSawPositionStartVisualizer();

        private:
            std::shared_ptr<GOLine> m_LineDistStart;
            std::shared_ptr<GOText> m_TxtDistStart;

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

    class CutCircularSawFeedbackVisualizer : public FeedbackVisualizer
    {
    public:
        CutCircularSawFeedbackVisualizer();

    private:
        std::shared_ptr<GOPoint> m_BottomPoint;
        std::shared_ptr<GOLine> m_LineToBottomPt;
        std::shared_ptr<GOLine> m_ProjLineOnFace;
        std::shared_ptr<GOLine> m_ProjLineOnFaceThickness;
        std::shared_ptr<GOLine> m_ProjLineOfBlade;

        std::shared_ptr<GOText> m_TxtBottomDist;

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

        // config
        bool m_ToShowCutPlane = true;

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
        void UpdateGeneralFeedback();
        void UpdateCutPlaneFeedback();
        void UpdateThicknessFeedback();

        CutCircularSawFeedbackVisualizer m_GeneralVisualizer;
        CircularSawCutPlaneVisualizer m_CutPlaneVisualizer;
        CutCircularOrientationVisualizer m_OrientationVisualizer;
        CutCircularSawPositionStartVisualizer m_PositionStartVisualizer;
        CircularSawCutBladeThicknessVisualizer m_ThicknessVisualizer;
    };
}


#endif //AC_CUTCIRCULARSAWFEEDBACK_H
