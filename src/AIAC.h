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

#include "AIAC/GlHeader.h"

#include "AIAC/Config.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "AIAC/Base.h"
#include "AIAC/Log.h"
#include "AIAC/Assert.h"

#include "AIAC/TouchMonitor.h"
#include "AIAC/Window.h"

#include "AIAC/EventSys/Event.h"
#include "AIAC/EventSys/SLAMEvent.h"

#include "AIAC/Image.h"
#include "AIAC/Camera.h"
#include "AIAC/DLoader.h"

#include "AIAC/Layer.h"
#include "AIAC/LayerCamera.h"
#include "AIAC/LayerCameraCalib.h"
#include "AIAC/LayerSlam.h"
#include "AIAC/LayerUI.h"
#include "AIAC/LayerModel.h"
#include "AIAC/LayerToolhead.h"
#include "AIAC/LayerFeedback.h"
#include "AIAC/LayerUtils.h"
#include "AIAC/LayerLogRecorder.h"

#include "AIAC/Render/Renderer.h"
#include "AIAC/GOSys/GO.h"

#include "AIAC/EventSys/Event.h"
#include "AIAC/EventSys/SLAMEvent.h"
#include "AIAC/EventSys/CameraEvent.h"
#include "AIAC/EventSys/ApplicationEvent.h"

/* >> add types of events here << */
#include "AIAC/EventSys/EventBus.h"

#include "AIAC/Application.h"

