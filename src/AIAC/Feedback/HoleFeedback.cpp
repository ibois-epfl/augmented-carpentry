#include "AIAC/Application.h"
#include "HoleFeedback.h"

namespace AIAC {
    HoleFeedbackVisualizer::HoleFeedbackVisualizer() {
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

        // Add everything that need to show to m_AllPrimitives
        for (auto& pt : this->m_GUIPointsTranslation)
            this->m_AllPrimitives.push_back(pt);
        this->m_AllPrimitives.push_back(this->m_GUILineOrientation);
        this->m_AllPrimitives.push_back(this->m_InfoText);

        Deactivate();
    }

    void HoleFeedback::Update() {
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

        auto goData = this->m_Visualizer;

        goData.m_HoleLine2ToolStart->SetPts(*AC_FF_TOOL->GetData<DrillBitData>().TooltipGO,  // start
                                                        *hole->GetStartPointGO());                       // end
        goData.m_HoleLine2ToolEnd->SetPts(*AC_FF_TOOL->GetData<DrillBitData>().TooltipGO,    // start
                                                      *hole->GetEndPointGO());                           // end
        goData.m_DrillBitLineAxis->SetPts(*AC_FF_TOOL->GetData<DrillBitData>().ToolbaseGO,   // start
                                                      *AC_FF_TOOL->GetData<DrillBitData>().TooltipGO);   // end
        goData.m_HoleLineAxis->SetPts(*hole->GetStartPointGO(),                              // start
                                                  *hole->GetEndPointGO());                               // end
        
        // start orientation guidance
        glm::vec3 toolTipVec = goData.m_DrillBitLineAxis->GetPEnd().GetPosition();
        glm::vec3 midPtToolAxisVec = goData.m_HoleLine2ToolStart->GetMidPointValues();
        glm::vec3 midPtToolAxisVecHalf1 = glm::vec3((toolTipVec.x + midPtToolAxisVec.x) / 2.f,
                                            (toolTipVec.y + midPtToolAxisVec.y) / 2.f,
                                            (toolTipVec.z + midPtToolAxisVec.z) / 2.f);
        glm::vec3 holeStartVec = goData.m_HoleLineAxis->GetPStart().GetPosition();
        goData.m_GUIPointsTranslation[0]->SetPosition(toolTipVec);
        goData.m_GUIPointsTranslation[1]->SetPosition(midPtToolAxisVecHalf1);
        goData.m_GUIPointsTranslation[2]->SetPosition(midPtToolAxisVec);

        // angle orientation guidance
        glm::vec3 midPtToolAxis = goData.m_DrillBitLineAxis->GetMidPointValues();
        glm::vec3 translVec = glm::vec3(goData.m_HoleLineAxis->GetPEnd().X() - goData.m_DrillBitLineAxis->GetPEnd().X(),
                                       goData.m_HoleLineAxis->GetPEnd().Y() - goData.m_DrillBitLineAxis->GetPEnd().Y(),
                                       goData.m_HoleLineAxis->GetPEnd().Z() - goData.m_DrillBitLineAxis->GetPEnd().Z());
        goData.m_DrillBitLineAxis->Translate(translVec);
        float lengthHole = goData.m_HoleLineAxis->GetLength();
        float lengthDrillBit = goData.m_DrillBitLineAxis->GetLength();
        float lengthDiff = lengthHole - lengthDrillBit;
        goData.m_DrillBitLineAxis->ExtendFromStart(lengthDiff);

        goData.m_GUILineOrientation->SetPts(goData.m_DrillBitLineAxis->GetPStart(),  // start
                                           goData.m_HoleLineAxis->GetPStart());     // end
        glm::vec3 vectGUITrans = glm::vec3(midPtToolAxis.x - goData.m_DrillBitLineAxis->GetPStart().X(),
                                           midPtToolAxis.y - goData.m_DrillBitLineAxis->GetPStart().Y(),
                                           midPtToolAxis.z - goData.m_DrillBitLineAxis->GetPStart().Z());
        goData.m_GUILineOrientation->Translate(vectGUITrans);


        goData.m_HoleLine2ToolStart->InitGLObject();
        goData.m_HoleLine2ToolEnd->InitGLObject();
        goData.m_DrillBitLineAxis->InitGLObject();
        goData.m_HoleLineAxis->InitGLObject();
        goData.m_GUILineOrientation->InitGLObject();
        for (auto& pt : goData.m_GUIPointsTranslation)
            pt->InitGLObject();

        // (i) start distance
        float dist = goData.m_HoleLine2ToolStart->GetLength();
        float distScaled = dist / m_ScaleFactor;
        int distScaledMM = std::round(distScaled * 1000.f);
        if (distScaledMM > 99) distScaledMM = 99;
        // make the text always 2 digits like 01, 02, 03, ...
        std::string distScaledMMStr = std::to_string(distScaledMM);
        if (distScaledMMStr.size() == 1) distScaledMMStr = "0" + distScaledMMStr;
        // AIAC_INFO(">> start distance: " + std::to_string(distScaledMMStr));

        // (ii) detect if inside
        float angle = goData.m_HoleLine2ToolStart->ComputeAngle(goData.m_HoleLine2ToolEnd);
        // AIAC_INFO(">> >> angle tooltips/holeEnds: " + std::to_string(angle));

        // (iii) angle
        float angleOrient = goData.m_DrillBitLineAxis->ComputeAngle(goData.m_HoleLineAxis);
        int angleOrientRounded = angleOrient;
        if (angleOrientRounded > 99) angleOrientRounded = 99;
        std::string angleOrientRoundedStr = std::to_string(angleOrientRounded);
        if (angleOrientRoundedStr.size() == 1) angleOrientRoundedStr = "0" + angleOrientRoundedStr;
        // AIAC_INFO(">> >> angle drillbit/holeAxis: " + std::to_string(angleOrientRoundedStr));

        // (iv) depth
        float depthLeft = goData.m_HoleLineAxis->GetPEnd().DistanceTo(*AC_FF_TOOL->GetData<DrillBitData>().TooltipGO);
        float depthLeftScaled = depthLeft / m_ScaleFactor;
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
            for (auto& pt : goData.m_GUIPointsTranslation)
                pt->SetVisibility(false);
        }
        else
        {
            // AIAC_INFO(">> >> >> drillbit is outside");
            for (auto& pt : goData.m_GUIPointsTranslation)
                pt->SetVisibility(true);
        }
        if (angleOrient < 0.5f)  // TODO: set tolerance var member
            goData.m_GUILineOrientation->SetVisibility(false);
        else
            goData.m_GUILineOrientation->SetVisibility(true);

        // -- text
        std::string test = " s:" + distScaledMMStr + "/a:" + angleOrientRoundedStr + "/e:" + depthLeftScaledMMStr;
        goData.m_InfoText->SetText(test);
        goData.m_InfoText->SetAnchor(midPtToolAxis);

    }

    void HoleFeedback::Activate() {
        Update();
        m_Visualizer.Activate();
    }

    void HoleFeedback::Deactivate() {
        m_Visualizer.Deactivate();
    }
}
