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

        void StartRecording();
        void StopRecording();
        void CaptureFrame();
        void ExportVideo();

    private:
        bool m_IsRecording;
        std::vector<std::string> m_SavedFrames;
    };

} // namespace AIAC::Utils
