#include "VideoRecorder.h"
#include "../AIAC/Application.h"
#include <opencv2/opencv.hpp>
#include <filesystem>
#include "AIAC/LayerUtils.h"

namespace AIAC::Utils {
    VideoRecorder::VideoRecorder(const std::string& basePath)
    : m_BasePath(basePath)
    {   this->UpdatePaths();
        this->InitializeDirectories();
    }

    VideoRecorder::~VideoRecorder() {
        this->DeleteFrameFolder();
    }

    void VideoRecorder::UpdatePaths() {
        auto now = std::chrono::system_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

        this->m_RecorderPath = this->m_BasePath + "/recorder";
        this->m_FramesPath = this->m_RecorderPath + "/frames_"+ std::to_string(timestamp);
        this->m_VideoPath = this->m_RecorderPath + "/video_"+ std::to_string(timestamp);
    }

    void VideoRecorder::CaptureFrames() {
        int width = AIAC_APP.GetWindow()->GetDisplayW();
        int height = AIAC_APP.GetWindow()->GetDisplayH();
        std::vector<unsigned char> pixels(width * height * 4);  // 4 for RGBA

        glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

        if(std::filesystem::exists(this->m_FramesPath)) {
            this->SaveFrames(height, width, pixels);
        } else {
            AIAC_ERROR("Error: {0} does not exist!", this->m_FramesPath);
    }
    }

    void VideoRecorder::SaveFrames(int height, int width, std::vector<unsigned char> pixels) {
        cv::Mat image(height, width, CV_8UC4, pixels.data());

        cv::flip(image, image, 0);
        cv::cvtColor(image, image, cv::COLOR_RGBA2BGR);

        auto now = std::chrono::system_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

        std::stringstream filename;
        filename << std::setfill('0') << std::setw(13) << timestamp << ".jpg";

        cv::imwrite(this->m_FramesPath + "/" + filename.str(), image);
    }

    void VideoRecorder::MakeVideoFromFrames() {
        const std::string framesFolder = this->m_FramesPath;

        std::vector<std::string> framePaths;
        for (const auto& entry : std::filesystem::directory_iterator(framesFolder)) {
            framePaths.push_back(entry.path().string());
        }
        std::sort(framePaths.begin(), framePaths.end());

        const std::string imageListFile = "image_list.txt";
        std::ofstream imageList(imageListFile);
        for (const std::string& framePath : framePaths) {
            imageList << "file '" << framePath << "'\n";
        }
        imageList.close();

        auto now = std::chrono::system_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

        std::stringstream videoname;
        videoname << std::setfill('0') << std::setw(13) << timestamp << ".mp4";

        const std::string videoPath = this->m_VideoPath + "/" + videoname.str();
        std::string ffmpegCommand = "ffmpeg -y -f concat -safe 0 -i " + imageListFile + " -vf \"fps=30\" -c:v libx264 -pix_fmt yuv420p " + videoPath + " 2>/dev/null";

        int result = std::system(ffmpegCommand.c_str());
        if (result) {
            AIAC_INFO("Video saved to: {0}", videoPath);
        } else {
            AIAC_ERROR("Error: ffmpeg could not create video!");
        }

        std::remove(imageListFile.c_str());
    }

    void VideoRecorder::InitializeDirectories(){
        for(const auto& path: {this->m_RecorderPath,this->m_FramesPath, this->m_VideoPath}) {
            LayerUtils::CreateFolder(path);
        }
    }

    void VideoRecorder::DeleteFrameFolder(){
        if (std::filesystem::exists(this->m_FramesPath)) {
            std::filesystem::remove_all(this->m_FramesPath);
        } else {
        AIAC_ERROR("Could not delete {0} folder", this->m_FramesPath);}
    }
}