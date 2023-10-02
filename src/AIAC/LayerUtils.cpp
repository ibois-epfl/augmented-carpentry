#include "LayerUtils.h"
#include "utils/VideoRecorder.h"
#include "Config.h"
#include <thread>

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
        // create the video from the frames in a separate thread
        std::thread([this]{
            this->m_VideoRecorder->MakeVideoFromFrames();
            // delete the frames folder and video recorder object
            this->m_VideoRecorder.reset();
        }).detach();
        // set the recording flag to false
        this->m_Recording = false;
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
}

