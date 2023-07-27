#include "FabFeed.h"
#include "AIAC/Application.h"
#include "AIAC/GOSys/GOPrimitive.h"
#include "AIAC/Log.h"
#include "utils/utils.h"
#include "utils/GeometryUtils.h"

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

        this->m_HoleLine2ToolStart->SetPts(*AC_FF_TOOL->GetData<DrillBitData>().TooltipGO,  // start
                                           *hole->GetStartPointGO());                       // end
        this->m_HoleLine2ToolEnd->SetPts(*AC_FF_TOOL->GetData<DrillBitData>().TooltipGO,    // start
                                         *hole->GetEndPointGO());                           // end
        this->m_DrillBitLineAxis->SetPts(*AC_FF_TOOL->GetData<DrillBitData>().ToolbaseGO,   // start
                                         *AC_FF_TOOL->GetData<DrillBitData>().TooltipGO);   // end
        this->m_HoleLineAxis->SetPts(*hole->GetStartPointGO(),                              // start
                                     *hole->GetEndPointGO());                               // end
        
        // start orientation guidance
        glm::vec3 toolTipVec = this->m_DrillBitLineAxis->GetPEnd().GetPosition();
        glm::vec3 midPtToolAxisVec = this->m_HoleLine2ToolStart->GetMidPointValues();
        glm::vec3 midPtToolAxisVecHalf1 = glm::vec3((toolTipVec.x + midPtToolAxisVec.x) / 2.f,
                                            (toolTipVec.y + midPtToolAxisVec.y) / 2.f,
                                            (toolTipVec.z + midPtToolAxisVec.z) / 2.f);
        glm::vec3 holeStartVec = this->m_HoleLineAxis->GetPStart().GetPosition();
        this->m_GUIPointsTranslation[0]->SetPosition(toolTipVec);
        this->m_GUIPointsTranslation[1]->SetPosition(midPtToolAxisVecHalf1);
        this->m_GUIPointsTranslation[2]->SetPosition(midPtToolAxisVec);

        // angle orientation guidance
        glm::vec3 midPtToolAxis = this->m_DrillBitLineAxis->GetMidPointValues();
        glm::vec3 translVec = glm::vec3(this->m_HoleLineAxis->GetPEnd().X() - this->m_DrillBitLineAxis->GetPEnd().X(),
                                       this->m_HoleLineAxis->GetPEnd().Y() - this->m_DrillBitLineAxis->GetPEnd().Y(),
                                       this->m_HoleLineAxis->GetPEnd().Z() - this->m_DrillBitLineAxis->GetPEnd().Z());
        this->m_DrillBitLineAxis->Translate(translVec);
        float lengthHole = this->m_HoleLineAxis->GetLength();
        float lengthDrillBit = this->m_DrillBitLineAxis->GetLength();
        float lengthDiff = lengthHole - lengthDrillBit;
        this->m_DrillBitLineAxis->ExtendFromStart(lengthDiff);

        this->m_GUILineOrientation->SetPts(this->m_DrillBitLineAxis->GetPStart(),  // start
                                           this->m_HoleLineAxis->GetPStart());     // end
        glm::vec3 vectGUITrans = glm::vec3(midPtToolAxis.x - this->m_DrillBitLineAxis->GetPStart().X(),
                                           midPtToolAxis.y - this->m_DrillBitLineAxis->GetPStart().Y(),
                                           midPtToolAxis.z - this->m_DrillBitLineAxis->GetPStart().Z());
        this->m_GUILineOrientation->Translate(vectGUITrans);


        this->m_HoleLine2ToolStart->InitGLObject();
        this->m_HoleLine2ToolEnd->InitGLObject();
        this->m_DrillBitLineAxis->InitGLObject();
        this->m_HoleLineAxis->InitGLObject();
        this->m_GUILineOrientation->InitGLObject();
        for (auto& pt : this->m_GUIPointsTranslation)
            pt->InitGLObject();

        // (i) start distance
        float dist = this->m_HoleLine2ToolStart->GetLength();
        float distScaled = dist / this->m_ScaleFactor;
        int distScaledMM = std::round(distScaled * 1000.f);
        if (distScaledMM > 99) distScaledMM = 99;
        // make the text always 2 digits like 01, 02, 03, ...
        std::string distScaledMMStr = std::to_string(distScaledMM);
        if (distScaledMMStr.size() == 1) distScaledMMStr = "0" + distScaledMMStr;
        // AIAC_INFO(">> start distance: " + std::to_string(distScaledMMStr));

        // (ii) detect if inside
        float angle = this->m_HoleLine2ToolStart->ComputeAngle(this->m_HoleLine2ToolEnd);
        // AIAC_INFO(">> >> angle tooltips/holeEnds: " + std::to_string(angle));

        // (iii) angle
        float angleOrient = this->m_DrillBitLineAxis->ComputeAngle(this->m_HoleLineAxis);
        int angleOrientRounded = angleOrient;
        if (angleOrientRounded > 99) angleOrientRounded = 99;
        std::string angleOrientRoundedStr = std::to_string(angleOrientRounded);
        if (angleOrientRoundedStr.size() == 1) angleOrientRoundedStr = "0" + angleOrientRoundedStr;
        // AIAC_INFO(">> >> angle drillbit/holeAxis: " + std::to_string(angleOrientRoundedStr));

        // (iv) depth
        float depthLeft = this->m_HoleLineAxis->GetPEnd().DistanceTo(*AC_FF_TOOL->GetData<DrillBitData>().TooltipGO);
        float depthLeftScaled = depthLeft / this->m_ScaleFactor;
        int depthLeftScaledMM = std::round(depthLeftScaled * 1000.f);
        std::string depthLeftScaledMMStr = std::to_string(depthLeftScaledMM);
        // AIAC_INFO(">> depthLeft: " + std::to_string(depthLeftScaledMMStr));




        // // >>>>>>>>>>>>>>>>>
        // if (distScaled < 0.005f)  // TODO: set tolerance var member, 5mm for now
        //     AIAC_INFO(">> >> >> drillbit is well positioned");  // TODO: set tolerance var member
        
        if (160.f < angle && angle < 200.f)  // TODO: set tolerance var member, 20deg for now
        {
            // AIAC_INFO(">> >> >> drillbit is inside");
            distScaledMMStr = "00";
            for (auto& pt : this->m_GUIPointsTranslation)
                pt->SetVisibility(false);
        }
        else
        {
            // AIAC_INFO(">> >> >> drillbit is outside");
            for (auto& pt : this->m_GUIPointsTranslation)
                pt->SetVisibility(true);
        }
        if (angleOrient < 0.5f)  // TODO: set tolerance var member
            this->m_GUILineOrientation->SetVisibility(false);
        else
            this->m_GUILineOrientation->SetVisibility(true);



        // -- text
        std::string test = " s:" + distScaledMMStr + "/a:" + angleOrientRoundedStr + "/e:" + depthLeftScaledMMStr;
        this->m_InfoText->SetText(test);
        this->m_InfoText->SetAnchor(midPtToolAxis);


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
        auto toolNormStartPt = AC_FF_TOOL->GetData<ChainSawData>().NormStartGO->GetPosition();
        auto toolNormEndPt = AC_FF_TOOL->GetData<ChainSawData>().NormEndGO->GetPosition();
        auto toolChainBasePt = AC_FF_TOOL->GetData<ChainSawData>().ChainBaseGO->GetPosition();
        auto toolChainMidPt = AC_FF_TOOL->GetData<ChainSawData>().ChainMidGO->GetPosition();
        auto toolChainEndPt = AC_FF_TOOL->GetData<ChainSawData>().ChainEndGO->GetPosition();
        auto toolNormalVec = glm::normalize(toolNormEndPt - toolNormStartPt);

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
            auto theta = glm::acos(glm::dot(faceNormal, toolNormalVec)/(glm::length(faceNormal)*glm::length(toolNormalVec)));

            auto distChainBase = glm::distance(faceInfo.GetCenter(), toolChainBasePt);
            auto distChainEnd = glm::distance(faceInfo.GetCenter(), toolChainEndPt);
            auto totalDist = distChainBase + distChainEnd;

            // for parallel faces, find the nearest one
            auto threshold = 0.7853f; // 45 degrees
            if(theta < threshold || (3.14159 - theta) < threshold) {
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
        double perpendicularFaceEdge1Dist = 0.0f;
        double perpendicularFaceEdge2Dist = 0.0f;
        glm::vec3 perpIntersectLineSegPt1, perpIntersectLineSegPt2; // for depth text anchor

        if(!nearestParallelFaceID.empty()){
            hasParallelFace = true;
            angleVisualizer.Activate();

            // find the projection point of the three points on the face
            auto faceInfo = cut->GetFace(nearestParallelFaceID);
            auto faceNormal = faceInfo.GetNormal();
            auto faceCenter = faceInfo.GetCenter();

            auto projNormStart = GetProjectionPointOnPlane(faceNormal, faceCenter, toolNormStartPt);
            auto projChainBase = GetProjectionPointOnPlane(faceNormal, faceCenter, toolChainBasePt);
            auto projChainEnd = GetProjectionPointOnPlane(faceNormal, faceCenter, toolChainEndPt);

            // update the visualizer
            angleVisualizer.m_LineEnd->SetPts(toolNormStartPt, projNormStart);
            angleVisualizer.m_LineChainBase->SetPts(toolChainBasePt, projChainBase);
            angleVisualizer.m_LineChainEnd->SetPts(toolChainEndPt, projChainEnd);

            parallelEndDist = glm::distance(toolNormStartPt, projNormStart);
            parallelChainBaseDist = glm::distance(toolChainBasePt, projChainBase);
            parallelChainEndDist = glm::distance(toolChainEndPt, projChainEnd);

            angleVisualizer.m_LineEnd->SetColor(parallelEndDist < 0.5f ? GOColor::GREEN : GOColor::WHITE);
            angleVisualizer.m_LineChainBase->SetColor(parallelChainBaseDist < 0.5f ? GOColor::GREEN : GOColor::WHITE);
            angleVisualizer.m_LineChainEnd->SetColor(parallelChainEndDist < 0.5f ? GOColor::GREEN : GOColor::WHITE);
        } else {
            // angleVisualizer.Deactivate();
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

            // Get the intersection line of the tool plane and the face plane
            glm::vec3 intersectLineVec, intersectLinePt;
            if(!GetIntersectLineOf2Planes(faceNormal, faceCenter,
                                          toolNormalVec, toolChainBasePt,
                                          intersectLineVec, intersectLinePt)){
                AIAC_ERROR("Failed to get the intersect line of two planes");
                // Technically this should not happen
                // TODO: Error handling?
            }

            // Get the intersection point of the intersect line and the face's edges
            std::vector<glm::vec3> intersectPts;
            for(auto const& edgeID: faceInfo.GetEdges()){
                auto edge = cut->GetEdge(edgeID);
                auto edgePt1 = edge.GetStartPt().GetPosition();
                auto edgePt2 = edge.GetEndPt().GetPosition();
                ExtendLineSeg(edgePt1, edgePt2, 5.0f);
                glm::vec3 intersectPt;
                if(GetIntersectPointOfLineAndLineSeg(intersectLineVec, intersectLinePt, edgePt1, edgePt2, intersectPt)) {
                    intersectPts.push_back(intersectPt);
                }
            }
            
            FormLongestLineSeg(intersectPts, perpIntersectLineSegPt1, perpIntersectLineSegPt2);
            
            // update the visualizer
            // FIXME: Change to intersection of two planes
            // Lines based on tool
            auto projChainBase = GetNearestPtOnLine(intersectLineVec, intersectLinePt, toolChainBasePt);
            auto projChainEnd = GetNearestPtOnLine(intersectLineVec, intersectLinePt, toolChainEndPt);

            depthVisualizer.m_LineIntersect->SetPts(projChainBase, projChainEnd);
            // depthVisualizer.m_LineDepthChainBase->SetPts(projChainBase, toolChainBasePt);
            // depthVisualizer.m_LineDepthChainEnd->SetPts(projChainEnd, toolChainEndPt);

            perpendicularChainBaseDist = glm::distance(toolChainBasePt, projChainBase);
            perpendicularChainEndDist = glm::distance(toolChainEndPt, projChainEnd);

            // Lines based on face edge
            // for face edge dist, we need to find the projection point of the two points on the saw first
            glm::vec3 pt1ProjPt, pt2ProjPt;
            auto pt1OnEndMid = GetNearestPtOnLine(toolChainEndPt - toolChainMidPt, toolChainEndPt, perpIntersectLineSegPt1);
            auto pt1OnMidBase = GetNearestPtOnLine(toolChainMidPt - toolChainBasePt, toolChainMidPt, perpIntersectLineSegPt1);
            auto pt2OnEndMid = GetNearestPtOnLine(toolChainEndPt - toolChainMidPt, toolChainEndPt, perpIntersectLineSegPt2);
            auto pt2OnMidBase = GetNearestPtOnLine(toolChainMidPt - toolChainBasePt, toolChainMidPt, perpIntersectLineSegPt2);

            pt1ProjPt = CheckIfPointInsideLineSeg(pt1OnMidBase, toolChainMidPt, toolChainBasePt) ? pt1OnMidBase : pt1OnEndMid;
            pt2ProjPt = CheckIfPointInsideLineSeg(pt2OnMidBase, toolChainMidPt, toolChainBasePt) ? pt2OnMidBase : pt2OnEndMid;

            depthVisualizer.m_LineDepthFaceEdge1->SetPts(perpIntersectLineSegPt1, pt1ProjPt);
            depthVisualizer.m_LineDepthFaceEdge2->SetPts(perpIntersectLineSegPt2, pt2ProjPt);

            perpendicularFaceEdge1Dist = glm::distance(perpIntersectLineSegPt1, pt1ProjPt);
            perpendicularFaceEdge2Dist = glm::distance(perpIntersectLineSegPt2, pt2ProjPt);

            // get the direction of tool
            auto toolUpVec = glm::normalize(toolNormStartPt - toolChainBasePt);
            auto chainBaseVec = glm::normalize(toolChainBasePt - projChainBase);
            auto chainEndVec = glm::normalize(toolChainEndPt - projChainEnd);
            auto faceEdge1Vec = glm::normalize(pt1ProjPt - perpIntersectLineSegPt1);
            auto faceEdge2Vec = glm::normalize(pt2ProjPt - perpIntersectLineSegPt2);

            // if(glm::dot(toolUpVec, chainBaseVec) < 0){
            //     depthVisualizer.m_LineDepthChainBase->SetColor(GOColor::RED);
            //     perpendicularChainBaseDist = -perpendicularChainBaseDist;
            // } else {
            //     depthVisualizer.m_LineDepthChainBase->SetColor(GOColor::YELLOW);
            // }
            // if(glm::dot(toolUpVec, chainEndVec) < 0){
            //     perpendicularChainEndDist = -perpendicularChainEndDist;
            //     depthVisualizer.m_LineDepthChainEnd->SetColor(GOColor::RED);
            // } else {
            //     depthVisualizer.m_LineDepthChainEnd->SetColor(GOColor::YELLOW);
            // }

            if(glm::dot(toolUpVec, faceEdge1Vec) < 0){
                depthVisualizer.m_LineDepthFaceEdge1->SetColor(GOColor::RED);
                perpendicularFaceEdge1Dist = -perpendicularFaceEdge1Dist;
            } else {
                depthVisualizer.m_LineDepthFaceEdge1->SetColor(GOColor::YELLOW);
            }
            if(glm::dot(toolUpVec, faceEdge2Vec) < 0){
                depthVisualizer.m_LineDepthFaceEdge2->SetColor(GOColor::RED);
                perpendicularFaceEdge2Dist = -perpendicularFaceEdge2Dist;
            } else {
                depthVisualizer.m_LineDepthFaceEdge2->SetColor(GOColor::YELLOW);
            }

        } else {
            depthVisualizer.Deactivate();
        }

        if(hasParallelFace || hasPerpendicularFace) {
            m_CutChainSawFeedVisualizer.Activate();

            m_CutChainSawFeedVisualizer.m_LineChainNormal->SetPts(toolChainEndPt, toolChainEndPt + toolNormalVec * 5.0f);

            auto toString = [](double &val) -> std::string {
                // const int precisionVal = 2;
                // std::string valStr = std::to_string(val);
                // return valStr.substr(0, valStr.find(".") + precisionVal + 1);

                // TODO: / 50 * 1000 => mm, change this to a variable
                int valInt = (int)(val / 50 * 1000);
                if(valInt > 99) valInt = 99;
                auto retVal = to_string(valInt);
                if(retVal.length() == 1){
                    return "0" + retVal;
                }
                return retVal;
            };

            auto strEnd = toString(parallelEndDist);
            auto strChainBase = toString(parallelChainBaseDist);
            auto strChainEnd = toString(parallelChainEndDist);

            this->m_CutChainSawFeedVisualizer.m_GuideTxtEnd->SetText(strEnd);
            this->m_CutChainSawFeedVisualizer.m_GuideTxtChainBase->SetText(strChainBase);
            this->m_CutChainSawFeedVisualizer.m_GuideTxtChainEnd->SetText(strChainEnd);

            this->m_CutChainSawFeedVisualizer.m_GuideTxtFaceEdgeDepth1->SetText(toString(perpendicularFaceEdge1Dist));
            this->m_CutChainSawFeedVisualizer.m_GuideTxtFaceEdgeDepth2->SetText(toString(perpendicularFaceEdge2Dist));

            this->m_CutChainSawFeedVisualizer.m_GuideTxtEnd->SetAnchor(toolNormStartPt);
            this->m_CutChainSawFeedVisualizer.m_GuideTxtChainBase->SetAnchor(toolChainBasePt);
            this->m_CutChainSawFeedVisualizer.m_GuideTxtChainEnd->SetAnchor(toolChainEndPt);

            this->m_CutChainSawFeedVisualizer.m_GuideTxtFaceEdgeDepth1->SetAnchor(perpIntersectLineSegPt1);
            this->m_CutChainSawFeedVisualizer.m_GuideTxtFaceEdgeDepth2->SetAnchor(perpIntersectLineSegPt2);

            auto endColor = GOColor::WHITE;
            auto chainBaseColor = GOColor::WHITE;
            auto chainEndColor = GOColor::WHITE;
            
            auto faceEdgeTxt1Color = GOColor::WHITE;
            auto faceEdgeTxt2Color = GOColor::WHITE;

            if(parallelEndDist != 0 && parallelEndDist < 0.5f){
                endColor = GOColor::GREEN;
            }
            if(parallelChainBaseDist != 0 && parallelChainBaseDist < 0.5f){
                chainBaseColor = GOColor::GREEN;
            }
            if(parallelChainEndDist != 0 && parallelChainEndDist < 0.5f){
                chainEndColor = GOColor::GREEN;
            }

            if(perpendicularFaceEdge1Dist > 0 && perpendicularFaceEdge1Dist < 0.5f){
                faceEdgeTxt1Color = GOColor::GREEN;
            } else if (perpendicularFaceEdge1Dist < 0){
                faceEdgeTxt1Color = GOColor::RED;
            }
            if(perpendicularFaceEdge2Dist > 0 && perpendicularFaceEdge2Dist < 0.5f){
                faceEdgeTxt2Color = GOColor::GREEN;
            } else if (perpendicularFaceEdge2Dist < 0){
                faceEdgeTxt2Color = GOColor::RED;
            }

            this->m_CutChainSawFeedVisualizer.m_GuideTxtEnd->SetColor(endColor);
            this->m_CutChainSawFeedVisualizer.m_GuideTxtChainBase->SetColor(chainBaseColor);
            this->m_CutChainSawFeedVisualizer.m_GuideTxtChainEnd->SetColor(chainEndColor);

            this->m_CutChainSawFeedVisualizer.m_GuideTxtFaceEdgeDepth1->SetColor(faceEdgeTxt1Color);
            this->m_CutChainSawFeedVisualizer.m_GuideTxtFaceEdgeDepth2->SetColor(faceEdgeTxt2Color);

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
        // m_LineDepthChainBase = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        // m_LineDepthChainEnd = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));

        m_LineDepthFaceEdge1 = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LineDepthFaceEdge2 = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));

        m_LineIntersect->SetColor(GOColor::CYAN);
        // m_LineDepthChainBase->SetColor(GOColor::YELLOW);
        // m_LineDepthChainEnd->SetColor(GOColor::YELLOW);
        m_LineDepthFaceEdge1->SetColor(GOColor::YELLOW);
        m_LineDepthFaceEdge2->SetColor(GOColor::YELLOW);

        m_AllPrimitives.push_back(m_LineIntersect);
        // m_AllPrimitives.push_back(m_LineDepthChainBase);
        // m_AllPrimitives.push_back(m_LineDepthChainEnd);
        m_AllPrimitives.push_back(m_LineDepthFaceEdge1);
        m_AllPrimitives.push_back(m_LineDepthFaceEdge2);

        Deactivate();
    }

    CutChainSawFeedVisualizer::CutChainSawFeedVisualizer(){
        // Text
        m_GuideTxtEnd = GOText::Add("End", GOPoint(0.f, 0.f, 0.f));
        m_GuideTxtChainBase = GOText::Add("ChainBase", GOPoint(0.f, 0.f, 0.f));
        m_GuideTxtChainEnd = GOText::Add("ChainEnd", GOPoint(0.f, 0.f, 0.f));

        m_GuideTxtFaceEdgeDepth1 = GOText::Add("FaceEdgeDepth1", GOPoint(0.f, 0.f, 0.f));
        m_GuideTxtFaceEdgeDepth2 = GOText::Add("FaceEdgeDepth2", GOPoint(0.f, 0.f, 0.f));

        m_GuideTxtEnd->SetColor(GOColor::WHITE);
        m_GuideTxtChainBase->SetColor(GOColor::WHITE);
        m_GuideTxtChainEnd->SetColor(GOColor::WHITE);

        m_GuideTxtFaceEdgeDepth1->SetColor(GOColor::WHITE);
        m_GuideTxtFaceEdgeDepth2->SetColor(GOColor::WHITE);

        m_AllPrimitives.push_back(m_GuideTxtEnd);
        m_AllPrimitives.push_back(m_GuideTxtChainBase);
        m_AllPrimitives.push_back(m_GuideTxtChainEnd);

        m_AllPrimitives.push_back(m_GuideTxtFaceEdgeDepth1);
        m_AllPrimitives.push_back(m_GuideTxtFaceEdgeDepth2);

        m_LineChainNormal = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LineChainNormal->SetColor(GOColor::BLUE);
        m_AllPrimitives.push_back(m_LineChainNormal);

        Deactivate();
    }

    bool FabFeed::ComputeCutCircularSawFeed()
    {
        AIAC_INFO("ComputeCutCircularSawFeed>>>>");
        return true;
    }

} // namespace AIAC