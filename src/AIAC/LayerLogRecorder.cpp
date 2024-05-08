#include "LayerLogRecorder.h"
#include "Application.h"
#include "utils/utils.h"

#include <utility>

void AIAC::LayerLogRecorder::OnAttach() {

}

void AIAC::LayerLogRecorder::OnFrameStart() {
    if (!m_IsRecording) return;

    m_LogFile << "#" << m_FrameCount << " " << GetCurrentTimestamp() << std::endl;
    LogSlamStatus();
    m_FrameCount++;
}

void AIAC::LayerLogRecorder::StartRecording(std::string logFilename) {
    m_IsRecording = true;
    m_LogFilename = std::move(logFilename);
    m_LogFile.open(m_LogFilename, std::ios::out);
    m_FrameCount = 0;

    m_LogHeader();
    m_LogFile << "[Content]" << std::endl;
}

void AIAC::LayerLogRecorder::StopRecording() {
    m_IsRecording = false;

    m_LogFile << "[End]" << std::endl;
}

void AIAC::LayerLogRecorder::m_LogHeader() {
    m_LogFile << "[Header]" << std::endl;
    m_LogFile << "Created Time: " << GetCurrentTimestamp() << std::endl;
    m_LogFile << "SLAM format: " << "SLAM <isTracked> [<p.x> <p.y> <p.z> <q.x> <q.y> <q.z> <q.w>]" << std::endl;
    m_LogFile << std::endl;
}

void AIAC::LayerLogRecorder::LogSlamStatus() {
    bool isTracked = AIAC_APP.GetLayer<AIAC::LayerSlam>()->IsTracked();
    m_LogFile << "SLAM ";
    if (!isTracked) {
        m_LogFile << "0" << endl;
        return;
    }
    // tracked
    m_LogFile << "1 ";

    // get pose
    cv::Vec4f quaternion;
    cv::Vec3f tvec;
    AIAC_APP.GetLayer<AIAC::LayerSlam>()->GetCamPoseQuaternionAndTvec(quaternion, tvec);

    // pose[x, y, z] = (0, 0, 0) and quaternion[x, y, z, w]
    m_LogFile << tvec[0] << " " << tvec[1] << " " << tvec[2] << " "
              << quaternion[0] << " " << quaternion[1] << " " << quaternion[2] << " " << quaternion[3] << endl;
}


