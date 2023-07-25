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
                pt1->SetVisibility(false);
                pt2->SetVisibility(false);
                m_HoleLine2Start = GOLine::Add(*pt1, *pt2);
                m_HoleLine2Start->SetColor(GOColor::CYAN);

                m_HoleLine2End = GOLine::Add(*pt1, *pt2);
                m_HoleLine2End->SetColor(GOColor::RED);

                // FIXME: why remove is not working anymorer?
                // GOPoint::Remove(pt1->GetId());
                // GOPoint::Remove(pt1->GetId());
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
            std::shared_ptr<GOLine> m_HoleLine2Start;
            /// the line from the drillbit tip to the end of the hole (aka depth)
            std::shared_ptr<GOLine> m_HoleLine2End;

            FeedbackVisualizer* m_CurrentFeedbackVisualizer = nullptr;
            CutChainSawFeedVisualizer m_CutChainSawFeedVisualizer;



        // private:
        //     std::shared_ptr<ACInfoToolhead> m_CurrentToolhead;
        //     std::shared_ptr<ACInfoModel> m_CurrentModel;
    };
}