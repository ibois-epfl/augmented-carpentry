//
// Created by zholmaga on 11.09.23.
//
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>

namespace AIAC::Utils {

    class VideoRecorder {
    public:///< Public members
        VideoRecorder();
        ~VideoRecorder();

        /// @brief Capture frames from the window
        void CaptureFrames();

        /// @brief Save frames to the frame folder
        /// @param height Height of the window
        /// @param width Width of the window
        /// @param pixels Vector to hold the data
        void SaveFrames(int height, int width, std::vector<unsigned char> pixels);

        /// @brief Create video from the frames
        void MakeVideoFromFrames();
        /// @brief Create folders for captured frames and videos
        void CreateFolders();
        /// @brief Delete the frames folder
        void DeleteFrameFolder();

    private:///< Private members
        /// Path to the image folder
        std::string m_ImageFolderPath = "./videorecorder";
        /// Path to the frames folder
        std::string m_FramesFolderPath = m_ImageFolderPath + "/frames";
        /// Path to the video folder
        std::string m_VideoFolderPath = m_ImageFolderPath + "/videos";
    };


}
