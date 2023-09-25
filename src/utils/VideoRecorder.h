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
    public:
        VideoRecorder();
        ~VideoRecorder();


        inline void StartRecording(){isRecording = true;};
        inline void StopRecording(){isRecording = false;};
        inline bool IsRecording() const {return isRecording;};

        void CaptureFrames();
        void SaveFrames(int height, int width, std::vector<unsigned char> pixels);
        void MakeVideoFromFrames();

    private:
        std::string imageFolderPath = "./videorecorder";  // Path to the image folder
        std::string framesFolderPath = imageFolderPath + "/frames";  // Path to the frames folder
        std::string videoFolderPath = imageFolderPath + "/videos";  // Path to the video folder
        bool isRecording;
    };


}
