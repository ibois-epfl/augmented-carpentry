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
                
                this->m_InfoText = GOText::Add("///", *pt1);
                this->m_InfoText->SetColor(GOColor::WHITE);

                this->m_HoleLine2ToolStart = GOLine::Add(*pt1, *pt2);
                this->m_HoleLine2ToolStart->SetColor(GOColor::CYAN);
                this->m_HoleLine2ToolEnd = GOLine::Add(*pt1, *pt2);
                this->m_HoleLine2ToolEnd->SetColor(GOColor::RED);
                this->m_DrillBitLineAxis = GOLine::Add(*pt1, *pt2);
                this->m_HoleLineAxis = GOLine::Add(*pt1, *pt2);
                this->m_HoleLineAxis->SetColor(GOColor::GREEN);
                this->m_GUILineOrientation = GOLine::Add(*pt1, *pt2);
                this->m_GUILineOrientation->SetColor(GOColor::WHITE);
                
                this->m_HoleLine2ToolStart->SetVisibility(true);
                this->m_HoleLine2ToolEnd->SetVisibility(false);
                this->m_GUILineOrientation->SetVisibility(true);
                this->m_DrillBitLineAxis->SetVisibility(false);
                this->m_HoleLineAxis->SetVisibility(false);
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
            /// GUI indicator for orientation
            std::shared_ptr<GOLine> m_GUILineOrientation;
            /// All text objects
            std::shared_ptr<GOText> m_InfoText;


        // private:
        //     std::shared_ptr<ACInfoToolhead> m_CurrentToolhead;
        //     std::shared_ptr<ACInfoModel> m_CurrentModel;
    };
}