

# File ACInfoToolheadManager.cpp

[**File List**](files.md) **>** [**AIAC**](dir_21da83368f7816722f2b707a7b03c84f.md) **>** [**ACInfoToolheadManager.cpp**](ACInfoToolheadManager_8cpp.md)

[Go to the documentation of this file](ACInfoToolheadManager_8cpp.md)


```C++
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
#include "AIAC/ACInfoToolheadManager.h"
#include "AIAC/Config.h"
#include "utils/utils.h"


namespace AIAC
{
    void ACInfoToolheadManager::LoadToolheadModels()
    {
        if (!this->m_ACInfoToolheadMap.empty())
            this->m_ACInfoToolheadMap.clear();

        std::string configPath = AIAC::Config::Get<std::string>(AIAC::Config::SEC_TTOOL,
                                                                AIAC::Config::CONFIG_FILE,
                                                                "deps/TTool/assets/config.yml");
        std::string ttoolRootPath = AIAC::Config::Get<std::string>(AIAC::Config::SEC_TTOOL,
                                                                   AIAC::Config::TTOOL_ROOT_PATH,
                                                                   "deps/TTool/assets/toolheads");
        std::vector<std::string> toolheadACITPaths = ParseConfigFile(configPath, "acitFiles");
        std::vector<std::string> toolheadOBJPaths = ParseConfigFile(configPath, "modelFiles");
        
        for (int i = 0; i < toolheadOBJPaths.size(); i++)
        {
            std::shared_ptr<ACInfoToolhead> acInfoToolhead = std::make_shared<ACInfoToolhead>(ttoolRootPath + "/" + toolheadACITPaths[i],
                                                                                              ttoolRootPath + "/" + toolheadOBJPaths[i],
                                                                                              (i+1));
            AIAC_INFO("Loading toolhead model: {}", acInfoToolhead->GetName());
            acInfoToolhead->SetVisibility(false);
            this->m_ACInfoToolheadMap.insert(std::make_pair(acInfoToolhead->GetName(), acInfoToolhead));
        }
        if (this->m_ACInfoToolheadMap.empty())
            AIAC_ERROR("No toolhead models loaded!");

        // if the config has no names, set the first one as active
        auto cachedToolhead = AIAC::Config::Get<std::string>(AIAC::Config::SEC_TTOOL, AIAC::Config::CACHED_TOOLHEAD);
        if (cachedToolhead.empty())
            this->SetActiveToolhead(this->m_ACInfoToolheadMap.begin()->first);
        else
            this->SetActiveToolhead(cachedToolhead);
    }

    void ACInfoToolheadManager::SetActiveToolhead(const std::string& toolheadName)
    {
        this->m_ActiveACInfoToolhead->SetVisibility(false);
        if (this->m_ACInfoToolheadMap.find(toolheadName) != this->m_ACInfoToolheadMap.end())
        {
            *this->m_ActiveACInfoToolhead = *this->m_ACInfoToolheadMap[toolheadName];
            AIAC::Config::UpdateEntry("TTool", "CachedToolhead", toolheadName);
        }
        else
            AIAC_ERROR("Toolhead model {} not found!", toolheadName);
    }
}
```


