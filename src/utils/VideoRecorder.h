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

        /// @brief Capture frames from the window
        void CaptureFrames();
        /**
         * @brief Save frames to the frame folder
         *
         * @param height Height of the window
         * @param width Width of the window
         * @param pixels Vector to hold the data
         */
        void SaveFrames(int height, int width, std::vector<unsigned char> pixels);
        /// @brief Create video from the frames using ffmpeg
        void MakeVideoFromFrames();
        /// @brief Create folders for captured frames and videos
        void InitializeDirectories();
        /// @brief Delete the /frames folder
        void DeleteFrameFolder();
        /// @brief Updates the paths used for video and frame storage
        void UpdatePaths();

    private:
        /// Base path of utils
        std::string m_BasePath;
        /// Path to recorder folder
        std::string m_RecorderPath;
        /// Path to frames folder
        std::string m_FramesPath;
        /// Path to video folder
        std::string m_VideoPath;
    };
}
