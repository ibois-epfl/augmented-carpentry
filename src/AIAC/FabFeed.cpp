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
        bool hasParallelFace = false, hasPerpendicularFace = false;
        auto& angleVisualizer = this->m_CutChainSawFeedVisualizer.GetAngleFeedVisualizer();

        double parallelEndDist = 0.0f;
        double parallelChainBaseDist = 0.0f;
        double parallelChainEndDist = 0.0f;
        double perpendicularChainBaseDist = 0.0f;
        double perpendicularChainEndDist = 0.0f;

        if(!nearestParallelFaceID.empty()){
            hasParallelFace = true;
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

            parallelEndDist = glm::distance(toolEndPt, projEnd);
            parallelChainBaseDist = glm::distance(toolChainBasePt, projChainBase);
            parallelChainEndDist = glm::distance(toolChainEndPt, projChainEnd);

            angleVisualizer.m_LineEnd->SetColor(parallelEndDist < 0.5f ? GOColor::GREEN : GOColor::WHITE);
            angleVisualizer.m_LineChainBase->SetColor(parallelChainBaseDist < 0.5f ? GOColor::GREEN : GOColor::WHITE);
            angleVisualizer.m_LineChainEnd->SetColor(parallelChainEndDist < 0.5f ? GOColor::GREEN : GOColor::WHITE);
        } else {
            angleVisualizer.Deactivate();
        }

        // Perpendicular face
        auto& depthVisualizer = this->m_CutChainSawFeedVisualizer.GetDepthFeedVisualizer();
        if(!nearestPerpendicularFaceID.empty()){
            hasPerpendicularFace = true;
            depthVisualizer.Activate();

            // find the projection point of the 2 points on the face
            auto faceInfo = cut->GetFace(nearestPerpendicularFaceID);
            auto faceNormal = faceInfo.GetNormal();
            auto faceCenter = faceInfo.GetCenter();

            auto projChainBase = GetProjectionPointOnPlane(faceNormal, faceCenter, toolChainBasePt);
            auto projChainEnd = GetProjectionPointOnPlane(faceNormal, faceCenter, toolChainEndPt);

            // update the visualizer
            depthVisualizer.m_LineIntersect->SetPts(projChainBase, projChainEnd);
            depthVisualizer.m_LineDepthChainBase->SetPts(projChainBase, toolChainBasePt);
            depthVisualizer.m_LineDepthChainEnd->SetPts(projChainEnd, toolChainEndPt);

            perpendicularChainBaseDist = glm::distance(toolChainBasePt, projChainBase);
            perpendicularChainEndDist = glm::distance(toolChainEndPt, projChainEnd);

            // get the direction of cutting
            // FIXIT: This we don't need to calculate toolUpVec everytime
            auto toolUpVec = glm::normalize(toolEndPt - toolChainBasePt);
            auto chainBaseVec = glm::normalize(toolChainBasePt - projChainBase);
            auto chainEndVec = glm::normalize(toolChainEndPt - projChainEnd);

            if(glm::dot(toolUpVec, chainBaseVec) < 0){
                depthVisualizer.m_LineDepthChainBase->SetColor(GOColor::RED);
                perpendicularChainBaseDist = -perpendicularChainBaseDist;
            } else {
                depthVisualizer.m_LineDepthChainBase->SetColor(GOColor::YELLOW);
            }
            if(glm::dot(toolUpVec, chainEndVec) < 0){
                perpendicularChainEndDist = -perpendicularChainEndDist;
                depthVisualizer.m_LineDepthChainEnd->SetColor(GOColor::RED);
            } else {
                depthVisualizer.m_LineDepthChainEnd->SetColor(GOColor::YELLOW);
            }

        } else {
            depthVisualizer.Deactivate();
        }

        if(hasParallelFace || hasPerpendicularFace) {
            m_CutChainSawFeedVisualizer.Activate();

            auto toString = [](double &val) -> std::string {
                // const int precisionVal = 2;
                // std::string valStr = std::to_string(val);
                // return valStr.substr(0, valStr.find(".") + precisionVal + 1);

                // TODO: / 50 * 1000 => mm, change this to a variable
                auto retVal = to_string(int(val * 20));
                if(retVal.length() == 1){
                    return "0" + retVal;
                }
                return retVal;
            };

            auto strEnd = "End: " + toString(parallelEndDist);
            auto strChainBase = "Base: " + toString(parallelChainBaseDist) + "/" + toString(perpendicularChainBaseDist);
            auto strChainEnd = "Tip: " + toString(parallelChainEndDist) + "/" + toString(perpendicularChainEndDist);

            this->m_CutChainSawFeedVisualizer.m_GuideTxtEnd->SetText(strEnd);
            this->m_CutChainSawFeedVisualizer.m_GuideTxtChainBase->SetText(strChainBase);
            this->m_CutChainSawFeedVisualizer.m_GuideTxtChainEnd->SetText(strChainEnd);

            this->m_CutChainSawFeedVisualizer.m_GuideTxtEnd->SetAnchor(toolEndPt);
            this->m_CutChainSawFeedVisualizer.m_GuideTxtChainBase->SetAnchor(toolChainBasePt);
            this->m_CutChainSawFeedVisualizer.m_GuideTxtChainEnd->SetAnchor(toolChainEndPt);

            auto endColor = GOColor::WHITE;
            auto chainBaseColor = GOColor::WHITE;
            auto chainEndColor = GOColor::WHITE;

            if(parallelEndDist != 0 && parallelEndDist < 0.5f){
                endColor = GOColor::GREEN;
            }
            if(parallelChainBaseDist != 0 && parallelChainBaseDist < 0.5f){
                chainBaseColor = GOColor::GREEN;
            }
            if(parallelChainEndDist != 0 && parallelChainEndDist < 0.5f){
                chainEndColor = GOColor::GREEN;
            }
            if(perpendicularChainBaseDist != 0 && perpendicularChainBaseDist < 0){
                chainBaseColor = GOColor::RED;
            }
            if(perpendicularChainEndDist != 0 && perpendicularChainEndDist < 0){
                chainEndColor = GOColor::RED;
            }

            this->m_CutChainSawFeedVisualizer.m_GuideTxtEnd->SetColor(endColor);
            this->m_CutChainSawFeedVisualizer.m_GuideTxtChainBase->SetColor(chainBaseColor);
            this->m_CutChainSawFeedVisualizer.m_GuideTxtChainEnd->SetColor(chainEndColor);
//            this->m_CutChainSawFeedVisualizer.m_GuideTxtChainBase->SetColor(parallelChainBaseDist < 0.5f ? GOColor::GREEN: GOColor::WHITE);
//            this->m_CutChainSawFeedVisualizer.m_GuideTxtChainEnd->SetColor(parallelChainEndDist < 0.5f ? GOColor::GREEN: GOColor::WHITE);

        }
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
        m_LineDepthChainBase = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LineDepthChainEnd = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));

        m_LineIntersect->SetColor(GOColor::CYAN);
        m_LineDepthChainBase->SetColor(GOColor::YELLOW);
        m_LineDepthChainEnd->SetColor(GOColor::YELLOW);

        m_AllPrimitives.push_back(m_LineIntersect);
        m_AllPrimitives.push_back(m_LineDepthChainBase);
        m_AllPrimitives.push_back(m_LineDepthChainEnd);

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