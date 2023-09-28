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
        if (!std::filesystem::exists(imageFolderPath)) {
            std::filesystem::create_directory(imageFolderPath);
            AIAC_INFO("Created {0} folder", imageFolderPath);
        }
        AIAC_INFO("{0} folder exists!", imageFolderPath);

        // create the /frames folder in image folder if image folder exists
        if (std::filesystem::exists(imageFolderPath) && !std::filesystem::exists(framesFolderPath)) {
            std::filesystem::create_directory(framesFolderPath);
            AIAC_INFO("Created {0} folder", framesFolderPath);
        }
        AIAC_INFO("{0} folder exists!", framesFolderPath);

        // create the /video folder in image folder if image folder exists
        if (std::filesystem::exists(imageFolderPath) && !std::filesystem::exists(videoFolderPath)) {
            std::filesystem::create_directory(videoFolderPath);
            AIAC_INFO("Created {0} folder", videoFolderPath);
        }
    }

    VideoRecorder::~VideoRecorder() {
        std::cout << "VideoRecorder destructor" << std::endl;
        if (std::filesystem::exists(framesFolderPath)) {
            std::filesystem::remove_all(framesFolderPath);
            std::cout << "Deleted /image/frames folder and its contents" << std::endl;
        }

    }

    void VideoRecorder::CaptureFrames() {
        std::cout << "VideoRecorder::CaptureFrames" << std::endl;
        int width = AIAC_APP.GetWindow()->GetDisplayW();
        int height = AIAC_APP.GetWindow()->GetDisplayH();
        // create a vector to hold the data
        std::vector<unsigned char> pixels(width * height * 4);  // 4 for RGBA

        glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

        // write pixels to image using opencv
        SaveFrames(height, width, pixels);

    }

    void VideoRecorder::SaveFrames(int height, int width, std::vector<unsigned char> pixels) {
        std::cout << "VideoRecorder::SaveFrames" << std::endl;
        cv::Mat image(height, width, CV_8UC4, pixels.data());
        // flip to match the opengl coordinate system
        cv::flip(image, image, 0);
        cv::cvtColor(image, image, cv::COLOR_RGBA2BGR);

        auto now = std::chrono::system_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

        std::stringstream filename;
        filename << std::setfill('0') << std::setw(13) << timestamp << ".jpg";
        cv::imwrite(framesFolderPath + "/" + filename.str(), image);
    }

    void VideoRecorder::MakeVideoFromFrames() {
        std::cout << "VideoRecorder::MakeVideoFromFrames" << std::endl;
        // count how many frames are in the /frames folder
        int frameCount = 0;
        const std::string framesFolder = framesFolderPath;
        for (const auto& entry : std::filesystem::directory_iterator(framesFolder)) {
            frameCount++;
        }

        if (frameCount == 0) {
            std::cout << "No frames found in the /frames folder." << std::endl;
            return;
        }

        // sort the names of the folder
        std::vector<std::string> framePaths;
        for (const auto& entry : std::filesystem::directory_iterator(framesFolder)) {
            framePaths.push_back(entry.path().string());
        }

        std::sort(framePaths.begin(), framePaths.end());
        std::cout << "SORTED:" << framePaths << std::endl;
        // create a video from the frames
        const std::string imageListFile = "image_list.txt";
        std::ofstream imageList(imageListFile);
        for (const std::string& framePath : framePaths) {
            imageList << "file '" << framePath << "'\n";
        }
        imageList.close();

        //video name
        auto now = std::chrono::system_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

        std::stringstream videoname;
        videoname << std::setfill('0') << std::setw(13) << timestamp << ".mp4";
        // save the video in the /video folder
        const std::string videoPath = videoFolderPath + "/" + videoname.str();
        std::string ffmpegCommand = "ffmpeg -y -f concat -safe 0 -i " + imageListFile + " -vf \"fps=30\" -c:v libx264 -pix_fmt yuv420p " + videoPath;

        std::cout << "ffmpegCommand: " << ffmpegCommand << std::endl;
        int result = std::system(ffmpegCommand.c_str());

        if (result == 0) {
            std::cout << "Video saved to: " << videoPath << std::endl;
        } else {
            std::cerr << "Error creating video." << std::endl;
        }

        // Clean up temporary files
        std::remove(imageListFile.c_str());

    }

}