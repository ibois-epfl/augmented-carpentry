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
        

        // translate DrillBitAxis to the end of the hole
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



        // -------
        // glm::vec3 midPt = this->m_DrillBitLineAxis->GetMidPointValues();
        // this->m_GUILineOrientation->SetPStartValues(midPt.x, midPt.y, midPt.z);
        
        // // get the line normal
        // glm::vec3 lineNormal = this->m_DrillBitLineAxis->GetNormalValues();
        // float xMidNormal = midPt.x + lineNormal.x;
        // float yMidNormal = midPt.y + lineNormal.y;
        // float zMidNormal = midPt.z + lineNormal.z;

        // this->m_GUILineOrientation->SetPEndValues(midPt.x + lineNormal.x,
        //                                           midPt.y + lineNormal.y,
        //                                           midPt.z + lineNormal.z);
        // -------







        this->m_HoleLine2ToolStart->InitGLObject();
        this->m_HoleLine2ToolEnd->InitGLObject();
        this->m_DrillBitLineAxis->InitGLObject();
        this->m_HoleLineAxis->InitGLObject();
        this->m_GUILineOrientation->InitGLObject();

        // (i) start distance
        float dist = this->m_HoleLine2ToolStart->GetLength();
        float distScaled = dist / this->m_ScaleFactor;
        AIAC_INFO(">> start distance: " + std::to_string(distScaled));

        // (ii) detect if inside
        float angle = this->m_HoleLine2ToolStart->ComputeAngle(this->m_HoleLine2ToolEnd);
        AIAC_INFO(">> >> angle tooltips/holeEnds: " + std::to_string(angle));

        // (iii) angle
        float angleOrient = this->m_DrillBitLineAxis->ComputeAngle(this->m_HoleLineAxis);
        AIAC_INFO(">> >> angle drillbit/holeAxis: " + std::to_string(angleOrient));

        // (iv) depth
        float depth = this->m_HoleLine2ToolEnd->GetLength();
        float depthScaled = depth / this->m_ScaleFactor;
        AIAC_INFO(">> depth: " + std::to_string(depthScaled));



        // >>>>>>>>>>>>>>>>>
        if (distScaled < 0.005f)  // TODO: set tolerance var member, 5mm for now
            AIAC_INFO(">> >> >> drillbit is well positioned");  // TODO: set tolerance var member
        else if (170.f < angle && angle < 190.f)
            AIAC_INFO(">> >> >> drillbit is inside and correct oriented");




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