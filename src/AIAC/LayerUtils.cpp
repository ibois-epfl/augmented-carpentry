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
        auto toolheadLayer = AIAC_APP.GetLayer<AIAC::LayerToolhead>();
        // Get the active toolhead
        auto activeToolhead = toolheadLayer->ACInfoToolheadManager->GetActiveToolhead();

        // Get the type of the active toolhead
        std::string activeToolheadType = activeToolhead->GetTypeString();
        if (activeToolheadType == "DRILLBIT"){
            auto toolbaseGO = activeToolhead->GetData<DrillBitData>().ToolbaseGO;
            std::cout << "DrillBit ToolBase: "
                      << "(X: " << toolbaseGO->X()
                      << ", Y: " << toolbaseGO->Y()
                      << ", Z: " << toolbaseGO->Z()
                      << ")" << std::endl;
            auto tooltipGO = activeToolhead->GetData<DrillBitData>().TooltipGO;
            std::cout << "DrillBit Tooltip: "
                      << "(X: " << tooltipGO->X()
                      << ", Y: " << tooltipGO->Y()
                      << ", Z: " << tooltipGO->Z()
                      << ")" << std::endl;

        }

        if (activeToolheadType == "SABERSAW"){
            auto toolbaseGO = activeToolhead->GetData<SaberSawData>().ToolbaseGO;
            std::cout << "SaberSaw ToolBase: "
                      << "(X: " << toolbaseGO->X()
                      << ", Y: " << toolbaseGO->Y()
                      << ", Z: " << toolbaseGO->Z()
                      << ")" << std::endl;
            auto tooltipGO = activeToolhead->GetData<SaberSawData>().TooltipGO;
            std::cout << "SaberSaw Tooltip: "
                      << "(X: " << tooltipGO->X()
                      << ", Y: " << tooltipGO->Y()
                      << ", Z: " << tooltipGO->Z()
                      << ")" << std::endl;
        }

        if (activeToolheadType == "CIRCULARSAW"){
            auto normstartGO = activeToolhead->GetData<CircularSawData>().NormStartGO;
            std::cout << "CircularSaw NormStart: "
                      << "(X: " << normstartGO->X()
                      << ", Y: " << normstartGO->Y()
                      << ", Z: " << normstartGO->Z()
                      << ")" << std::endl;
            auto normendGO = activeToolhead->GetData<CircularSawData>().NormEndGO;
            std::cout << "CircularSaw NormEnd: "
                      << "(X: " << normendGO->X()
                      << ", Y: " << normendGO->Y()
                      << ", Z: " << normendGO->Z()
                      << ")" << std::endl;
        }

        if (activeToolheadType == "CHAINSAW"){
            auto chainbaseGO = activeToolhead->GetData<ChainSawData>().ChainBaseGO;
            std::cout << "ChainSaw ChainBase: "
                      << "(X: " << chainbaseGO->X()
                      << ", Y: " << chainbaseGO->Y()
                      << ", Z: " << chainbaseGO->Z()
                      << ")" << std::endl;
            auto chainendGO = activeToolhead->GetData<ChainSawData>().ChainEndGO;
            std::cout << "ChainSaw ChainEnd: "
                      << "(X: " << chainendGO->X()
                      << ", Y: " << chainendGO->Y()
                      << ", Z: " << chainendGO->Z()
                      << ")" << std::endl;
        }
    }

}

