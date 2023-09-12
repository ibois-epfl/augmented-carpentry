//
// Created by zholmaga on 11.09.23.
//

#include "VideoRecorder.h"
#include "../AIAC/Application.h"


namespace AIAC::Utils {

    VideoRecorder::VideoRecorder()
            : m_IsRecording(false) {}

    VideoRecorder::~VideoRecorder() {
        // Clean up resources
    }

    void VideoRecorder::StartRecording() {
        m_IsRecording = true;
        m_SavedFrames.clear();
    }

    void VideoRecorder::StopRecording() {
        m_IsRecording = false;
        ExportVideo();
    }

    void VideoRecorder::CaptureFrame() {
        if (m_IsRecording) {
            // Create the necessary buffer
            GLuint pbo;
            glGenBuffers(1, &pbo);
            glBindBuffer(GL_PIXEL_PACK_BUFFER, pbo);
            uint32_t m_WindowWidth = AIAC_APP.GetSpecification().WinWidth;
            uint32_t m_WindowHeight = AIAC_APP.GetSpecification().WinHeight;
            glBufferData(GL_PIXEL_PACK_BUFFER, m_WindowWidth * m_WindowHeight * 4, 0, GL_STREAM_READ);

            // Capture the frame
            CaptureFrame(AIAC_APP.GetWindow()->GetGLFWWindow(), m_WindowWidth, m_WindowHeight);

            // Generate unique filename for the frame
            std::string filename = "frame_.png";
            m_SavedFrames.push_back(filename);

            // Cleanup PBO
            glDeleteBuffers(1, &pbo);
        }
    }

    void VideoRecorder::ExportVideo() {
        if (!m_SavedFrames.empty()) {
            // Use ffmpeg to create a video from the saved frames

            // And then deleting the saved frames
        }
    }

    void VideoRecorder::RenderUI() {
        if (ImGui::Button("Start Recording")) {
            StartRecording();
        }
        if (ImGui::Button("Stop Recording")) {
            StopRecording();
        }
    }

} // namespace AIAC::Utils