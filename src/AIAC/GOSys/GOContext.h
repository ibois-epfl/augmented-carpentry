#pragma once

#include "AIAC/GOSys/GOCollection.h"

namespace AIAC
{
    namespace GO
    {
        using GORegistry = std::map<std::string, std::shared_ptr<GOCollection>>;
        using GORegistryPointer = std::unique_ptr<GORegistry>;

        class GOContext
        {
        public:
            GOContext();
            ~GOContext() = default;
        
            void Init();

            inline void GORegistryAdd(std::string name, std::shared_ptr<GOCollection> go) { s_GORegistry->emplace(name, go);}
            inline void GORegistryRemove(std::string name) { s_GORegistry->erase(name); }
            inline void GORegistryClear() { s_GORegistry->clear(); }

        private:
            static GORegistryPointer s_GORegistry;
        };
    }
}