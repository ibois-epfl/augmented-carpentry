// #####################################################################
// >>>>>>>>>>>>>>>>>>>>> BEGINNING OF LEGAL NOTICE >>>>>>>>>>>>>>>>>>>>>
//######################################################################
//
// This source file, along with its associated content, was authored by
// Andrea Settimi, Hong-Bin Yang, Naravich Chutisilp, and numerous other
// contributors. The code was originally developed at the Laboratory for
// Timber Construction (IBOIS, director: Prof. Yves Weinand) at the School of 
// Architecture, Civil and Environmental Engineering (ENAC) at the Swiss
// Federal Institute of Technology in Lausanne (EPFL) for the Doctoral
// Research "Augmented Carpentry" (PhD researcher: Andrea Settimi,
// co-director: Dr. Julien Gamerro, director: Prof. Yves Weinand).
//
// Although the entire repository is distributed under the GPL license,
// these particular source files may also be used under the terms of the
// MIT license. By accessing or using this file, you agree to the following:
//
// 1. You may reproduce, modify, and distribute this file in accordance
//    with the terms of the MIT license.
// 2. You must retain this legal notice in all copies or substantial
//    portions of this file.
// 3. This file is provided "AS IS," without any express or implied
//    warranties, including but not limited to the implied warranties of
//    merchantability and fitness for a particular purpose.
//
// If you cannot or will not comply with the above conditions, you are
// not permitted to use this file. By proceeding, you acknowledge and
// accept all terms and conditions herein.
//
//######################################################################
// <<<<<<<<<<<<<<<<<<<<<<< END OF LEGAL NOTICE <<<<<<<<<<<<<<<<<<<<<<<<
// #####################################################################
//
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