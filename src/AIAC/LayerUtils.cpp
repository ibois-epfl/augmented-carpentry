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
namespace AIAC {

    void LayerUtils::OnFrameEnd() {
        std::cout << "LayerUtils::OnFrameEnd()" << std::endl;


        /*int width = AIAC_APP.GetWindow()->GetDisplayW();
        int height = AIAC_APP.GetWindow()->GetDisplayH();
        std::cout << "Before Frame buffer: width: " << width << " height: " << height << std::endl;
        // create a vector to hold the data
        std::vector<unsigned char> pixels(width * height * 4);  // 4 for RGBA

        // read pixels from the framebuffer
        glReadBuffer(GL_BACK);
        glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

        // write pixels to image using opencv
        cv::Mat image(height, width, CV_8UC4, pixels.data());
        cv::cvtColor(image, image, cv::COLOR_RGBA2BGR);
*//*        cv::imwrite("output.jpg", image);
        std::cout << "Frame saved" << std::endl;*//*
        boost::uuids::uuid myUuid = boost::uuids::random_generator()();
        cv::imwrite("images/" + boost::uuids::to_string(myUuid) + ".jpg", image);
        std::cout << "Frame saved" << std::endl;*/

    }

}

