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