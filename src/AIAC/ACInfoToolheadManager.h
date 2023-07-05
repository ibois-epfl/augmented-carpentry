#pragma once

#include "AIAC/ACInfoToolhead.h"

namespace AIAC
{
    class ACInfoToolheadManager
    {
        public:
            ACInfoToolheadManager()
                : m_ActiveACInfoToolhead(nullptr)
            {};

        public:
            /// @brief Load each toolhead model acit/obj from the dataset dir
            void LoadToolheadModels();

        public:
            /// @brief Set a toolhead model as active by its name
            void SetActiveToolhead(const std::string& toolheadName);
            /// @brief Get the active toolhead model
            inline std::shared_ptr<ACInfoToolhead> GetActiveToolhead() const { return this->m_ActiveACInfoToolhead; }
            /// @brief Get the active toolhead model's name
            inline std::string GetActiveToolheadName() const { return this->m_ActiveACInfoToolhead->GetName(); }
            
            /// @brief Return the  list of names of the toolheads loaded
            inline std::vector<std::string> GetToolheadNames() const
            {
                std::vector<std::string> toolheadNames;
                for (auto& toolhead : this->m_ACInfoToolheadMap)
                {
                    toolheadNames.push_back(toolhead.first);
                }
                return toolheadNames;
            }

        private:
            /// @brief Map of toolhead name to toolhead model of all possible toolheads loaded
            std::map<std::string, std::shared_ptr<ACInfoToolhead>> m_ACInfoToolheadMap;
            /// @brief The active toolhead model
            std::shared_ptr<ACInfoToolhead> m_ActiveACInfoToolhead;
    };
}