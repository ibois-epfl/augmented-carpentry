#pragma once

#include "AIAC/Layer.h"
#include "utils/VideoRecorder.h"
#include "utils/HoleToolheadAxisExporter.h"
#include "Config.h"
#include "AIAC/GOSys/GOPrimitive.h"

namespace AIAC {

    class LayerUtils : public AIAC::Layer {
    public:
        LayerUtils();
        virtual void OnFrameEnd() override;
        /**
         * @brief Create a folder if it does not exist
         *
         * @param path Path to the folder
         * @return true if the folder is created
         * @return false if the folder already exists
         */
        static bool CreateFolder(const std::string& path);

    public: ///< video recorder
        /// @brief Start recording the video of a window
        void StartRecording();
        /// @brief Stop recording the video of a window
        void StopRecording();
        /// @brief Set the save folder path for the recorder
        void SetSaveFolderPath(std::string path);
        /// @brief Get the save folder path for the recorder
        std::string GetSaveFolderPath(){return m_UtilsDefaultPath;};
        /// @brief Check if the video is being processed
        bool IsProcessing(){return m_Processing;};

    public: ///< toolhead exporter
        /// @brief Start exporting the hole and toolhead coordinates
        void ExportHoleToolheadAxis();


    private:
        /// Flag to check if the video is being recorded
        bool m_Recording;
        /// Flag to check if the video is being processed
        bool m_Processing;
        /// Default path to save the video
        std::string m_UtilsDefaultPath = AIAC::Config::Get<std::string>(AIAC::Config::SEC_UTILS, AIAC::Config::UTILS_DEFAULT_PATH);;
        /// Video recorder object
        std::unique_ptr<AIAC::Utils::VideoRecorder> m_VideoRecorder;

        /// Hole toolhead exporter object
        std::unique_ptr<AIAC::Utils::HoleToolheadAxisExporter> m_HoleToolheadAxisExporter;
    };
}
