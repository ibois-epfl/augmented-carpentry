#ifndef AC_HOLEFEEDBACK_H
#define AC_HOLEFEEDBACK_H

#include "AIAC/GOSys/GOPrimitive.h"
#include "AIAC/ACInfoModel.h"
#include "FeedbackVisualizer.h"
#include "FabFeedback.h"
#include "utils/GeometryUtils.h"

namespace AIAC{
    class HoleFeedbackVisualizer : public FeedbackVisualizer {
    public:
        HoleFeedbackVisualizer();

    private:
        /// the line from the drillbit tip to the start of the hole (aka start distance)
        std::shared_ptr<GOLine> m_HoleLine2ToolStart;
        /// the line from the drillbit tip to the end of the hole (aka depth)
        std::shared_ptr<GOLine> m_HoleLine2ToolEnd;
        /// the line axis for the drillbit
        std::shared_ptr<GOLine> m_DrillBitLineAxis;
        /// the line axis for the hole
        std::shared_ptr<GOLine> m_HoleLineAxis;
        /// GUI indicator for orientation
        std::shared_ptr<GOLine> m_GUILineOrientation;
        /// All text objects
        std::shared_ptr<GOText> m_InfoText;

    friend class HoleFeedback;
    };

    class HoleFeedback : public FabFeedback {
    public:
        HoleFeedback() = default;
        ~HoleFeedback() = default;

        void Update() override;
        void Activate() override;
        void Deactivate() override;

    private:
        // TODO: here we need to differentiate between the different types of visualization
        // e.g.: the position visualization and rotation visualization
        HoleFeedbackVisualizer m_Visualizer;
    };
}

#endif // AC_HOLEFEEDBACK_H