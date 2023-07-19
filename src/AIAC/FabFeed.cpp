#include "FabFeed.h"
#include "AIAC/Log.h"
#include "AIAC/Application.h"

namespace AIAC
{
    bool FabFeed::Compute()
    {
        if (AC_FABFEED_TOOL->GetTypeString() == "DRILLBIT")
            if (AC_FABFEED_COMP->GetTypeString() == "HOLE")
                return ComputeHoleFeed();
            else
                return false;
        else if (AC_FABFEED_TOOL->GetTypeString() == "CIRCULARSAW")
            if (AC_FABFEED_COMP->GetTypeString() == "CUT")
                return ComputeCutCircularSawFeed();
            else
                return false;
        else if (AC_FABFEED_TOOL->GetTypeString() == "SABERSAW")
            if (AC_FABFEED_COMP->GetTypeString() == "CUT")
                return ComputeCutSaberSawFeed();
            else
                return false;
        else if (AC_FABFEED_TOOL->GetTypeString() == "CHAINSAW")
            if (AC_FABFEED_COMP->GetTypeString() == "CUT")
                return ComputeCutChainSawFeed();
            else
                return false;
        else
            return false;
    }

    bool FabFeed::ComputeHoleFeed()
    {
        AIAC_INFO("ComputeHoleFeed>>>>");
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