#include "AIAC/Application.h"
#include "HoleFeedback.h"

namespace AIAC
{
    HoleFeedbackText::HoleFeedbackText()
    {
        auto pt1 = GOPoint::Add(0.f, 0.f, 0.f); pt1->SetVisibility(false);
        auto pt2 = GOPoint::Add(5.f, 5.f, 5.f); pt2->SetVisibility(false);
        
        this->m_InfoText = GOText::Add("///", *pt1);
        this->m_InfoText->SetTextSize(GOTextSize::Small);
        this->m_InfoText->SetColor(GOColor::WHITE);

        this->m_AllPrimitives.push_back(this->m_InfoText);

        Deactivate();
    }

    HoleFeedbackPosition::HoleFeedbackPosition()
    {
        auto pt1 = GOPoint::Add(0.f, 0.f, 0.f); pt1->SetVisibility(false);
        auto pt2 = GOPoint::Add(5.f, 5.f, 5.f); pt2->SetVisibility(false);
        
        this->m_HoleLine2ToolEnd = GOLine::Add(*pt1, *pt2);
        this->m_HoleLine2ToolEnd->SetColor(GOColor::RED);

        this->m_HoleLine2ToolStart = GOLine::Add(*pt1, *pt2);
        this->m_HoleLine2ToolStart->SetColor(GOColor::YELLOW);

        this->m_HoleLine2ToolEnd->SetVisibility(false);
        this->m_HoleLine2ToolStart->SetVisibility(true);

        this->m_AllPrimitives.push_back(this->m_HoleLine2ToolStart);

        Deactivate();
    }

    HoleFeedbackRotation::HoleFeedbackRotation()
    {
        auto pt1 = GOPoint::Add(0.f, 0.f, 0.f); pt1->SetVisibility(false);
        auto pt2 = GOPoint::Add(5.f, 5.f, 5.f); pt2->SetVisibility(false);

        this->m_GUILineOrientation = GOLine::Add(*pt1, *pt2);
        this->m_GUILineOrientation->SetColor(GOColor::WHITE);

        this->m_GUILineOrientation->SetVisibility(true);

        this->m_AllPrimitives.push_back(this->m_GUILineOrientation);
    }

    HoleFeedback::HoleFeedback()
    {
        auto pt1 = GOPoint::Add(0.f, 0.f, 0.f); pt1->SetVisibility(false);
        auto pt2 = GOPoint::Add(5.f, 5.f, 5.f); pt2->SetVisibility(false);

        this->m_DrillBitLineAxis = GOLine::Add(*pt1, *pt2);
        this->m_HoleLineAxis = GOLine::Add(*pt1, *pt2);

        this->m_DrillBitLineAxis->SetVisibility(false);
        this->m_HoleLineAxis->SetVisibility(false);
    }

