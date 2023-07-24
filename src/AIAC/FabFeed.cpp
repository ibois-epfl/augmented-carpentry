#include "FabFeed.h"
#include "AIAC/Application.h"
#include "AIAC/GOSys/GOPrimitive.h"
#include "AIAC/Log.h"
#include "utils/utils.h"

namespace AIAC
{
    bool FabFeed::Compute()
    {
        if(m_CurrentFeedbackVisualizer != nullptr){
            m_CurrentFeedbackVisualizer->Deactivate();
        }

        if (AC_FF_TOOL->GetTypeString() == "DRILLBIT")
            if (AC_FF_COMP->GetTypeString() == "HOLE")
                return ComputeHoleFeed();
            else
                return false;
        else if (AC_FF_TOOL->GetTypeString() == "CIRCULARSAW")
            if (AC_FF_COMP->GetTypeString() == "CUT")
                return ComputeCutCircularSawFeed();
            else
                return false;
        else if (AC_FF_TOOL->GetTypeString() == "SABERSAW")
            if (AC_FF_COMP->GetTypeString() == "CUT")
                return ComputeCutSaberSawFeed();
            else
                return false;
        else if (AC_FF_TOOL->GetTypeString() == "CHAINSAW")
            if (AC_FF_COMP->GetTypeString() == "CUT") {
                m_CutChainSawFeedVisualizer.Activate();
                m_CurrentFeedbackVisualizer = &m_CutChainSawFeedVisualizer;
                return ComputeCutChainSawFeed();
            }
            else
                return false;
        else
            return false;
    }

