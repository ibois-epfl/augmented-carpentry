// #####################################################################
// >>>>>>>>>>>>>>>>>>>>> BEGINNING OF LEGAL NOTICE >>>>>>>>>>>>>>>>>>>>>
//######################################################################
//
// This source file, along with its associated content, was authored by
// Andrea Settimi, Hong-Bin Yang, Naravich Chutisilp, and numerous other
// contributors. The code was originally developed at the Laboratory for
// Timber Construction (IBOIS, director: Prof. Yves Weinand) at the School of 
// Architecture, Civil and Environmental Engineering (ENAC) at the Swiss
// Federal Institute of Technology in Lausanne (EPFL) for the Doctoral
// Research "Augmented Carpentry" (PhD researcher: Andrea Settimi,
// co-director: Dr. Julien Gamerro, director: Prof. Yves Weinand).
//
// Although the entire repository is distributed under the GPL license,
// these particular source files may also be used under the terms of the
// MIT license. By accessing or using this file, you agree to the following:
//
// 1. You may reproduce, modify, and distribute this file in accordance
//    with the terms of the MIT license.
// 2. You must retain this legal notice in all copies or substantial
//    portions of this file.
// 3. This file is provided "AS IS," without any express or implied
//    warranties, including but not limited to the implied warranties of
//    merchantability and fitness for a particular purpose.
//
// If you cannot or will not comply with the above conditions, you are
// not permitted to use this file. By proceeding, you acknowledge and
// accept all terms and conditions herein.
//
//######################################################################
// <<<<<<<<<<<<<<<<<<<<<<< END OF LEGAL NOTICE <<<<<<<<<<<<<<<<<<<<<<<<
// #####################################################################
//
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
        /// @brief Take a screenshot of the colored buffer
        void TakeBufferScreenshot();
        /**
         * @brief Set the flag to check if the screenshot is of the window
         *
         * @param value True if the screenshot is of the window
         */
        void SetWindowScreenshot(bool value){m_WindowScreenshot = value;};

    private:
        /// Default path to utils folder
        std::string m_UtilsPath = AIAC::Config::Get<std::string>(AIAC::Config::SEC_UTILS,
                                                                 AIAC::Config::UTILS_PATH,
                                                                 "./temp");
    private: ///< video recorder
        /// Flag to check if the video is being recorded
        bool m_Recording = false;
        /// Flag to check if the video is being processed
        bool m_Processing = false;
        /// Video recorder object
        std::unique_ptr<AIAC::Utils::VideoRecorder> m_VideoRecorder;

    private: ///< hole and toolhead exporter
        /// Hole and toolhead exporter object
        std::unique_ptr<AIAC::Utils::HoleToolheadAxisExporter> m_HoleToolheadAxisExporter;

    private: ///< screenshot
        /// Flag to check if the screenshot is of the window
        bool m_WindowScreenshot = false;
    };
}

