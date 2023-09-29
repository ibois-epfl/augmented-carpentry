//
// Created by zholmaga on 11.09.23.
//

#include "LayerUtils.h"
#include "utils/VideoRecorder.h"

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
        // create the video recorder object
        this->videoRecorder = std::make_unique<AIAC::Utils::VideoRecorder>();
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

}

