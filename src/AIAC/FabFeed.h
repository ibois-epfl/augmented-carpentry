#pragma once

#include "AIAC/ACInfoToolheadManager.h"
#include "AIAC/ACInfoToolhead.h"
#include "AIAC/ACInfoModel.h"
#include "AIAC/GOSys/GOPrimitive.h"
#include "AIAC/Config.h"

///< timber components
#define AC_FF_COMP AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().GetCurrentComponent()
// #define AC_FF_HOLE dynamic_cast<TimberInfo::Hole*>(AC_FF_COMP)
///< toolhead
#define AC_FF_TOOL AIAC_APP.GetLayer<LayerToolhead>()->ACInfoToolheadManager->GetActiveToolhead()
// #define AC_FF_TOOL_DRILLBIT_D AC_FF_TOOL->GetData<DrillBitData>()
// #define AC_FF_TOOL_CIRCULARSAW_D AC_FF_TOOL->GetData<CircularSawData>()
// #define AC_FF_TOOL_SABERSAW_D AC_FF_TOOL->GetData<SaberSawData>()
// #define AC_FF_TOOL_CHAINSAW_D AC_FF_TOOL->GetData<ChainSawData>()

namespace AIAC
{
    class FeedbackVisualizer {
    public:
        FeedbackVisualizer() = default;
        ~FeedbackVisualizer() = default;

        inline void Activate() {
            for (auto &p : m_AllPrimitives) {
                p->SetVisibility(true);
            }
        }

        inline void Deactivate() {
            for (auto &p : m_AllPrimitives) {
                p->SetVisibility(false);
            }
        }

    protected:
        std::vector<std::shared_ptr<GOPrimitive>> m_AllPrimitives;

    friend class FabFeed;
    };

    class CutChainSawAngleFeedVisualizer : public FeedbackVisualizer {
    public:
        CutChainSawAngleFeedVisualizer();

    private:
        std::shared_ptr<GOLine> m_LineEnd;
        std::shared_ptr<GOLine> m_LineChainBase;
        std::shared_ptr<GOLine> m_LineChainEnd;

    friend class FabFeed;
    };

    class CutChainSawDepthFeedVisualizer : public FeedbackVisualizer {
    public:
        CutChainSawDepthFeedVisualizer();

    private:
        std::shared_ptr<GOLine> m_LineIntersect;
        std::shared_ptr<GOLine> m_LineDepthChainBase;
        std::shared_ptr<GOLine> m_LineDepthChainEnd;

    friend class FabFeed;
    };

    class CutChainSawFeedVisualizer : public FeedbackVisualizer {
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

    friend class FabFeed;
    };

    class FabFeed
    {
    public:
            FabFeed()
            {
                this->m_ScaleFactor = AIAC::Config::Get<float>(AIAC::Config::SEC_AIAC, AIAC::Config::SCALE_FACTOR, 50.f);

                auto pt1 = GOPoint::Add(0.f, 0.f, 0.f);
                auto pt2 = GOPoint::Add(5.f, 5.f, 5.f);
                auto pt3 = GOPoint::Add(5.f, 5.f, 5.f);
                pt1->SetVisibility(false);
                pt2->SetVisibility(false);
                pt3->SetVisibility(false);
                
                this->m_InfoText = GOText::Add("///", *pt1);
                this->m_InfoText->SetColor(GOColor::WHITE);

                this->m_HoleLine2ToolStart = GOLine::Add(*pt1, *pt2);
                this->m_HoleLine2ToolStart->SetColor(GOColor::CYAN);
                this->m_HoleLine2ToolEnd = GOLine::Add(*pt1, *pt2);
                this->m_HoleLine2ToolEnd->SetColor(GOColor::RED);
                this->m_DrillBitLineAxis = GOLine::Add(*pt1, *pt2);
                this->m_HoleLineAxis = GOLine::Add(*pt1, *pt2);
                this->m_HoleLineAxis->SetColor(GOColor::GREEN);
                this->m_GUIPointsTranslation.push_back(pt1);  // tooltip
                this->m_GUIPointsTranslation.push_back(pt2);  // midHalf1
                this->m_GUIPointsTranslation.push_back(pt3);  // midHalf
                for (auto& pt : this->m_GUIPointsTranslation)
                    pt->SetColor(GOColor::WHITE);
                this->m_GUILineOrientation = GOLine::Add(*pt1, *pt2);
                this->m_GUILineOrientation->SetColor(GOColor::WHITE);

                for (auto& pt : this->m_GUIPointsTranslation)
                    pt->SetWeight(GOWeight::BoldThick);
                
                this->m_HoleLine2ToolStart->SetVisibility(false);
                this->m_HoleLine2ToolEnd->SetVisibility(false);
                this->m_GUILineOrientation->SetVisibility(true);
                this->m_DrillBitLineAxis->SetVisibility(false);
                this->m_HoleLineAxis->SetVisibility(false);
                for (auto& pt : this->m_GUIPointsTranslation)
                    pt->SetVisibility(true);
            };

        public:
            /**
             * @brief The main function to produce the feedback based on the current toolhead and 
             *        model component (hole or cut).
             * 
             * @return true if the feedback is produced
             */
            bool Compute();
            bool ComputeHoleFeed();
            bool ComputeCutSaberSawFeed();
            bool ComputeCutChainSawFeed();
            bool ComputeCutCircularSawFeed();

        private:
            /// Scale factor
            float m_ScaleFactor = m_ScaleFactor;
            /// the line from the drillbit tip to the start of the hole (aka start distance)
            std::shared_ptr<GOLine> m_HoleLine2ToolStart;
            /// the line from the drillbit tip to the end of the hole (aka depth)
            std::shared_ptr<GOLine> m_HoleLine2ToolEnd;
            /// the line axis for the drillbit
            std::shared_ptr<GOLine> m_DrillBitLineAxis;
            /// the line axis for the hole
            std::shared_ptr<GOLine> m_HoleLineAxis;
            /// GUI indicator for translation (dots)
            std::vector<std::shared_ptr<GOPoint>> m_GUIPointsTranslation;
            /// GUI indicator for orientation
            std::shared_ptr<GOLine> m_GUILineOrientation;
            /// All text objects
            std::shared_ptr<GOText> m_InfoText;

            FeedbackVisualizer* m_CurrentFeedbackVisualizer = nullptr;
            // For Cuts
            CutChainSawFeedVisualizer m_CutChainSawFeedVisualizer;

        // private:
        //     std::shared_ptr<ACInfoToolhead> m_CurrentToolhead;
        //     std::shared_ptr<ACInfoModel> m_CurrentModel;
    };
}