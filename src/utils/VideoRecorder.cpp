#include "VideoRecorder.h"
#include "../AIAC/Application.h"
#include <opencv2/opencv.hpp>
#include <filesystem>

namespace AIAC::Utils {
    VideoRecorder::VideoRecorder(const std::string& basePath)
    : m_BasePath(basePath)
    {   this->UpdatePaths();
        this->InitializeDirectories();
    }

    VideoRecorder::~VideoRecorder() {
        // delete folders
        this->DeleteFrameFolder();
    }

    void VideoRecorder::UpdatePaths() {
        // get the timestamp to name the folders
        auto now = std::chrono::system_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

        this->m_RecorderPath = this->m_BasePath + "/recorder";
        this->m_FramesPath = this->m_RecorderPath + "/frames_"+ std::to_string(timestamp);
        this->m_VideoPath = this->m_RecorderPath + "/video_"+ std::to_string(timestamp);
    }

    void VideoRecorder::CaptureFrames() {
        // get the height and width of the window
        int width = AIAC_APP.GetWindow()->GetDisplayW();
        int height = AIAC_APP.GetWindow()->GetDisplayH();
        // create a vector to hold the data
        std::vector<unsigned char> pixels(width * height * 4);  // 4 for RGBA

        // opengl 0,0 -- lower left corner
        glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

        // write pixels to image using opencv
        if(std::filesystem::exists(this->m_FramesPath)) {
            this->SaveFrames(height, width, pixels);
        } else {
            AIAC_ERROR("Error: {0} does not exist!", this->m_FramesPath);
    }
    }

    void VideoRecorder::SaveFrames(int height, int width, std::vector<unsigned char> pixels) {
        // create mat object to hold the data
        cv::Mat image(height, width, CV_8UC4, pixels.data());
        // opencv 0,0 -- upper left corner
        cv::flip(image, image, 0);
        cv::cvtColor(image, image, cv::COLOR_RGBA2BGR);

        // get the timestamp to name the image
        auto now = std::chrono::system_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

        // format the filename
        std::stringstream filename;
        filename << std::setfill('0') << std::setw(13) << timestamp << ".jpg";

        // save the image in the /frames folder
        cv::imwrite(this->m_FramesPath + "/" + filename.str(), image);
    }

    void VideoRecorder::MakeVideoFromFrames() {
        const std::string framesFolder = this->m_FramesPath;

        // sort the names of the folder
        std::vector<std::string> framePaths;
        for (const auto& entry : std::filesystem::directory_iterator(framesFolder)) {
            framePaths.push_back(entry.path().string());
        }
        std::sort(framePaths.begin(), framePaths.end());

        // create a file to hold the names of the images
        const std::string imageListFile = "image_list.txt";
        std::ofstream imageList(imageListFile);
        for (const std::string& framePath : framePaths) {
            imageList << "file '" << framePath << "'\n";
        }
        imageList.close();

        // get the timestamp to name the video
        auto now = std::chrono::system_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

        // format the video filename
        std::stringstream videoname;
        videoname << std::setfill('0') << std::setw(13) << timestamp << ".mp4";

        // run the ffmpeg command to create the video and save it in the /video folder
        const std::string videoPath = this->m_VideoPath + "/" + videoname.str();
        std::string ffmpegCommand = "ffmpeg -y -f concat -safe 0 -i " + imageListFile + " -vf \"fps=30\" -c:v libx264 -pix_fmt yuv420p " + videoPath + " 2>/dev/null";

        // check if the video was created successfully
        int result = std::system(ffmpegCommand.c_str());
        if (result == 0) {
            AIAC_INFO("Video saved to: {0}", videoPath);
        } else {
            AIAC_ERROR("Error creating video.");
        }

        // Clean up temporary files
        std::remove(imageListFile.c_str());
    }

    void VideoRecorder::InitializeDirectories(){
        // create the folders if they don't exist
        for(const auto& path: {this->m_BasePath, this->m_RecorderPath,
                                            this->m_FramesPath, this->m_VideoPath}) {
            this->CreateFolder(path);
        }
    }

    bool VideoRecorder::CreateFolder(const std::string& path) {
        if(std::filesystem::exists(path)) {
            AIAC_INFO("{0} folder already exists!", path);
            return true;
        }
        if(std::filesystem::create_directory(path)) {
            AIAC_INFO("Created {0} folder", path);
            return true;
        } else {
            AIAC_ERROR("Failed to create {0} folder", path);
            return false;
        }
    }

    void VideoRecorder::DeleteFrameFolder(){
        // delete the /frames folder
        if (std::filesystem::exists(this->m_FramesPath)) {
            std::filesystem::remove_all(this->m_FramesPath);
        } else {
        AIAC_ERROR("Could not delete {0} folder", this->m_FramesPath);}
    }
}