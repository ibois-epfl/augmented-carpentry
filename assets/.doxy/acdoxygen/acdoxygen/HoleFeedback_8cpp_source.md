

# File HoleFeedback.cpp

[**File List**](files.md) **>** [**AIAC**](dir_21da83368f7816722f2b707a7b03c84f.md) **>** [**Feedback**](dir_2e808e595a766fe55342199a604574e7.md) **>** [**HoleFeedback.cpp**](HoleFeedback_8cpp.md)

[Go to the documentation of this file](HoleFeedback_8cpp.md)


```C++
// #####################################################################
// >>>>>>>>>>>>>>>>>>>>> BEGINNING OF LEGAL NOTICE >>>>>>>>>>>>>>>>>>>>>
//######################################################################
//
// This source file, along with its associated content, was authored by
// Andrea Settimi, Hong-Bin Yang, Naravich Chutisilp, and numerous other
// contributors. The code was originally developed at the Laboratory for
// Timber Construction (IBOIS, director: Prof. Yves Weinand) at the School of 
// Architecture, Civil and Environmental Engineering (ENAC) at the Swiss
// Federal Institute of Technology in Lausanne (EPFL) for the Doctoral
// Research "Augmented Carpentry" (PhD researcher: Andrea Settimi,
// co-director: Dr. Julien Gamerro, director: Prof. Yves Weinand).
//
// Although the entire repository is distributed under the GPL license,
// these particular source files may also be used under the terms of the
// MIT license. By accessing or using this file, you agree to the following:
//
// 1. You may reproduce, modify, and distribute this file in accordance
//    with the terms of the MIT license.
// 2. You must retain this legal notice in all copies or substantial
//    portions of this file.
// 3. This file is provided "AS IS," without any express or implied
//    warranties, including but not limited to the implied warranties of
//    merchantability and fitness for a particular purpose.
//
// If you cannot or will not comply with the above conditions, you are
// not permitted to use this file. By proceeding, you acknowledge and
// accept all terms and conditions herein.
//
//######################################################################
// <<<<<<<<<<<<<<<<<<<<<<< END OF LEGAL NOTICE <<<<<<<<<<<<<<<<<<<<<<<<
// #####################################################################
//
#include "AIAC/Application.h"
#include "HoleFeedback.h"

namespace AIAC
{
    HoleFeedbackText::HoleFeedbackText()
    {
        this->m_InfoText = GOText::Add("///", GOPoint(0.f, 0.f, 0.f));
        this->m_InfoText->SetTextSize(GOTextSize::ExtraSmall);
        this->m_InfoText->SetColor(GOColor::WHITE);

        this->m_AllPrimitives.push_back(this->m_InfoText);

        this->Deactivate();
    }

    HoleFeedbackPosition::HoleFeedbackPosition()
    {
        this->m_HoleLine2ToolEnd_A = GOPoint::Add(0.f, 0.f, 0.f);
        this->m_HoleLine2ToolEnd_B = GOPoint::Add(0.f, 0.f, 0.f);
        this->m_HoleLine2ToolEnd = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));

        this->m_HoleLine2ToolStart_A = GOPoint::Add(0.f, 0.f, 0.f);
        this->m_HoleLine2ToolStart_B = GOPoint::Add(0.f, 0.f, 0.f);
        this->m_HoleLine2ToolStart = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));

        this->m_HoleLine2ToolEnd->SetColor(GOColor::RED_TRANSP07);
        this->m_HoleLine2ToolStart->SetColor(GOColor::YELLOW_TRANSP07);
        this->m_HoleLine2ToolEnd_A->SetColor(GOColor::YELLOW_TRANSP07);
        this->m_HoleLine2ToolEnd_B->SetColor(GOColor::PINK_TRANSP07);
        this->m_HoleLine2ToolStart_A->SetColor(GOColor::YELLOW_TRANSP07);
        this->m_HoleLine2ToolStart_B->SetColor(GOColor::PINK_TRANSP07);

        this->m_HoleLine2ToolEnd->SetWeight(GOWeight::Medium);
        this->m_HoleLine2ToolStart->SetWeight(GOWeight::Medium);
        this->m_HoleLine2ToolEnd_A->SetWeight(GOWeight::MediumThick);
        this->m_HoleLine2ToolEnd_B->SetWeight(GOWeight::MediumThick);
        this->m_HoleLine2ToolStart_A->SetWeight(GOWeight::MediumThick);
        this->m_HoleLine2ToolStart_B->SetWeight(GOWeight::MediumThick);

        this->m_AllPrimitives.push_back(this->m_HoleLine2ToolStart_A);
        this->m_AllPrimitives.push_back(this->m_HoleLine2ToolStart_B);
        this->m_AllPrimitives.push_back(this->m_HoleLine2ToolStart);
        this->m_AllPrimitives.push_back(this->m_HoleLine2ToolEnd_A);
        this->m_AllPrimitives.push_back(this->m_HoleLine2ToolEnd_B);
        this->m_AllPrimitives.push_back(this->m_HoleLine2ToolEnd);

        this->Deactivate();
    }

    HoleFeedbackRotation::HoleFeedbackRotation()
    {
        this->m_GUILineOrientation_A = GOPoint::Add(0.f, 0.f, 0.f);
        this->m_GUILineOrientation_B = GOPoint::Add(0.f, 0.f, 0.f);
        this->m_GUILineOrientation = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        
        this->m_GUILineOrientation_A->SetColor(GOColor::YELLOW_TRANSP07);
        this->m_GUILineOrientation_B->SetColor(GOColor::PINK_TRANSP07);
        this->m_GUILineOrientation->SetColor(GOColor::MAGENTA_TRANSP07);
        
        this->m_GUILineOrientation_A->SetWeight(GOWeight::MediumThick);
        this->m_GUILineOrientation_B->SetWeight(GOWeight::MediumThick);
        this->m_GUILineOrientation->SetWeight(GOWeight::Medium);

        this->m_AllPrimitives.push_back(this->m_GUILineOrientation_A);
        this->m_AllPrimitives.push_back(this->m_GUILineOrientation_B);
        this->m_AllPrimitives.push_back(this->m_GUILineOrientation);

        this->Deactivate();
    }

    HoleFeedback::HoleFeedback()
    {
        this->m_DrillBitLineAxis = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        this->m_HoleLineAxis = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));

        this->m_DrillBitLineAxis->SetVisibility(false);
        this->m_HoleLineAxis->SetVisibility(false);

        this->Deactivate();
    }

    void HoleFeedback::Update()
    {
        auto hole = dynamic_cast<TimberInfo::Hole*>(AC_FF_COMP);
        float scaleF = AIAC::Config::Get<float>(AIAC::Config::SEC_AIAC, AIAC::Config::SCALE_FACTOR, 1.0f);

        this->m_VisPosition.m_HoleLine2ToolStart_A->SetPosition(*AC_FF_TOOL->GetData<DrillBitData>().TooltipGO);
        this->m_VisPosition.m_HoleLine2ToolStart_B->SetPosition(*hole->GetStartPointGO());
        this->m_VisPosition.m_HoleLine2ToolStart->SetPts(
            *AC_FF_TOOL->GetData<DrillBitData>().TooltipGO,    // start
            *hole->GetStartPointGO());                         // end
        this->m_VisPosition.m_HoleLine2ToolEnd_A->SetPosition(*AC_FF_TOOL->GetData<DrillBitData>().EattipGO);
        this->m_VisPosition.m_HoleLine2ToolEnd_B->SetPosition(*hole->GetEndPointGO());
        this->m_VisPosition.m_HoleLine2ToolEnd->SetPts(
            *AC_FF_TOOL->GetData<DrillBitData>().EattipGO,    // start
            *hole->GetEndPointGO());                           // end
        this->m_DrillBitLineAxis->SetPts(
            *AC_FF_TOOL->GetData<DrillBitData>().ToolbaseGO,   // start
            *AC_FF_TOOL->GetData<DrillBitData>().TooltipGO);   // end
        this->m_HoleLineAxis->SetPts(
            *hole->GetStartPointGO(),                          // start
            *hole->GetEndPointGO());                           // end

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

        this->m_VisRotation.m_GUILineOrientation->SetPts(
            this->m_DrillBitLineAxis->GetPStart(),  // start
            this->m_HoleLineAxis->GetPStart());     // end
        glm::vec3 vectGUITrans = glm::vec3(midPtToolAxis.x - this->m_DrillBitLineAxis->GetPStart().X(),
                                           midPtToolAxis.y - this->m_DrillBitLineAxis->GetPStart().Y(),
                                           midPtToolAxis.z - this->m_DrillBitLineAxis->GetPStart().Z());
        this->m_VisRotation.m_GUILineOrientation->Translate(vectGUITrans);
        this->m_VisRotation.m_GUILineOrientation_A->SetPosition(
            this->m_VisRotation.m_GUILineOrientation->GetPStart()
        );
        this->m_VisRotation.m_GUILineOrientation_B->SetPosition(
            this->m_VisRotation.m_GUILineOrientation->GetPEnd()
        );

        // (i) start distance
        float dist = this->m_VisPosition.m_HoleLine2ToolStart->GetLength();
        float distScaled = dist / scaleF;
        int distScaledMM = std::round(distScaled * 1000.f);
        if (distScaledMM > 99) distScaledMM = 99;
        std::string distScaledMMStr = std::to_string(distScaledMM);
        if (distScaledMMStr.size() == 1)
            distScaledMMStr = "0" + distScaledMMStr;

        // (ii) detect if inside
        float angle = this->m_VisPosition.m_HoleLine2ToolStart->ComputeAngle(this->m_VisPosition.m_HoleLine2ToolEnd);

        // (iii) angle
        float angleOrient = this->m_DrillBitLineAxis->ComputeAngle(this->m_HoleLineAxis);
        int angleOrientRounded = angleOrient;
        if (angleOrientRounded > 99) angleOrientRounded = 99;
        std::string angleOrientRoundedStr = std::to_string(angleOrientRounded);
        if (angleOrientRoundedStr.size() == 1) angleOrientRoundedStr = "0" + angleOrientRoundedStr;

        // (iv) depth
        float depthLeft = this->m_HoleLineAxis->GetPStart().DistanceTo(*AC_FF_TOOL->GetData<DrillBitData>().EattipGO);
        float holeLength = this->m_HoleLineAxis->GetLength();
        float depthDrilled = holeLength - depthLeft;
        float depthDrilledScaled = depthDrilled / scaleF;
        int depthDrilledScaledMM = std::round(depthDrilledScaled * 1000.f);
        std::string depthDrilledScaledMMStr = std::to_string(depthDrilledScaledMM);

        // >>>>>>>>>>>>>>>>>
        // (v) computed/visual feedbacks
        this->m_VisText.m_InfoText->SetColor(GOColor::WHITE);
        this->m_VisPosition.m_HoleLine2ToolEnd_A->SetColor(GOColor::YELLOW_TRANSP07);
        this->m_VisPosition.m_HoleLine2ToolEnd_B->SetColor(GOColor::PINK_TRANSP07);
        this->m_VisPosition.m_HoleLine2ToolStart_A->SetColor(GOColor::YELLOW_TRANSP07);
        this->m_VisPosition.m_HoleLine2ToolStart_B->SetColor(GOColor::PINK_TRANSP07);

        if ((180.f - this->m_InsideOutDetection) < angle && angle < (180.f + m_InsideOutDetection))
        {
            this->m_VisPosition.m_HoleLine2ToolStart->SetVisibility(false);
            this->m_VisPosition.m_HoleLine2ToolStart_A->SetVisibility(false);
            this->m_VisPosition.m_HoleLine2ToolStart_B->SetVisibility(false);

            // here we are inside the hole
            distScaledMMStr = "00";
            if (depthDrilled < 0.f)
            {
                this->m_VisPosition.m_HoleLine2ToolEnd->SetColor(GOColor::RED_TRANSP07);
                this->m_VisPosition.m_HoleLine2ToolEnd_A->SetColor(GOColor::RED_TRANSP07);
                this->m_VisPosition.m_HoleLine2ToolEnd_B->SetColor(GOColor::RED_TRANSP07);
                this->m_VisText.m_InfoText->SetColor(GOColor::RED);
            }
            else
                this->m_VisPosition.m_HoleLine2ToolEnd->SetColor(GOColor::GREEN);
        }
        else
        {
            this->m_VisPosition.m_HoleLine2ToolEnd->SetVisibility(false);
            this->m_VisPosition.m_HoleLine2ToolEnd_A->SetVisibility(false);
            this->m_VisPosition.m_HoleLine2ToolEnd_B->SetVisibility(false);

            // here we are still outside
            if (depthDrilled > 0.f)
                this->m_VisPosition.m_HoleLine2ToolStart->SetColor(GOColor::YELLOW_TRANSP07);
            else
            {
                this->m_VisPosition.m_HoleLine2ToolStart->SetColor(GOColor::RED_TRANSP07);
                this->m_VisText.m_InfoText->SetColor(GOColor::RED);
                this->m_VisPosition.m_HoleLine2ToolStart_A->SetColor(GOColor::RED_TRANSP07);
                this->m_VisPosition.m_HoleLine2ToolStart_B->SetColor(GOColor::RED_TRANSP07);
            }
        }
        
        // if the orientation is under 1 degree, change the color to green
        this->m_VisRotation.m_GUILineOrientation_A->SetColor(GOColor::YELLOW_TRANSP07);
        this->m_VisRotation.m_GUILineOrientation_B->SetColor(GOColor::PINK_TRANSP07);
        if (angleOrient < this->m_OrientationTolerance)
        {
            this->m_VisRotation.m_GUILineOrientation->SetColor(GOColor::GREEN);
            this->m_VisRotation.m_GUILineOrientation_A->SetColor(GOColor::GREEN_TRANSP07);
            this->m_VisRotation.m_GUILineOrientation_B->SetColor(GOColor::GREEN_TRANSP07);
        }
        else if (this->m_OrientationTolerance < angleOrient && angleOrient < 5.f)
            this->m_VisRotation.m_GUILineOrientation->SetColor(GOColor::YELLOW_TRANSP07);
        else if (angleOrient < 10.f && angleOrient >= 5.f)
        {
            this->m_VisRotation.m_GUILineOrientation->SetColor(GOColor::ORANGE);
            this->m_VisText.m_InfoText->SetColor(GOColor::ORANGE);
        }
        else if (angleOrient >= 10.f)
        {
            this->m_VisRotation.m_GUILineOrientation->SetColor(GOColor::RED_TRANSP07);
            this->m_VisText.m_InfoText->SetColor(GOColor::RED);
        }
        else
            this->m_VisRotation.m_GUILineOrientation->SetColor(GOColor::MAGENTA_TRANSP07);

        // text setting
        std::string test = \
            " s:" + distScaledMMStr + \
            "/a:" + angleOrientRoundedStr + \
            "/e:" + depthDrilledScaledMMStr;
        this->m_VisText.m_InfoText->SetText(test);
        this->m_VisText.m_InfoText->SetAnchor(midPtToolAxis);
    }

    void HoleFeedback::Activate()
    {
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
```


