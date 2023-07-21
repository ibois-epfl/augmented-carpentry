#include "FabFeed.h"
#include "AIAC/Application.h"
#include "AIAC/GOSys/GOPrimitive.h"
#include "AIAC/Log.h"

namespace AIAC
{
    bool FabFeed::Compute()
    {
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
            if (AC_FF_COMP->GetTypeString() == "CUT")
                return ComputeCutChainSawFeed();
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
        AIAC_INFO("ComputeCutChainSawFeed>>>>");
        return true;
    }

    bool FabFeed::ComputeCutCircularSawFeed()
    {
        AIAC_INFO("ComputeCutCircularSawFeed>>>>");
        return true;
    }

} // namespace AIAC