#pragma once

#include "AIAC/ACInfoToolhead.h"

namespace AIAC
{
    class ACInfoToolheadManager
    {
        ACInfoToolheadManager();

        public:
            /// @brief Load each toolhead model acit/obj from the dataset dir
            void LoadToolheadModels();

        private:
            /// @brief Map of toolhead name to toolhead model of all possible toolheads loaded
            std::map<std::string, std::shared_ptr<ACInfoToolhead>> m_ACInfoToolheadMap;
    };
}