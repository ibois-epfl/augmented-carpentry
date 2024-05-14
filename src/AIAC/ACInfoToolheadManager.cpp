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
                                                                AIAC::Config::CONFIG_FILE);
        std::string ttoolRootPath = AIAC::Config::Get<std::string>(AIAC::Config::SEC_TTOOL,
                                                                   AIAC::Config::TTOOL_ROOT_PATH);
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
        if (AIAC::Config::Get<std::string>(AIAC::Config::SEC_TTOOL, AIAC::Config::CACHED_TOOLHEAD).empty())
            this->SetActiveToolhead(this->m_ACInfoToolheadMap.begin()->first);
        else
            this->SetActiveToolhead(AIAC::Config::Get<std::string>(AIAC::Config::SEC_TTOOL, AIAC::Config::CACHED_TOOLHEAD));
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