    void HoleFeedback::Update()
    {
        
        auto hole = dynamic_cast<TimberInfo::Hole*>(AC_FF_COMP);
        float scaleF = AIAC::Config::Get<float>(AIAC::Config::SEC_AIAC, AIAC::Config::SCALE_FACTOR, 50.f);

        this->m_VisPosition.m_HoleLine2ToolStart->SetPts(*AC_FF_TOOL->GetData<DrillBitData>().TooltipGO,  // start
                                           *hole->GetStartPointGO());                       // end
        this->m_VisPosition.m_HoleLine2ToolEnd->SetPts(*AC_FF_TOOL->GetData<DrillBitData>().TooltipGO,    // start
                                         *hole->GetEndPointGO());                           // end
        this->m_DrillBitLineAxis->SetPts(*AC_FF_TOOL->GetData<DrillBitData>().ToolbaseGO,   // start
                                         *AC_FF_TOOL->GetData<DrillBitData>().TooltipGO);   // end
        this->m_HoleLineAxis->SetPts(*hole->GetStartPointGO(),                              // start
                                     *hole->GetEndPointGO());                               // end

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

        this->m_VisRotation.m_GUILineOrientation->SetPts(this->m_DrillBitLineAxis->GetPStart(),  // start
                                           this->m_HoleLineAxis->GetPStart());     // end
        glm::vec3 vectGUITrans = glm::vec3(midPtToolAxis.x - this->m_DrillBitLineAxis->GetPStart().X(),
                                           midPtToolAxis.y - this->m_DrillBitLineAxis->GetPStart().Y(),
                                           midPtToolAxis.z - this->m_DrillBitLineAxis->GetPStart().Z());
        this->m_VisRotation.m_GUILineOrientation->Translate(vectGUITrans);

        // FIXME: should this go into the renderer?
        this->m_VisPosition.m_HoleLine2ToolStart->InitGLObject();
        this->m_VisPosition.m_HoleLine2ToolEnd->InitGLObject();
        this->m_DrillBitLineAxis->InitGLObject();
        this->m_HoleLineAxis->InitGLObject();
        this->m_VisRotation.m_GUILineOrientation->InitGLObject();

        // (i) start distance
        float dist = this->m_VisPosition.m_HoleLine2ToolStart->GetLength();
        float distScaled = dist / scaleF;
        int distScaledMM = std::round(distScaled * 1000.f);
        if (distScaledMM > 99) distScaledMM = 99;
        // make the text always 2 digits like 01, 02, 03, ...
        std::string distScaledMMStr = std::to_string(distScaledMM);
        if (distScaledMMStr.size() == 1) distScaledMMStr = "0" + distScaledMMStr;

        // (ii) detect if inside
        float angle = this->m_VisPosition.m_HoleLine2ToolStart->ComputeAngle(this->m_VisPosition.m_HoleLine2ToolEnd);

        // (iii) angle
        float angleOrient = this->m_DrillBitLineAxis->ComputeAngle(this->m_HoleLineAxis);
        int angleOrientRounded = angleOrient;
        if (angleOrientRounded > 99) angleOrientRounded = 99;
        std::string angleOrientRoundedStr = std::to_string(angleOrientRounded);
        if (angleOrientRoundedStr.size() == 1) angleOrientRoundedStr = "0" + angleOrientRoundedStr;

        // (iv) depth
        float depthLeft = this->m_HoleLineAxis->GetPStart().DistanceTo(*AC_FF_TOOL->GetData<DrillBitData>().TooltipGO);
        float holeLength = this->m_HoleLineAxis->GetLength();
        float depthDrilled = holeLength - depthLeft;
        float depthDrilledScaled = depthDrilled / scaleF;
        int depthDrilledScaledMM = std::round(depthDrilledScaled * 1000.f);
        std::string depthDrilledScaledMMStr = std::to_string(depthDrilledScaledMM);

        // >>>>>>>>>>>>>>>>>
        // (v) computed feedbacks
        this->m_VisText.m_InfoText->SetColor(GOColor::WHITE);
        if ((180.f - this->m_InsideOutDetection) < angle && angle < (180.f + m_InsideOutDetection))
        {
            distScaledMMStr = "00";
            this->m_VisPosition.m_HoleLine2ToolStart->SetColor(GOColor::YELLOW);
            if (depthDrilled < 0.f)
            {
                this->m_VisPosition.m_HoleLine2ToolEnd->SetColor(GOColor::RED);
                this->m_VisText.m_InfoText->SetColor(GOColor::RED);
            }
            else
                this->m_VisPosition.m_HoleLine2ToolEnd->SetColor(GOColor::GREEN);
        }
        else
        {
            if (depthDrilled > 0.f)
                this->m_VisPosition.m_HoleLine2ToolStart->SetColor(GOColor::YELLOW);
            else
            {
                this->m_VisPosition.m_HoleLine2ToolStart->SetColor(GOColor::RED);
                this->m_VisText.m_InfoText->SetColor(GOColor::RED);
            }
        }
        if (angleOrient < this->m_OrientationTolerance)
            // this->m_VisRotation.m_GUILineOrientation->SetVisibility(false);
            this->m_VisRotation.Activate();
        else
            // this->m_VisRotation.m_GUILineOrientation->SetVisibility(true);
            this->m_VisRotation.Deactivate();

        std::string test = " s:" + distScaledMMStr + "/a:" + angleOrientRoundedStr + "/e:" + depthDrilledScaledMMStr;
        this->m_VisText.m_InfoText->SetText(test);
        this->m_VisText.m_InfoText->SetAnchor(midPtToolAxis);
    }

    void HoleFeedback::Activate()
    {
        Update();
        this->m_VisText.Activate();
        this->m_VisPosition.Activate();
        this->m_VisRotation.Activate();
    }

    void HoleFeedback::Deactivate()
    {
        this->m_VisText.Deactivate();
        this->m_VisPosition.Deactivate();
        this->m_VisRotation.Deactivate();
    }
}
