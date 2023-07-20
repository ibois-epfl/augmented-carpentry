#include "FabFeed.h"
#include "AIAC/Log.h"
#include "AIAC/Application.h"
#include "AIAC/GOSys/GOPrimitive.h"
#include "AIAC/Config.h"

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
         *    x Tb
         *     \
         *      \
         *       \
         *        \
         *         \
         *          x Tt
         *          ..
         *          .  .v2
         *          .    .
         *          .     x Hs
         *       v1 .    /
         *          .   /
         *          .  /
         *          . /
         *          ./
         *          x He
         * 
         */
        auto hole = dynamic_cast<TimberInfo::Hole*>(AC_FF_COMP);
        
        this->m_HoleLine2Start->SetPts(*AC_FF_TOOL->GetData<DrillBitData>().TooltipGO,
                                     *hole->GetStartPointGO());
        this->m_HoleLine2Start->InitGLObject();

        this->m_HoleLine2End->SetPts(*AC_FF_TOOL->GetData<DrillBitData>().TooltipGO,
                                     *hole->GetEndPointGO());
        this->m_HoleLine2End->InitGLObject();



        

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