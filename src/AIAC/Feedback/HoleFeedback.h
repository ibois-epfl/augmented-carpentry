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
#ifndef AC_HOLEFEEDBACK_H
#define AC_HOLEFEEDBACK_H

#include "AIAC/GOSys/GOPrimitive.h"
#include "AIAC/ACInfoModel.h"
#include "FeedbackVisualizer.h"
#include "FabFeedback.h"
#include "utils/GeometryUtils.h"

namespace AIAC
{
    /**
        @brief The general visualizer for the info displayed as text
    */
    class HoleFeedbackText : public FeedbackVisualizer
    {
    public:
        HoleFeedbackText();

    private:
        // @brief text visualized for numeric values of start, orientation and depth
        std::shared_ptr<GOText> m_InfoText;

    friend class HoleFeedback;
    };

    /**
        @brief The UI widget for providing feedback on position
    */
    class HoleFeedbackPosition : public FeedbackVisualizer
    {
    public:
        HoleFeedbackPosition();

    private:
        /// @brief the line from the drillbit tip to the end of the hole
        std::shared_ptr<GOLine> m_HoleLine2ToolEnd;
        std::shared_ptr<GOPoint> m_HoleLine2ToolEnd_A;
        std::shared_ptr<GOPoint> m_HoleLine2ToolEnd_B;
        /// @brief the line from the drillbit tip to the start of the hole (aka start distance)
        std::shared_ptr<GOLine> m_HoleLine2ToolStart;
        std::shared_ptr<GOPoint> m_HoleLine2ToolStart_A;
        std::shared_ptr<GOPoint> m_HoleLine2ToolStart_B;

    friend class HoleFeedback;
    };

    /**
        @brief The UI widget for providing feedback on rotation
    */
    class HoleFeedbackRotation : public FeedbackVisualizer
    {
    public:
        HoleFeedbackRotation();

    private:
        /// @brief UI indicator for orientation
        std::shared_ptr<GOLine> m_GUILineOrientation;
        std::shared_ptr<GOPoint> m_GUILineOrientation_A;
        std::shared_ptr<GOPoint> m_GUILineOrientation_B;

    friend class HoleFeedback;
    };

    /**
        @brief The UI widget for providing feedback on orientation
                Feeds (in chronological order):
                - (i) position
                - (ii) angle
                - (iii) depth

                *    x Tb
                *     \
                *      \
                *       \ v3
                *        \
                *         \
                *          x Tt
                *          ..
                *          .  .v2
                *          .    .
                *          .     x Hs
                *       v1 .    /
                *          .   /
                *          .  / v4
                *          . /
                *          ./
                *          x He

    */
    class HoleFeedback : public FabFeedback 
    {
    public:
        HoleFeedback();
        ~HoleFeedback() = default;

        void Update() override;
        void Activate() override;
        void Deactivate() override;

    private:  ///< general data for all feedbacks but not visualized
        /// @brief the line axis for the drillbit
        std::shared_ptr<GOLine> m_DrillBitLineAxis;
        /// @brief the line axis for the hole
        std::shared_ptr<GOLine> m_HoleLineAxis;

    private:  ///< for UI widgets
        /// @brief the text visualized for numeric values of start, orientation and depth
        HoleFeedbackText m_VisText;
        /// @brief The ui widget for position guidance
        HoleFeedbackPosition m_VisPosition;
        /// @brief The ui widget to guide for the orientation
        HoleFeedbackRotation m_VisRotation;

    private:  ///< tolerances for angle and position feedbacks
        /// @brief the tolerance to detect if the tooltip is inside or outside the  hole
        float m_InsideOutDetection = 20.f;
        /// @brief acceptable tolerance for the correct rotation detection
        float m_OrientationTolerance = 1.1f;

    };
}

#endif // AC_HOLEFEEDBACK_H