#include "AIAC/Application.h"
#include "HoleFeedback.h"

namespace AIAC {
    HoleFeedbackVisualizer::HoleFeedbackVisualizer() {
        auto pt1 = GOPoint::Add(0.f, 0.f, 0.f);
        auto pt2 = GOPoint::Add(5.f, 5.f, 5.f);
        pt1->SetVisibility(false);
        pt2->SetVisibility(false);
        
        this->m_InfoText = GOText::Add("///", *pt1);
        this->m_InfoText->SetColor(GOColor::WHITE);

        this->m_HoleLine2ToolStart = GOLine::Add(*pt1, *pt2);
        this->m_HoleLine2ToolStart->SetColor(GOColor::YELLOW);
        this->m_HoleLine2ToolEnd = GOLine::Add(*pt1, *pt2);
        this->m_HoleLine2ToolEnd->SetColor(GOColor::RED);
        this->m_DrillBitLineAxis = GOLine::Add(*pt1, *pt2);
        this->m_HoleLineAxis = GOLine::Add(*pt1, *pt2);
        this->m_HoleLineAxis->SetColor(GOColor::GREEN);
        this->m_GUILineOrientation = GOLine::Add(*pt1, *pt2);
        this->m_GUILineOrientation->SetColor(GOColor::WHITE);
        
        this->m_HoleLine2ToolStart->SetVisibility(true);  // << position guidance
        this->m_HoleLine2ToolEnd->SetVisibility(false);
        this->m_GUILineOrientation->SetVisibility(true);
        this->m_DrillBitLineAxis->SetVisibility(false);
        this->m_HoleLineAxis->SetVisibility(false);

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
        float scaleF = AIAC::Config::Get<float>(AIAC::Config::SEC_AIAC, AIAC::Config::SCALE_FACTOR, 50.f);

        this->m_Visualizer.m_HoleLine2ToolStart->SetPts(*AC_FF_TOOL->GetData<DrillBitData>().TooltipGO,  // start
                                           *hole->GetStartPointGO());                       // end
        this->m_Visualizer.m_HoleLine2ToolEnd->SetPts(*AC_FF_TOOL->GetData<DrillBitData>().TooltipGO,    // start
                                         *hole->GetEndPointGO());                           // end
        this->m_Visualizer.m_DrillBitLineAxis->SetPts(*AC_FF_TOOL->GetData<DrillBitData>().ToolbaseGO,   // start
                                         *AC_FF_TOOL->GetData<DrillBitData>().TooltipGO);   // end
        this->m_Visualizer.m_HoleLineAxis->SetPts(*hole->GetStartPointGO(),                              // start
                                     *hole->GetEndPointGO());                               // end

        // angle orientation guidance
        glm::vec3 midPtToolAxis = this->m_Visualizer.m_DrillBitLineAxis->GetMidPointValues();
        glm::vec3 translVec = glm::vec3(this->m_Visualizer.m_HoleLineAxis->GetPEnd().X() - this->m_Visualizer.m_DrillBitLineAxis->GetPEnd().X(),
                                        this->m_Visualizer.m_HoleLineAxis->GetPEnd().Y() - this->m_Visualizer.m_DrillBitLineAxis->GetPEnd().Y(),
                                        this->m_Visualizer.m_HoleLineAxis->GetPEnd().Z() - this->m_Visualizer.m_DrillBitLineAxis->GetPEnd().Z());
        this->m_Visualizer.m_DrillBitLineAxis->Translate(translVec);
        float lengthHole = this->m_Visualizer.m_HoleLineAxis->GetLength();
        float lengthDrillBit = this->m_Visualizer.m_DrillBitLineAxis->GetLength();
        float lengthDiff = lengthHole - lengthDrillBit;
        this->m_Visualizer.m_DrillBitLineAxis->ExtendFromStart(lengthDiff);

        this->m_Visualizer.m_GUILineOrientation->SetPts(this->m_Visualizer.m_DrillBitLineAxis->GetPStart(),  // start
                                           this->m_Visualizer.m_HoleLineAxis->GetPStart());     // end
        glm::vec3 vectGUITrans = glm::vec3(midPtToolAxis.x - this->m_Visualizer.m_DrillBitLineAxis->GetPStart().X(),
                                           midPtToolAxis.y - this->m_Visualizer.m_DrillBitLineAxis->GetPStart().Y(),
                                           midPtToolAxis.z - this->m_Visualizer.m_DrillBitLineAxis->GetPStart().Z());
        this->m_Visualizer.m_GUILineOrientation->Translate(vectGUITrans);

        // FIXME: normally you shouldn't call this->m_Visualizer.y yourself
        this->m_Visualizer.m_HoleLine2ToolStart->InitGLObject();
        this->m_Visualizer.m_HoleLine2ToolEnd->InitGLObject();
        this->m_Visualizer.m_DrillBitLineAxis->InitGLObject();
        this->m_Visualizer.m_HoleLineAxis->InitGLObject();
        this->m_Visualizer.m_GUILineOrientation->InitGLObject();

        // (i) start distance
        float dist = this->m_Visualizer.m_HoleLine2ToolStart->GetLength();
        float distScaled = dist / scaleF;
        int distScaledMM = std::round(distScaled * 1000.f);
        if (distScaledMM > 99) distScaledMM = 99;
        // make the text always 2 digits like 01, 02, 03, ...
        std::string distScaledMMStr = std::to_string(distScaledMM);
        if (distScaledMMStr.size() == 1) distScaledMMStr = "0" + distScaledMMStr;

        // (ii) detect if inside
        float angle = this->m_Visualizer.m_HoleLine2ToolStart->ComputeAngle(this->m_Visualizer.m_HoleLine2ToolEnd);

        // (iii) angle
        float angleOrient = this->m_Visualizer.m_DrillBitLineAxis->ComputeAngle(this->m_Visualizer.m_HoleLineAxis);
        int angleOrientRounded = angleOrient;
        if (angleOrientRounded > 99) angleOrientRounded = 99;
        std::string angleOrientRoundedStr = std::to_string(angleOrientRounded);
        if (angleOrientRoundedStr.size() == 1) angleOrientRoundedStr = "0" + angleOrientRoundedStr;

        // (iv) depth
        float depthLeft = this->m_Visualizer.m_HoleLineAxis->GetPEnd().DistanceTo(*AC_FF_TOOL->GetData<DrillBitData>().TooltipGO);
        float holeLength = this->m_Visualizer.m_HoleLineAxis->GetLength();
        float depthDrilled = holeLength - depthLeft;
        float depthDrilledScaled = depthDrilled / scaleF;
        int depthDrilledScaledMM = std::round(depthDrilledScaled * 1000.f);
        std::string depthDrilledScaledMMStr = std::to_string(depthDrilledScaledMM);

        // >>>>>>>>>>>>>>>>>
        // computed feedbacks
        if (160.f < angle && angle < 200.f)  // TODO: set tolerance var member, 20deg for now
        {
            distScaledMMStr = "00";
            if (depthDrilled < 0.f)
                this->m_Visualizer.m_HoleLine2ToolEnd->SetColor(GOColor::RED);
            else
                this->m_Visualizer.m_HoleLine2ToolEnd->SetColor(GOColor::GREEN);
        }
        else
        {
            if (depthDrilled > 0.f)
                this->m_Visualizer.m_HoleLine2ToolStart->SetColor(GOColor::YELLOW);
            else
                this->m_Visualizer.m_HoleLine2ToolStart->SetColor(GOColor::RED);

        }
        if (angleOrient < 0.5f)  // TODO: set tolerance var member
            this->m_Visualizer.m_GUILineOrientation->SetVisibility(false);
        else
            this->m_Visualizer.m_GUILineOrientation->SetVisibility(true);

        // -- text
        std::string test = " s:" + distScaledMMStr + "/a:" + angleOrientRoundedStr + "/e:" + depthDrilledScaledMMStr;
        this->m_Visualizer.m_InfoText->SetText(test);
        this->m_Visualizer.m_InfoText->SetAnchor(midPtToolAxis);
    }

    void HoleFeedback::Activate() {
        Update();
        m_Visualizer.Activate();
    }

    void HoleFeedback::Deactivate() {
        m_Visualizer.Deactivate();
    }
}
