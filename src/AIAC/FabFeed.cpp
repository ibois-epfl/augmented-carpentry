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

        this->m_HoleLine2Start->SetPts(*AC_FF_TOOL->GetData<DrillBitData>().TooltipGO,  // start
                                       *hole->GetStartPointGO());                       // end
        this->m_HoleLine2Start->InitGLObject();

        this->m_HoleLine2End->SetPts(*AC_FF_TOOL->GetData<DrillBitData>().TooltipGO,    // start
                                     *hole->GetEndPointGO());                           // end
        this->m_HoleLine2End->InitGLObject();

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
        AIAC_INFO("ComputeCutChainSawFeed>>>>");
        return true;
    }

    bool FabFeed::ComputeCutCircularSawFeed()
    {
        AIAC_INFO("ComputeCutCircularSawFeed>>>>");
        return true;
    }

} // namespace AIAC