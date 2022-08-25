#include "aiacpch.h"

#include "GOContext.h"


namespace AIAC
{
    namespace GO
    {
        GOContext::GOContext() {}

        void GOContext::Init()
        {
            s_GORegistry = GORegistryPointer();
        }
    }
}