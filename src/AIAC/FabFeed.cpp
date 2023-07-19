#include "FabFeed.h"
#include "AIAC/Log.h"
#include "AIAC/Application.h"
#include "AIAC/GOSys/GOPrimitive.h"

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
        auto hole = dynamic_cast<TimberInfo::Hole*>(AC_FF_COMP);
        // auto testHole = hole->GetStartPointGO();


        // auto comp = AC_FABFEED_COMP;
        // implicit cast Component to Hole
        // auto test = AC_FF_HOLE->GetStartPointGO();
        float distStartToolTip = AC_FF_TOOL->GetData<DrillBitData>().TooltipGO->DistanceTo(*hole->GetStartPointGO());
        // float distScaled = distStartToolTip * (AIAC::Config::Get<float>(AIAC::Config::SEC_AIAC, AIAC::Config::SCALE_FACTOR));
        float distScaled = distStartToolTip * 50;

        AIAC_INFO("distances: {0}", distScaled);

        // auto hole = std::dynamic_pointer_cast<TimberInfo::Hole>(AC_FABFEED_COMP);
        // AC_FABFEED_HOLE->GetStartPointGO();

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