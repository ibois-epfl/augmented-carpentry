#include "AIAC/ACInfoToolheadManager.h"
#include "AIAC/Config.h"
#include "utils/utils.h"


namespace AIAC
{
    void ACInfoToolheadManager::LoadToolheadModels()
    {
        if (!this->m_ACInfoToolheadMap.empty())
            this->m_ACInfoToolheadMap.clear();

        std::string datasetDir = AIAC::Config::Get<std::string>(AIAC::Config::SEC_TTOOL,
                                                                AIAC::Config::DATASET_DIR);
        std::vector<std::string> toolheadPaths = GetFolderPaths(datasetDir);

        for (auto& toolheadPath : toolheadPaths)
        {
            std::string acitPath = GetFilePaths(toolheadPath, ".acit")[0];
            std::string objPath = GetFilePaths(toolheadPath, ".obj")[0];
            std::shared_ptr<ACInfoToolhead> acInfoToolhead = std::make_shared<ACInfoToolhead>(acitPath,
                                                                                              objPath);
            AIAC_INFO("Loading toolhead model: {}", acInfoToolhead->GetName());
            this->m_ACInfoToolheadMap.insert(std::make_pair(acInfoToolhead->GetName(), acInfoToolhead));
        }
    }

    void ACInfoToolheadManager::SetActiveToolhead(const std::string& toolheadName)
    {
        if (this->m_ACInfoToolheadMap.find(toolheadName) != this->m_ACInfoToolheadMap.end())
            this->m_ActiveACInfoToolhead = this->m_ACInfoToolheadMap[toolheadName];
        else
            AIAC_ERROR("Toolhead model {} not found!", toolheadName);
    }
}