//
// Created by zholmaga on 11.09.23.
//

#include "LayerUtils.h"
#include <boost/uuid/uuid_io.hpp>
#include "utils/VideoRecorder.h"
namespace AIAC {
    void LayerUtils::OnFrameEnd() {
        if(this->m_Recording){
            this->videoRecorder->CaptureFrames();
        }
    }

    void LayerUtils::StartRecording(){
        std::cout << "LayerUtils::StartRecording" << std::endl;
        this->m_Recording = true;
        this->videoRecorder = std::make_unique<AIAC::Utils::VideoRecorder>();
    };

    void LayerUtils::StopRecording(){
        std::cout << "LayerUtils::StopRecording" << std::endl;
        this->m_Recording = false;
        this->videoRecorder->MakeVideoFromFrames();
        this -> videoRecorder.reset();
    };

}

