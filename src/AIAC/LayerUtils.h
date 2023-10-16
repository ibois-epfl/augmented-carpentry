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
        void OnFrameEnd() override;
        /**
         * @brief Create a folder if it does not exist
         *
         * @param path Path to the folder
         * @return true if the folder is created
         * @return false if the folder already exists
         */
        static bool CreateFolder(const std::string& path);
        /**
         * @brief Set the save folder path for the utils from UI
         *
         * @param path Path to the folder that comes from UI
         */
        void SetSaveFolderPath(const std::string& path);
        /**
         * @brief Get the current save folder path for the utils
         *
         * @return std::string Path to the current utils folder
         */
        std::string GetSaveFolderPath(){return m_UtilsPath;};

    public: ///< video recorder
        /// @brief Start recording the video of a window
        void StartRecording();
        /// @brief Stop recording the video of a window
        void StopRecording();
        /// @brief Check if the video is being processed
        bool IsProcessing(){return m_Processing;};

    public: ///< hole and toolhead exporter
        /// @brief Export and write the hole and toolhead coordinates
        void ExportHoleToolheadAxis();

    public: ///< screenshot
        /// @brief Take a screenshot of the current window
        void TakeWindowScreenshot();
        void CapturePhoto(std::string& savePath);
        void CaptureBuffer(std::string& savePath);
        void TakeBufferScreenshot();

    private:
        /// Default path to utils folder
        std::string m_UtilsPath = AIAC::Config::Get<std::string>(AIAC::Config::SEC_UTILS,
                                                                 AIAC::Config::UTILS_PATH);

    private: ///< video recorder
        /// Flag to check if the video is being recorded
        bool m_Recording;
        /// Flag to check if the video is being processed
        bool m_Processing;
        /// Video recorder object
        std::unique_ptr<AIAC::Utils::VideoRecorder> m_VideoRecorder;

    private: ///< hole and toolhead exporter
        /// Hole and toolhead exporter object
        std::unique_ptr<AIAC::Utils::HoleToolheadAxisExporter> m_HoleToolheadAxisExporter;
    };
}

