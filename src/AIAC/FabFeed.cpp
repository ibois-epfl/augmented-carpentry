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
        auto toolMidPt = AC_FF_TOOL->GetData<ChainSawData>().ChainMidGO->GetPosition();
        auto toolNormalVec = glm::cross((toolStartPt - toolMidPt), (toolEndPt - toolMidPt));

        std::string nearestParallelFaceID;
        float nearestParallelFaceDist = 1e9f;
        vector<std::string> parallelFaceIDs;
        vector<std::string> perpendicularFaceIDs;

        TimberInfo::Cut* cut = dynamic_cast<TimberInfo::Cut*>(AC_FF_COMP);
        for(auto const& [faceID, faceInfo]: cut->GetAllFaces()){
            if (faceInfo.IsExposed()) continue;
            auto faceNormal = faceInfo.GetNormal();
            auto theta = glm::acos(glm::dot(faceNormal, toolNormalVec)/(glm::length(faceNormal)*glm::length(toolNormalVec)));
            // AIAC_INFO(">> theta: " + std::to_string(theta) + "(45 = " + std::to_string(glm::radians(45.0f)) + ")");

            // for parallel faces, find the nearest one
            if(theta < glm::radians(45.0f) || theta > glm::radians(-45.0f)){
                parallelFaceIDs.push_back(faceID);
                auto distStart = glm::distance(faceInfo.GetCenter(), toolStartPt);
                auto distEnd = glm::distance(faceInfo.GetCenter(), toolEndPt);
                auto distMid = glm::distance(faceInfo.GetCenter(), toolMidPt);
                auto totalDist = distStart + distEnd + distMid;
                
                // update nearest parallel face
                if(nearestParallelFaceID.empty() || totalDist < nearestParallelFaceDist){
                    nearestParallelFaceID = faceID;
                    nearestParallelFaceDist = totalDist;
                }
            } else {
                perpendicularFaceIDs.push_back(faceID);
            }
            //
        }

        // Update the visualizer for the closest parallel face
        if(!nearestParallelFaceID.empty()){
            // find the projection point of the three points on the face
            auto faceInfo = cut->GetFace(nearestParallelFaceID);
            auto faceNormal = faceInfo.GetNormal();
            auto faceCenter = faceInfo.GetCenter();

            auto projStart = GetProjectionPointOnPlane(faceNormal, faceCenter, toolStartPt);
            auto projEnd = GetProjectionPointOnPlane(faceNormal, faceCenter, toolEndPt);
            auto projMid = GetProjectionPointOnPlane(faceNormal, faceCenter, toolMidPt);

            auto toolStartPt = AC_FF_TOOL->GetData<ChainSawData>().StartGO->GetPosition();
            auto toolEndPt = AC_FF_TOOL->GetData<ChainSawData>().EndGO->GetPosition();
            auto toolMidPt = AC_FF_TOOL->GetData<ChainSawData>().ChainMidGO->GetPosition();
            
            // update the visualizer
            this->m_CutChainSawFeedVisualizer.LineStart->SetPts(toolStartPt, projStart);
            this->m_CutChainSawFeedVisualizer.LineEnd->SetPts(toolEndPt, projEnd);
            this->m_CutChainSawFeedVisualizer.LineMid->SetPts(toolMidPt, projMid);
        }

        return true;
    }

    bool FabFeed::ComputeCutCircularSawFeed()
    {
        AIAC_INFO("ComputeCutCircularSawFeed>>>>");
        return true;
    }

} // namespace AIAC