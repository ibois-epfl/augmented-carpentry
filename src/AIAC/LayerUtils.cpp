//
// Created by zholmaga on 11.09.23.
//

#include "LayerUtils.h"
#include "Application.h"
#include <GL/glew.h>
#include "Window.h"
#include <opencv2/opencv.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "Render/Viewport.h"
#include "utils/VideoRecorder.h"
namespace AIAC {

    void LayerUtils::OnFrameEnd() {
        std::cout << "LayerUtils::OnFrameEnd()" << std::endl;
        Utils::VideoRecorder recorder;
        recorder.CaptureFrames();
        recorder.MakeVideoFromFrames();

    }

}

