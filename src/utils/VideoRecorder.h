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

        /// @brief Create video from the frames
        void MakeVideoFromFrames();
        /// @brief Create folders for captured frames and videos
        void InitializeDirectories();
        /// @brief Delete the frames folder
        void DeleteFrameFolder();
        /// @brief Update the paths
        void UpdatePaths();
        /**
         * @brief Create a folder if it does not exist
         *
         * @param path Path to the folder
         * @return true if the folder is created
         * @return false if the folder already exists
         */
        static bool CreateFolder(const std::string& path);


    private:
        /// Base path to save the video
        std::string m_BasePath;
        /// Path to recorder folder
        std::string m_RecorderPath;
        /// Path to frames folder
        std::string m_FramesPath;
        /// Path to video folder
        std::string m_VideoPath;
    };
}
