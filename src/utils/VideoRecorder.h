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

        void CaptureFrames();
        void SaveFrames(int height, int width, std::vector<unsigned char> pixels);
        void MakeVideoFromFrames();

    };


}
