

# File Screenshot.cpp

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**utils**](dir_313caf1132e152dd9b58bea13a4052ca.md) **>** [**Screenshot.cpp**](Screenshot_8cpp.md)

[Go to the documentation of this file](Screenshot_8cpp.md)


```C++
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
#include "Screenshot.h"
#include "AIAC/Config.h"
#include "../AIAC/Application.h"
#include "AIAC/LayerCamera.h"
#include "AIAC/LayerUtils.h"

namespace AIAC::Utils{
    Screenshot::Screenshot(const std::string& basePath)
            : m_BasePath(basePath)
    {
        LayerUtils::CreateFolder(this->m_BasePath + this->m_ScreenshotPath);
    }

    void Screenshot::CaptureWindow(){
        int width = AIAC_APP.GetWindow()->GetDisplayW();
        int height = AIAC_APP.GetWindow()->GetDisplayH();

        std::vector<unsigned char> pixels(width * height * 4);

        glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
        cv::Mat image(height, width, CV_8UC4, pixels.data());
        cv::flip(image, image, 0);
        cv::cvtColor(image, image, cv::COLOR_RGBA2BGR);

        this->GenerateImageName(true);
        this->SaveScreenshot(image);
    }

    void Screenshot::CaptureBuffer() {
        cv::Mat currentFrame;
        AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetColorCurrentFrame().GetCvMat().copyTo(currentFrame);

        this->GenerateImageName(false);
        this->SaveScreenshot(currentFrame);
    }

    void Screenshot::GenerateImageName(bool isWindow){
        auto now = std::chrono::system_clock::now();
        auto timestamp = std::chrono::system_clock::to_time_t(now);

        std::stringstream imagename;
        if (isWindow) {
            imagename << "window-";
        } else {
            imagename << "buffer-";
        }
        struct std::tm* tm;
        tm = std::localtime(&timestamp);

        imagename << std::put_time(tm, "%Y-%m-%d-%H-%M-%S") << ".png";

        const std::string imagePath = this->m_BasePath + this->m_ScreenshotPath + "/" + imagename.str();
        this->m_ImageName = imagePath;
    }

    void Screenshot::SaveScreenshot(cv::Mat image){
        if(std::filesystem::exists(this->m_BasePath + this->m_ScreenshotPath)) {
            cv::imwrite(m_ImageName, image);
            AIAC_INFO("The image is saved to : {0}", m_ImageName);
        } else {
            AIAC_ERROR("Error: {0} does not exist!", this->m_BasePath + this->m_ScreenshotPath);
        }
    }
}
```


