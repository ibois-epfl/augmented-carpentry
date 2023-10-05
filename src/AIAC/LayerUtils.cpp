#include "LayerUtils.h"
#include "utils/VideoRecorder.h"
#include "Config.h"
#include <thread>
#include "Application.h"
#include "ACInfoModel.h"

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
        this->GetCurrentHole();
    }

    void LayerUtils::GetCurrentToolhead(){
        std::cout << "Getting current toolhead" << std::endl;
        // Get the type of the active toolhead
        std::string activeToolheadType = AC_FF_TOOL->GetTypeString();
        if (activeToolheadType == "DRILLBIT"){
            auto drillBitData = AC_FF_TOOL->GetData<DrillBitData>();
            this->WriteCoordToFile(activeToolheadType, "ToolbaseGO", drillBitData.ToolbaseGO);
            this->WriteCoordToFile(activeToolheadType, "TooltipGO", drillBitData.TooltipGO);
        }
        if (activeToolheadType == "CHAINSAW"){
            auto chainSawData = AC_FF_TOOL->GetData<ChainSawData>();
            this->WriteCoordToFile(activeToolheadType, "ChainBaseGO", chainSawData.ChainBaseGO);
            this->WriteCoordToFile(activeToolheadType, "NormStartGO", chainSawData.NormStartGO);
        }

        if (activeToolheadType == "CIRCULARSAW"){
            auto circularSawData = AC_FF_TOOL->GetData<CircularSawData>();
            this->WriteCoordToFile(activeToolheadType, "CenterGO", circularSawData.CenterGO);
            this->WriteCoordToFile(activeToolheadType, "NormStartGO", circularSawData.NormStartGO);
        }
    }

    void LayerUtils::WriteCoordToFile(const std::string& objType, const std::string& pointType, std::shared_ptr<GOPoint> goPoint){
        std::cout << "Writing coordinates to file" << std::endl;
        std::ofstream myfile;
        // append mode
        myfile.open(this->m_SaveToolCoordDefaultPath + "/coordinates.log", std::ios_base::app);
        myfile << objType << "," << pointType << "," << goPoint->X() << "," << goPoint->Y() << "," << goPoint->Z() << "\n";
        myfile.close();
    }

    void LayerUtils::GetCurrentHole(){
        std::cout << "Getting current hole" << std::endl;
        std::string activeHoleType = AC_FF_COMP->GetTypeString();
        TimberInfo::Component* currentComponent = AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().GetCurrentComponent();
        if (activeHoleType == "HOLE"){
            TimberInfo::Hole* hole = dynamic_cast<TimberInfo::Hole*>(currentComponent);
            if (hole) {
                WriteCoordToFile(activeHoleType, "StartPoint", hole->GetStartPointGO());
                WriteCoordToFile(activeHoleType, "EndPoint", hole->GetEndPointGO());
            }
        }
    }
}

