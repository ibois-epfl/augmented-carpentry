#include "LayerUtils.h"
#include "utils/VideoRecorder.h"
#include "Config.h"
#include <thread>
#include "Application.h"

namespace AIAC {
    void LayerUtils::OnFrameEnd() {
        // check if the recording flag is set to true
        if(this->m_Recording){
            // capture the frames
            this->m_VideoRecorder->CaptureFrames();
        }
    }

    void LayerUtils::StartRecording(){
        AIAC_INFO("Started Recording");
        // set the recording flag to true
        this->m_Recording = true;
        // get the save path
        std::string savePath = this->GetSaveFolderPath();
        // create the video recorder object
        this->m_VideoRecorder = std::make_unique<AIAC::Utils::VideoRecorder>(savePath);
    };

    void LayerUtils::StopRecording(){
        AIAC_INFO("Stopped Recording");
        // set the recording flag to false
        this->m_Recording = false;
        // create the video from the frames in a separate thread
        std::thread([this]{
            this->m_Processing = true;
            this->m_VideoRecorder->MakeVideoFromFrames();
            // delete the frames folder and video recorder object
            this->m_VideoRecorder.reset();
            this->m_Processing = false;
        }).detach();
    };

    void LayerUtils::SetSaveFolderPath(std::string path){
        // Set the save folder path for the video recorder
        if(path.empty()) {
            AIAC_INFO("Using default path: {}", m_SaveFolderPath);
        } else {
            m_SaveFolderPath = path;
            AIAC_INFO("Using specified path: {}", m_SaveFolderPath);
        }
    };

    void LayerUtils::OnFrameStart(){
        this->GetCurrentToolhead();
    }

    void LayerUtils::GetCurrentToolhead(){
        std::cout << "Getting current toolhead" << std::endl;
        auto toolheadLayer = AIAC_APP.GetLayer<AIAC::LayerToolhead>();
        // Get the active toolhead
        auto activeToolhead = toolheadLayer->ACInfoToolheadManager->GetActiveToolhead();

        // Get the type of the active toolhead
        std::string activeToolheadType = activeToolhead->GetTypeString();
        if (activeToolheadType == "DRILLBIT"){
            auto drillBitData = activeToolhead->GetData<DrillBitData>();
            this->WriteCoordToFile(activeToolheadType, "ToolbaseGO", drillBitData.ToolbaseGO);
            this->WriteCoordToFile(activeToolheadType, "TooltipGO", drillBitData.TooltipGO);
        }

        if (activeToolheadType == "SABERSAW"){
            auto saberSawData = activeToolhead->GetData<SaberSawData>();
            this->WriteCoordToFile(activeToolheadType, "ToolbaseGO", saberSawData.ToolbaseGO);
            this->WriteCoordToFile(activeToolheadType, "TooltipGO", saberSawData.TooltipGO);
        }

        if (activeToolheadType == "CIRCULARSAW"){
            auto circularSawData = activeToolhead->GetData<CircularSawData>();
            this->WriteCoordToFile(activeToolheadType, "NormStartGO", circularSawData.NormStartGO);
            this->WriteCoordToFile(activeToolheadType, "NormEndGO", circularSawData.NormEndGO);
        }

        if (activeToolheadType == "CHAINSAW"){
            auto chainSawData = activeToolhead->GetData<ChainSawData>();
            this->WriteCoordToFile(activeToolheadType, "ChainBaseGO", chainSawData.ChainBaseGO);
            this->WriteCoordToFile(activeToolheadType, "ChainEndGO", chainSawData.ChainEndGO);
        }
    }

    void LayerUtils::WriteCoordToFile(const std::string& toolheadType, const std::string& pointType, std::shared_ptr<GOPoint> goPoint){
        std::cout << "Writing coordinates to file" << std::endl;
        std::ofstream myfile;
        // append mode
        myfile.open(this->m_SaveToolCoordDefaultPath + "/coordinates.log", std::ios_base::app);
        myfile << toolheadType << "," << pointType << "," << goPoint->X() << "," << goPoint->Y() << "," << goPoint->Z() << "\n";
        myfile.close();
    }

}

