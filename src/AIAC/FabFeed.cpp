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
        float nearestPerpendicularFaceDist = 1e9f;
        std::string nearestPerpendicularFaceID;
        vector<std::string> parallelFaceIDs;
        vector<std::string> perpendicularFaceIDs;

        TimberInfo::Cut* cut = dynamic_cast<TimberInfo::Cut*>(AC_FF_COMP);
        for(auto const& [faceID, faceInfo]: cut->GetAllFaces()){
            if (faceInfo.IsExposed()) continue;
            auto faceNormal = faceInfo.GetNormal();
            auto theta = abs(glm::acos(glm::dot(faceNormal, toolNormalVec)/(glm::length(faceNormal)*glm::length(toolNormalVec))));
            AIAC_INFO(">> theta: " + std::to_string(theta) + "(45 = " + std::to_string(glm::radians(45.0f)) + ")");

            auto distChainBase = glm::distance(faceInfo.GetCenter(), toolChainBasePt);
            auto distChainEnd = glm::distance(faceInfo.GetCenter(), toolChainEndPt);
            auto totalDist = distChainBase + distChainEnd;

            // for parallel faces, find the nearest one
            if(theta < glm::radians(45.0f)){
                parallelFaceIDs.push_back(faceID);    
                // update nearest parallel face
                if(nearestParallelFaceID.empty() || totalDist < nearestParallelFaceDist){
                    nearestParallelFaceID = faceID;
                    nearestParallelFaceDist = totalDist;
                }
            } else {
                perpendicularFaceIDs.push_back(faceID);
                // update nearest perpendicular face
                if(nearestPerpendicularFaceID.empty() || totalDist < nearestPerpendicularFaceDist){
                    nearestPerpendicularFaceID = faceID;
                    nearestPerpendicularFaceDist = totalDist;
                }
            }
        }

        // Highlight the face
        cut->HighlightFace(nearestParallelFaceID);

        // Update the visualizer for the closest parallel face
        bool toShowText = false;
        auto& angleVisualizer = this->m_CutChainSawFeedVisualizer.GetAngleFeedVisualizer();
        if(!nearestParallelFaceID.empty()){
            toShowText = true;
            angleVisualizer.Activate();
            // find the projection point of the three points on the face
            auto faceInfo = cut->GetFace(nearestParallelFaceID);
            auto faceNormal = faceInfo.GetNormal();
            auto faceCenter = faceInfo.GetCenter();
            
            auto projEnd = GetProjectionPointOnPlane(faceNormal, faceCenter, toolEndPt);
            auto projChainBase = GetProjectionPointOnPlane(faceNormal, faceCenter, toolChainBasePt);
            auto projChainEnd = GetProjectionPointOnPlane(faceNormal, faceCenter, toolChainEndPt);

            // update the visualizer
            angleVisualizer.m_LineEnd->SetPts(toolEndPt, projEnd);
            angleVisualizer.m_LineChainBase->SetPts(toolChainBasePt, projChainBase);
            angleVisualizer.m_LineChainEnd->SetPts(toolChainEndPt, projChainEnd);
            
            this->m_CutChainSawFeedVisualizer.m_GuideTxtEnd->SetAnchor(toolEndPt);
            this->m_CutChainSawFeedVisualizer.m_GuideTxtChainBase->SetAnchor(toolChainBasePt);
            this->m_CutChainSawFeedVisualizer.m_GuideTxtChainEnd->SetAnchor(toolChainEndPt);

            double endDist = glm::distance(toolEndPt, projEnd);
            double chainBaseDist = glm::distance(toolChainBasePt, projChainBase);
            double chainEndDist = glm::distance(toolChainEndPt, projChainEnd);

            auto toString = [](double &val) -> std::string {
                const int precisionVal = 2;
                std::string valStr = std::to_string(val);
                return valStr.substr(0, valStr.find(".") + precisionVal + 1);
            };

            angleVisualizer.m_LineChainBase->SetColor(chainBaseDist < 0.5f ? GOColor::GREEN : GOColor::WHITE);
            angleVisualizer.m_LineEnd->SetColor(endDist < 0.5f ? GOColor::GREEN : GOColor::WHITE);
            angleVisualizer.m_LineChainEnd->SetColor(chainEndDist < 0.5f ? GOColor::GREEN : GOColor::WHITE);

            this->m_CutChainSawFeedVisualizer.m_GuideTxtEnd->SetText("End: " + toString(endDist));
            this->m_CutChainSawFeedVisualizer.m_GuideTxtChainBase->SetText("Base: " + toString(chainBaseDist));
            this->m_CutChainSawFeedVisualizer.m_GuideTxtChainEnd->SetText("Tip: " + toString(chainEndDist));

            this->m_CutChainSawFeedVisualizer.m_GuideTxtEnd->SetColor(endDist < 0.5f ? GOColor::GREEN: GOColor::WHITE);
            this->m_CutChainSawFeedVisualizer.m_GuideTxtChainBase->SetColor(chainBaseDist < 0.5f ? GOColor::GREEN: GOColor::WHITE);
            this->m_CutChainSawFeedVisualizer.m_GuideTxtChainEnd->SetColor(chainEndDist < 0.5f ? GOColor::GREEN: GOColor::WHITE);
        } else {
            angleVisualizer.Deactivate();
        }

        // Perpendicular face
        if(!nearestPerpendicularFaceID.empty()){
            toShowText = true;
        }

        if(toShowText) m_CutChainSawFeedVisualizer.Activate();
        else m_CutChainSawFeedVisualizer.Deactivate();

        return true;
    }

    CutChainSawAngleFeedVisualizer::CutChainSawAngleFeedVisualizer(){
        // Line            
        m_LineEnd = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LineChainBase = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LineChainEnd = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));

        m_LineEnd->SetColor(GOColor::WHITE);
        m_LineChainBase->SetColor(GOColor::WHITE);
        m_LineChainEnd->SetColor(GOColor::WHITE);

        m_AllPrimitives.push_back(m_LineEnd);
        m_AllPrimitives.push_back(m_LineChainBase);
        m_AllPrimitives.push_back(m_LineChainEnd);

        Deactivate();
    }

    CutChainSawDepthFeedVisualizer::CutChainSawDepthFeedVisualizer(){
        // Line
        m_LineIntersect = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LineDepthFront = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LineDepthBack = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));

        m_LineIntersect->SetColor(GOColor::WHITE);
        m_LineDepthFront->SetColor(GOColor::WHITE);
        m_LineDepthBack->SetColor(GOColor::WHITE);

        m_AllPrimitives.push_back(m_LineIntersect);
        m_AllPrimitives.push_back(m_LineDepthFront);
        m_AllPrimitives.push_back(m_LineDepthBack);

        Deactivate();
    }

    CutChainSawFeedVisualizer::CutChainSawFeedVisualizer(){
        // Text
        m_GuideTxtEnd = GOText::Add("End", GOPoint(0.f, 0.f, 0.f));
        m_GuideTxtChainBase = GOText::Add("ChainBase", GOPoint(0.f, 0.f, 0.f));
        m_GuideTxtChainEnd = GOText::Add("ChainEnd", GOPoint(0.f, 0.f, 0.f));

        m_GuideTxtEnd->SetColor(GOColor::WHITE);
        m_GuideTxtChainBase->SetColor(GOColor::WHITE);
        m_GuideTxtChainEnd->SetColor(GOColor::WHITE);

        m_AllPrimitives.push_back(m_GuideTxtEnd);
        m_AllPrimitives.push_back(m_GuideTxtChainBase);
        m_AllPrimitives.push_back(m_GuideTxtChainEnd);

        Deactivate();
    }

    bool FabFeed::ComputeCutCircularSawFeed()
    {
        AIAC_INFO("ComputeCutCircularSawFeed>>>>");
        return true;
    }

} // namespace AIAC