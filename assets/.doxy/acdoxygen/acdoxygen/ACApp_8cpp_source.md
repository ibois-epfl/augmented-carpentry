

# File ACApp.cpp

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**ACApp.cpp**](ACApp_8cpp.md)

[Go to the documentation of this file](ACApp_8cpp.md)


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

#include "aiacpch.h"
#include "AIAC.h"

int main(int argc, char* argv[]) {
#ifdef __linux__
    AIAC::Log::Init();

    // by default, take the config.ini in the root folder
    std::string configPath = "config.ini";
    if (argc >= 2){
        configPath = argv[1];
    }
    AIAC::Config config(configPath, true);

    AIAC::ApplicationSpecification appSpec;
    appSpec.Name = "augmented_carpentry";  // かくちょう_だいく
    appSpec.WinWidth = 800;
    appSpec.WinHeight = 480;
    appSpec.IsResizable = false;
    appSpec.VSync = true;
    appSpec.WindowBackColor = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);

    std::unique_ptr<AIAC::Application> acApp_ptr = std::unique_ptr<AIAC::Application>(new AIAC::Application(appSpec));

    acApp_ptr->GetWindow()->Init();

    acApp_ptr->GetGORegistry()->Init();

    acApp_ptr->PushLayer<AIAC::LayerCamera>();
    acApp_ptr->PushLayer<AIAC::LayerCameraCalib>();
    acApp_ptr->PushLayer<AIAC::LayerSlam>();
    acApp_ptr->PushLayer<AIAC::LayerModel>();
    acApp_ptr->PushLayer<AIAC::LayerToolhead>();
    acApp_ptr->PushLayer<AIAC::LayerFeedback>();
#ifndef HEADLESS_TEST
    acApp_ptr->PushLayer<AIAC::LayerUI>();
#endif
    acApp_ptr->PushLayer<AIAC::LayerUtils>();
    acApp_ptr->PushLayer<AIAC::LayerLogRecorder>();

    acApp_ptr->GetRenderer()->Init();

    acApp_ptr->GetEventBus()->Init();
    acApp_ptr->Run();

    return 0;
#else
    return -1;
#endif

}
```


