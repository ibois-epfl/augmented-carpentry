//
// Created by zholmaga on 11.09.23.
//

#pragma once

#include "AIAC/Layer.h"
#include "utils/VideoRecorder.h"
#include "Config.h"

namespace AIAC {

    class LayerUtils : public AIAC::Layer {
    public:///< Public members
        virtual void OnFrameEnd() override;
        /// @brief Start recording the video of a window
        void StartRecording();
        /// @brief Stop recording the video of a window
        void StopRecording();
        /// @brief Set the save folder path for the recorder
        void SetSaveFolderPath(std::string path);
        /// @brief Get the save folder path for the recorder
        std::string GetSaveFolderPath(){return m_SaveFolderPath;};

    private:///< Private members
        /// Flag to check if the video is being recorded
        bool m_Recording;
        /// Path to save the video
        std::string m_SaveFolderPath = AIAC::Config::Get<std::string>(AIAC::Config::SEC_UTILS, AIAC::Config::RECORDER_DEFAULT_PATH);;
        /// Video recorder object
        std::unique_ptr<AIAC::Utils::VideoRecorder> videoRecorder;
    };

}

