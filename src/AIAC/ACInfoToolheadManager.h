#pragma once

#include "AIAC/ACInfoToolhead.h"

namespace AIAC
{
    class ACInfoToolheadManager
    {
        public:
            ACInfoToolheadManager()
                // : m_ActiveACInfoToolhead(nullptr)
            {
                m_ActiveACInfoToolhead = std::make_shared<ACInfoToolhead>(); 
            };

        public:
            /// @brief Load each toolhead model acit/obj from the dataset dir
            void LoadToolheadModels();

        public:
            /// @brief Set a toolhead model as active by its name
            void SetActiveToolhead(const std::string& toolheadName);
            /// @brief Get the active toolhead model
            inline std::shared_ptr<ACInfoToolhead> GetActiveToolhead() const { return this->m_ActiveACInfoToolhead; }
            /// @brief Get the toolhead model by its name
            inline std::shared_ptr<ACInfoToolhead> GetToolhead(const std::string& toolheadName) const { return this->m_ACInfoToolheadMap.at(toolheadName); }
            /// @brief Get the active toolhead model's name
            inline std::string GetActiveToolheadName() const { return this->m_ActiveACInfoToolhead->GetName(); }
            /// @brief Get the toolhead's type by its name
            inline ACToolHeadType GetToolheadType(const std::string& toolheadName) const { return this->m_ACInfoToolheadMap.at(toolheadName)->GetType(); }
            /// @brief Get the current active toolhead's type
            inline ACToolHeadType GetActiveToolheadType() const { return this->m_ActiveACInfoToolhead->GetType(); }


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