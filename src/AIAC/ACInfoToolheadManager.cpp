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



        std::string configPath = AIAC::Config::Get<std::string>(AIAC::Config::SEC_TTOOL,
                                                                AIAC::Config::CONFIG_FILE);
        // parse the config file to get the list of acit toolheads from entry "modelFiles"


        std::vector<std::string> toolheadACITPaths = ParseConfigFile(configPath, "acitFiles");
        std::vector<std::string> toolheadOBJPaths = ParseConfigFile(configPath, "modelFiles");



        // for (auto& toolheadPath : toolheadPaths)
        for (int i = 0; i < toolheadOBJPaths.size(); i++)
        {
            std::shared_ptr<ACInfoToolhead> acInfoToolhead = std::make_shared<ACInfoToolhead>(toolheadACITPaths[i],
                                                                                              toolheadOBJPaths[i],
                                                                                              (i+1));
            AIAC_INFO("Loading toolhead model: {}", acInfoToolhead->GetName());
            acInfoToolhead->SetVisibility(false);
            this->m_ACInfoToolheadMap.insert(std::make_pair(acInfoToolhead->GetName(), acInfoToolhead));
        }
        if (this->m_ACInfoToolheadMap.empty())
            AIAC_ERROR("No toolhead models loaded!");
            
        this->m_ActiveACInfoToolhead = this->m_ACInfoToolheadMap.begin()->second;
        this->m_ActiveACInfoToolhead->SetVisibility(true);
    }

    void ACInfoToolheadManager::SetActiveToolhead(const std::string& toolheadName)
    {
        this->m_ActiveACInfoToolhead->SetVisibility(false);
        if (this->m_ACInfoToolheadMap.find(toolheadName) != this->m_ACInfoToolheadMap.end())
        {
            this->m_ActiveACInfoToolhead = this->m_ACInfoToolheadMap[toolheadName];
            this->m_ActiveACInfoToolhead->SetVisibility(true);
        }
        else
            AIAC_ERROR("Toolhead model {} not found!", toolheadName);
    }
}