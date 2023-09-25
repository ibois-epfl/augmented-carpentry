//
// Created by zholmaga on 11.09.23.
//

#include "VideoRecorder.h"
#include "../AIAC/Application.h"
#include <opencv2/opencv.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <filesystem>

namespace AIAC::Utils {

    VideoRecorder::VideoRecorder() {
        // check /image folder if it doesn't exist create it
        std::string imageFolderPath = "./videorecorder";  // Path to the image folder
        if (!std::filesystem::exists(imageFolderPath)) {
            std::filesystem::create_directory(imageFolderPath);
            AIAC_INFO("Created {0} folder", imageFolderPath);
        }
        AIAC_INFO("{0} folder exists!", imageFolderPath);

        // create the /frames folder in image folder if image folder exists
        std::string framesFolderPath = imageFolderPath + "/frames";  // Path to the frames folder
        if (std::filesystem::exists(imageFolderPath) && !std::filesystem::exists(framesFolderPath)) {
            std::filesystem::create_directory(framesFolderPath);
            AIAC_INFO("Created {0} folder", framesFolderPath);
        }
        AIAC_INFO("{0} folder exists!", framesFolderPath);

        // create the /video folder in image folder if image folder exists
        std::string videoFolderPath = imageFolderPath + "/videos";  // Path to the video folder
        if (std::filesystem::exists(imageFolderPath) && !std::filesystem::exists(videoFolderPath)) {
            std::filesystem::create_directory(videoFolderPath);
            AIAC_INFO("Created {0} folder", videoFolderPath);
        }
    }

    VideoRecorder::~VideoRecorder() {
        std::cout << "VideoRecorder destructor" << std::endl;

    }

    void VideoRecorder::CaptureFrames() {
        std::cout << "VideoRecorder::CaptureFrames" << std::endl;
        int width = AIAC_APP.GetWindow()->GetDisplayW();
        int height = AIAC_APP.GetWindow()->GetDisplayH();
        // create a vector to hold the data
        std::vector<unsigned char> pixels(width * height * 4);  // 4 for RGBA

        // read pixels from the framebuffer
        glReadBuffer(GL_BACK);
        glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

        // write pixels to image using opencv
        SaveFrames(height, width, pixels);

    }

    void VideoRecorder::SaveFrames(int height, int width, std::vector<unsigned char> pixels) {
        std::cout << "VideoRecorder::SaveFrames" << std::endl;
        cv::Mat image(height, width, CV_8UC4, pixels.data());
        cv::cvtColor(image, image, cv::COLOR_RGBA2BGR);

        boost::uuids::uuid myUuid = boost::uuids::random_generator()();
        cv::imwrite("images/" + boost::uuids::to_string(myUuid) + ".jpg", image);
    }

    void VideoRecorder::MakeVideoFromFrames() {
        std::cout << "VideoRecorder::MakeVideoFromFrames" << std::endl;
    }

}