//
// Created by zholmaga on 11.09.23.
//

#include "LayerUtils.h"
#include "utils/VideoRecorder.h"
#include "Config.h"

namespace AIAC {
    void LayerUtils::OnFrameEnd() {
        // check if the recording flag is set to true
        if(this->m_Recording){
            // capture the frames
            this->videoRecorder->CaptureFrames();
        }
    }

    void LayerUtils::StartRecording(){
        AIAC_INFO("LayerUtils::StartRecording");
        // set the recording flag to true
        this->m_Recording = true;
        // get the save path
        std::string savePath = this->GetSaveFolderPath();
        // create the video recorder object
        this->videoRecorder = std::make_unique<AIAC::Utils::VideoRecorder>(savePath);
    };

    void LayerUtils::StopRecording(){
        AIAC_INFO("LayerUtils::StopRecording");
        // set the recording flag to false
        this->m_Recording = false;
        // create the video from the frames
        this->videoRecorder->MakeVideoFromFrames();
        // delete the frames folder and video recorder object
        this->videoRecorder.reset();
    };

    void LayerUtils::SetSaveFolderPath(std::string path){
        AIAC_INFO("LayerUtils::SetSaveFolderPath");
        std::cout << "LayerUtils::SetSaveFolderPath" << std::endl;
        // Set the save folder path for the video recorder
        if(path.empty()) {
            AIAC_INFO("No path specified, using default path: {}", m_SaveFolderPath);
        } else {
            m_SaveFolderPath = path;
            AIAC_INFO("Using specified path: {}", m_SaveFolderPath);
        }
    };

}

