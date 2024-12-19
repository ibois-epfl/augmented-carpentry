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

namespace AIAC::Utils{
    class Screenshot {
    public:
        explicit Screenshot(const std::string& basePath);
        /// @brief Capture pixels of the current window
        void CaptureWindow();
        /// @brief Capture current buffer (color)
        void CaptureBuffer();
        /**
         * @brief Generate the name of the image
         *
         * @param isWindow Flag to check if the image is a window screenshot if not it is a buffer screenshot
         */
        void GenerateImageName(bool isWindow);
        /**
         * @brief Save the screenshot
         *
         * @param image Image to save
         */
        void SaveScreenshot(cv::Mat image);

    private:
        /// Base path of utils
        std::string m_BasePath;
        /// Save path for screenshots
        std::string m_ScreenshotPath = "/screenshots";
        /// Name of the image
        std::string m_ImageName;
    };
}

