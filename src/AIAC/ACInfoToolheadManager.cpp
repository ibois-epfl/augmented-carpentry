#include "AIAC/ACInfoToolheadManager.h"
#include "AIAC/Config.h"
#include "utils/utils.h"


namespace AIAC
{
    void ACInfoToolheadManager::LoadToolheadModels()
    {
        std::string datasetDir = AIAC::Config::Get<std::string>(AIAC::Config::SEC_TTOOL,
                                                                AIAC::Config::DATASET_DIR);
        std::vector<std::string> toolheadPaths = GetFolderPaths(datasetDir);



        for (auto& toolheadPath : toolheadPaths)
        {
            std::string acitPath = GetFilePaths(toolheadPath, ".acit")[0];
            std::string objPath = GetFilePaths(toolheadPath, ".obj")[0];
            std::shared_ptr<ACInfoToolhead> acInfoToolhead = std::make_shared<ACInfoToolhead>(acitPath,
                                                                                              objPath);
            AIAC_INFO("Loaded toolhead model: {}", acInfoToolhead->GetName());
            // this->m_ACInfoToolheadMap[acInfoToolhead->GetName()] = acInfoToolhead;
        }
    }
}