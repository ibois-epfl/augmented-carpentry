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
#include "AIAC/LayerRecorder.h"

#include "AIAC/Render/Renderer.h"
#include "AIAC/GOSys/GO.h"

#include "AIAC/EventSys/Event.h"
#include "AIAC/EventSys/SLAMEvent.h"
#include "AIAC/EventSys/CameraEvent.h"
#include "AIAC/EventSys/ApplicationEvent.h"
/* >> add types of events here << */
#include "AIAC/EventSys/EventBus.h"

#include "AIAC/Application.h"