    bool FabFeed::ComputeHoleFeed()
    {
        /*
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
        auto hole = dynamic_cast<TimberInfo::Hole*>(AC_FF_COMP);

        this->m_HoleLine2Start->SetPts(*AC_FF_TOOL->GetData<DrillBitData>().TooltipGO,  // start
                                       *hole->GetStartPointGO());

        this->m_HoleLine2End->SetPts(*AC_FF_TOOL->GetData<DrillBitData>().TooltipGO,    // start
                                     *hole->GetEndPointGO());                           // end

        // (i) start distance
        float dist = this->m_HoleLine2Start->GetLength();
        float distScaled = dist * this->m_ScaleFactor;
        AIAC_INFO(">> start distance: " + std::to_string(distScaled));

        // (ii) angle
        float angle = this->m_HoleLine2Start->ComputeAngle(this->m_HoleLine2End);
        AIAC_INFO(">> >> angle: " + std::to_string(angle));




        return true;
    }

    bool FabFeed::ComputeCutSaberSawFeed()
    {
        AIAC_INFO("ComputeCutSaberSawFeed>>>>");
        return true;
    }

    bool FabFeed::ComputeCutChainSawFeed()
    {
        // calculate tool normal
        auto toolStartPt = AC_FF_TOOL->GetData<ChainSawData>().StartGO->GetPosition();
        auto toolEndPt = AC_FF_TOOL->GetData<ChainSawData>().EndGO->GetPosition();
        auto toolChainBasePt = AC_FF_TOOL->GetData<ChainSawData>().ChainBaseGO->GetPosition();
        auto toolChainMidPt = AC_FF_TOOL->GetData<ChainSawData>().ChainMidGO->GetPosition();
        auto toolChainEndPt = AC_FF_TOOL->GetData<ChainSawData>().ChainEndGO->GetPosition();
        auto toolNormalVec = glm::cross((toolStartPt - toolChainMidPt), (toolEndPt - toolChainMidPt));

        float nearestParallelFaceDist = 1e9f;
        std::string nearestParallelFaceID;
        vector<std::string> parallelFaceIDs;
        vector<std::string> perpendicularFaceIDs;

        TimberInfo::Cut* cut = dynamic_cast<TimberInfo::Cut*>(AC_FF_COMP);
        for(auto const& [faceID, faceInfo]: cut->GetAllFaces()){
            if (faceInfo.IsExposed()) continue;
            auto faceNormal = faceInfo.GetNormal();
            auto theta = abs(glm::acos(glm::dot(faceNormal, toolNormalVec)/(glm::length(faceNormal)*glm::length(toolNormalVec))));
            AIAC_INFO(">> theta: " + std::to_string(theta) + "(60 = " + std::to_string(glm::radians(60.0f)) + ")");

            // for parallel faces, find the nearest one
            if(theta < glm::radians(60.0f)){
                parallelFaceIDs.push_back(faceID);
                auto distChainBase = glm::distance(faceInfo.GetCenter(), toolChainBasePt);
                auto distChainEnd = glm::distance(faceInfo.GetCenter(), toolChainEndPt);
                auto totalDist = distChainBase + distChainEnd;
                
                // update nearest parallel face
                if(nearestParallelFaceID.empty() || totalDist < nearestParallelFaceDist){
                    nearestParallelFaceID = faceID;
                    nearestParallelFaceDist = totalDist;
                }
            } else {
                perpendicularFaceIDs.push_back(faceID);
            }
        }

        // Highlight the face
        cut->HighlightFace(nearestParallelFaceID);

        // Update the visualizer for the closest parallel face
        if(!nearestParallelFaceID.empty()){
            m_CutChainSawFeedVisualizer.Activate();
            // find the projection point of the three points on the face
            auto faceInfo = cut->GetFace(nearestParallelFaceID);
            auto faceNormal = faceInfo.GetNormal();
            auto faceCenter = faceInfo.GetCenter();
            
            auto projEnd = GetProjectionPointOnPlane(faceNormal, faceCenter, toolEndPt);
            auto projChainBase = GetProjectionPointOnPlane(faceNormal, faceCenter, toolChainBasePt);
            auto projChainEnd = GetProjectionPointOnPlane(faceNormal, faceCenter, toolChainEndPt);

            // update the visualizer
            this->m_CutChainSawFeedVisualizer.LineEnd->SetPts(toolEndPt, projEnd);
            this->m_CutChainSawFeedVisualizer.LineChainBase->SetPts(toolChainBasePt, projChainBase);
            this->m_CutChainSawFeedVisualizer.LineChainEnd->SetPts(toolChainEndPt, projChainEnd);
            
            this->m_CutChainSawFeedVisualizer.GuideTxtEnd->SetAnchor(toolEndPt);
            this->m_CutChainSawFeedVisualizer.GuideTxtChainBase->SetAnchor(toolChainBasePt);
            this->m_CutChainSawFeedVisualizer.GuideTxtChainEnd->SetAnchor(toolChainEndPt);

            double endDist = glm::distance(toolEndPt, projEnd);
            double chainBaseDist = glm::distance(toolChainBasePt, projChainBase);
            double chainEndDist = glm::distance(toolChainEndPt, projChainEnd);

            auto toString = [](double &val) -> std::string {
                const int precisionVal = 2;
                std::string valStr = std::to_string(val);
                return valStr.substr(0, valStr.find(".") + precisionVal + 1);
            };

            this->m_CutChainSawFeedVisualizer.GuideTxtEnd->SetText("End: " + toString(endDist));
            this->m_CutChainSawFeedVisualizer.GuideTxtChainBase->SetText("Base: " + toString(chainBaseDist));
            this->m_CutChainSawFeedVisualizer.GuideTxtChainEnd->SetText("Tip: " + toString(chainEndDist));

            this->m_CutChainSawFeedVisualizer.GuideTxtEnd->SetColor(endDist < 0.5f ? GOColor::GREEN: GOColor::WHITE);
            this->m_CutChainSawFeedVisualizer.GuideTxtChainBase->SetColor(chainBaseDist < 0.5f ? GOColor::GREEN: GOColor::WHITE);
            this->m_CutChainSawFeedVisualizer.GuideTxtChainEnd->SetColor(chainEndDist < 0.5f ? GOColor::GREEN: GOColor::WHITE);

            this->m_CutChainSawFeedVisualizer.LineEnd->SetColor(endDist < 0.5f ? GOColor::GREEN: GOColor::WHITE);
            this->m_CutChainSawFeedVisualizer.LineChainBase->SetColor(chainBaseDist < 0.5f ? GOColor::GREEN: GOColor::WHITE);
            this->m_CutChainSawFeedVisualizer.LineChainEnd->SetColor(chainEndDist < 0.5f ? GOColor::GREEN: GOColor::WHITE);
        } else {
            m_CutChainSawFeedVisualizer.Deactivate();
        }

        return true;
    }

    bool FabFeed::ComputeCutCircularSawFeed()
    {
        AIAC_INFO("ComputeCutCircularSawFeed>>>>");
        return true;
    }

} // namespace AIAC