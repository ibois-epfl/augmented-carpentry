#include "aiacpch.h"

#include "AIAC/GOSys/GOCollection.h"

namespace AIAC
{
    namespace GO
    {

        uint32_t GOCollection::CreateKey(std::shared_ptr<GOPrimitive>& goPrimitive)
        {
            uint32_t id = reinterpret_cast<uint32_t>(goPrimitive.get());
            return id;
        }

        void GOCollection::Add(std::shared_ptr<GOPrimitive>& goPrimitive)
        {
            uint32_t id = CreateKey(goPrimitive);
            m_GOCollection.emplace(id, goPrimitive);
        }

        void GOCollection::Remove(uint32_t key)
        {
            m_GOCollection.erase(key);
        }
    }
}