//
// Created by zholmaga on 11.09.23.
//

#pragma once

#include "AIAC/Layer.h"
#include "utils/VideoRecorder.h"

namespace AIAC {

    class LayerUtils : public AIAC::Layer {
    public:///< Public members
        virtual void OnFrameEnd() override;
        /// @brief Start recording the video of a window
        void StartRecording();
        /// @brief Stop recording the video of a window
        void StopRecording();

    private:///< Private members
        /// Flag to check if the video is being recorded
        bool m_Recording;
        /// Video recorder object
        std::unique_ptr<AIAC::Utils::VideoRecorder> videoRecorder;
    };

}

