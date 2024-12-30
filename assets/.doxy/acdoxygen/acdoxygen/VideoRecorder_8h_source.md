

# File VideoRecorder.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**utils**](dir_313caf1132e152dd9b58bea13a4052ca.md) **>** [**VideoRecorder.h**](VideoRecorder_8h.md)

[Go to the documentation of this file](VideoRecorder_8h.md)


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

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <utility>
#include <vector>
#include <string>

namespace AIAC::Utils {

    class VideoRecorder {
    public:
        explicit VideoRecorder(const std::string& basePath);
        ~VideoRecorder();

        void CaptureFrames();
        void SaveFrames(int height, int width, std::vector<unsigned char> pixels);
        void MakeVideoFromFrames();
        void InitializeDirectories();
        void DeleteFrameFolder();
        void UpdatePaths();


    private:
        std::string m_BasePath;
        std::string m_RecorderPath;
        std::string m_FramesPath;
        std::string m_VideoPath;
    };
}
```


