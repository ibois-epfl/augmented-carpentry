#include "LayerRecorder.h"

#include <utility>

void AIAC::LayerRecorder::OnAttach() {

}

void AIAC::LayerRecorder::OnFrameStart() {
    if (!m_IsRecording) return;
}

void AIAC::LayerRecorder::StartRecording(std::string logFilename) {
    m_IsRecording = true;
    m_LogFilename = std::move(logFilename);
}

void AIAC::LayerRecorder::StopRecording() {
    m_IsRecording = false;
}