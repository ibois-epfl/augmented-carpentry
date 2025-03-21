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

#pragma once

#include "AIAC/Feedback/CutPlaneVisualizer.h"
#include "AIAC/Feedback/FeedbackVisualizer.h"
#include "AIAC/Feedback/FabFeedback.h"

#include <vector>

namespace AIAC
{
    /**
     * @brief This visualizer gives a bit of guidance on the cut orientation. Although it is not possible
     * to determine the exact orientation of the cut, this visualizer gives a rough idea of the pitch and roll.
     * The way this is done is by projecting the blade normal onto the face normal, and then projecting the
     * resulting vector onto the face normal. If we close the triangle of these two lines we can monitor the angle
     * that must be 45*. This way we can also have the direction towards which the blade needs to be tilted.
     *
    */
    class CutOrientationVisualizer : public FeedbackVisualizer
    {
        public:
            CutOrientationVisualizer();

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
        
        friend class CutChainSawFeedback;

    };

    class CutChainSawAngleFeedVisualizer : public FeedbackVisualizer
    {
        public:
            CutChainSawAngleFeedVisualizer();

        private:
            std::shared_ptr<GOLine> m_LineEnd;
            std::shared_ptr<GOLine> m_LineChainBase;
            std::shared_ptr<GOLine> m_LineChainEnd;

        friend class CutChainSawFeedback;
        };

        class CutChainSawDepthFeedVisualizer : public FeedbackVisualizer
        {
        public:
            CutChainSawDepthFeedVisualizer();

        private:
            std::shared_ptr<GOLine> m_LineIntersect;
            std::shared_ptr<GOLine> m_LineIntersectThickness;
            std::shared_ptr<GOLine> m_LineDepthFaceEdge1;
            std::shared_ptr<GOLine> m_LineDepthFaceEdge2;

        friend class CutChainSawFeedback;
    };

    class ChainSawCutPlaneVisualizer: public CutPlaneVisualizer
    {
        public:
            ChainSawCutPlaneVisualizer() = default;

        friend class CutChainSawFeedback;
        };

        class CutChainSawFeedVisualizer : public FeedbackVisualizer
        {
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

            std::shared_ptr<GOText> m_GuideTxtFaceEdgeDepth;

            ///< @brief This is the tolerance difference between the two depth line indicators of the chainsaw
            float m_DistDepthAcceptance = 0.0025f;

            friend class CutChainSawFeedback;
    };

    class CutChainSawFeedback : public FabFeedback
    {
        public:
            CutChainSawFeedback() = default;

            void Update() override;
            void Activate() override;
            void Deactivate() override;

            // FIXME: maybe we can have a "CutFeedback" class for such fuctions
            inline void EnableCutPlane(bool enable) { 
                m_ToShowCutPlane = enable;
                if(enable) m_CutPlaneVisualizer.Activate();
                else m_CutPlaneVisualizer.Deactivate();
            }

            /**
             * Manually select the reference face (the nearest parallel face)
             * @param scrollDirection when > 0, goes to next; <= 0, goes back.
             */
            void ManuallyScrollRefFace(int scrollDirection);

        public:
            // config exposed to UI
            bool IsRefFacesSelectedManually = false;

        private:
            void UpdateCutPlane();
            void UpdateRefFaces();

            glm::vec3 m_NormStart;
            glm::vec3 m_NormEnd;
            glm::vec3 m_NormalVec;
            glm::vec3 m_ChainBase;
            glm::vec3 m_ChainMid;
            glm::vec3 m_ChainEnd;

            bool m_ToShowCutPlane = false;

        private:
            TimberInfo::Cut* m_Cut;
            std::string m_NearestParallelFaceID;
            std::string m_NearestPerpendicularFaceID;

            CutChainSawFeedVisualizer m_Visualizer;
            ChainSawCutPlaneVisualizer m_CutPlaneVisualizer;
            CutOrientationVisualizer m_CutOrientationVisualizer;
    };
}