#pragma once

#include "AIAC/Layer.h"
#include "utils/VideoRecorder.h"
#include "Config.h"

namespace AIAC {

    class LayerUtils : public AIAC::Layer {
    public:
        virtual void OnFrameEnd() override;
        /// @brief Start recording the video of a window
        void StartRecording();
        /// @brief Stop recording the video of a window
        void StopRecording();
        /// @brief Set the save folder path for the recorder
        void SetSaveFolderPath(std::string path);
        /// @brief Get the save folder path for the recorder
        std::string GetSaveFolderPath(){return m_SaveFolderPath;};
        /// @brief Check if the video is being processed
        bool IsProcessing(){return m_Processing;};


    public:
        virtual void OnFrameStart() override;
        /// @brief Get the current drillbit
        void GetCurrentDrillbit();

    private:
        /// Flag to check if the video is being recorded
        bool m_Recording;
        /// Flag to check if the video is being processed
        bool m_Processing;
        /// Default path to save the video
        std::string m_SaveFolderPath = AIAC::Config::Get<std::string>(AIAC::Config::SEC_UTILS, AIAC::Config::RECORDER_DEFAULT_PATH);;
        /// Video recorder object
        std::unique_ptr<AIAC::Utils::VideoRecorder> m_VideoRecorder;
    };
}

