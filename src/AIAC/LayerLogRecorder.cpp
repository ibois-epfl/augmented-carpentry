#include "LayerLogRecorder.h"
#include "Application.h"
#include "utils/utils.h"

#include <utility>

void AIAC::LayerLogRecorder::OnAttach() {

}

void AIAC::LayerLogRecorder::OnFrameStart() {
    if (!m_IsRecording) return;

    m_LogFile << "#" << m_FrameCount << " " << GetCurrentTimestamp() << std::endl;
    m_LogSlamStatus();
    m_LogTToolStatus();
    m_FrameCount++;
}

void AIAC::LayerLogRecorder::StartRecording(std::string logFilename) {
    if (m_IsRecording) {
        AIAC_WARN("Already recording, stop the current recording first.");
        return;
    }

    AIAC_INFO("Start recording log to: {}", logFilename);
    m_IsRecording = true;
    m_LogFilename = std::move(logFilename);
    m_LogFile.open(m_LogFilename, std::ios::out);
    m_FrameCount = 0;

    m_LogHeader();
    m_LogFile << "[Content]" << std::endl;
}

void AIAC::LayerLogRecorder::StopRecording() {
    if (!m_IsRecording) return;

    m_IsRecording = false;
    m_LogFile << "[End]" << std::endl;
    m_LogFile.close();

    m_PreviousToolheadName.clear();

    AIAC_INFO("Stop recording log to: {}", m_LogFilename);
}

void AIAC::LayerLogRecorder::m_LogHeader() {
    m_LogFile << "[Header]" << std::endl;
    m_LogFile << "Created Time: " << GetCurrentTimestamp() << std::endl;
    m_LogFile << "SLAM format: " << "SLAM <isTracked> [<p.x> <p.y> <p.z> <q.x> <q.y> <q.z> <q.w>]" << std::endl;
    m_LogFile << std::endl;
}

void AIAC::LayerLogRecorder::m_LogSlamStatus() {
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

void AIAC::LayerLogRecorder::m_LogTToolStatus() {
    // toolhead change event
    bool toolheadChanged = false;
    std::string toolheadName = AIAC_APP.GetLayer<AIAC::LayerToolhead>()->ACInfoToolheadManager->GetActiveToolhead()->GetName();
    if (m_PreviousToolheadName.empty() || (!toolheadName.empty() && toolheadName != m_PreviousToolheadName)) {
        toolheadChanged = true;

        m_LogFile << "Toolhead " << toolheadName << endl;
        m_PreviousToolheadName = toolheadName;
    }

    // position

    std::string status;

    auto ttoolState = AIAC_APP.GetLayer<AIAC::LayerToolhead>()->GetTtoolState();
    switch (ttoolState) {
        case ttool::EventType::Tracking:
            status = "Tracking";
            break;
        case ttool::EventType::PoseInput:
            status = "PoseInput";
            break;
        default:
            status = "None";
            break;
    }

    /// The status is not "PoseInput" or "Tracking", meaning that the position is the same, no need to log
    if (m_TToolStatusToLog.find(status) == m_TToolStatusToLog.end() && !toolheadChanged) {
        return;
    }

    /// get pose, which is the relative position to the camera
    auto ttoolPose = AIAC_APP.GetLayer<AIAC::LayerToolhead>()->TTool->GetPose();
    cv::Vec3f tvec;
    cv::Vec4f qvec;
    ConvertTransMatToTvecAndQvec(ttoolPose, tvec, qvec);


///  World coordinate
//    auto toolPoseInWorldGlm = AIAC_APP.GetLayer<AIAC::LayerToolhead>()->GetWorldPose();
//    auto toolPoseInWorld = cv::Mat();
//    CvtGlmMat2CvMat(toolPoseInWorldGlm, toolPoseInWorld);
//
//    cv::Vec3f tvec;
//    cv::Vec4f qvec;
//    ConvertTransMatToTvecAndQvec(toolPoseInWorld, tvec, qvec);

    m_LogFile << "TTool " << status << " " << tvec[0] << " " << tvec[1] << " " << tvec[2] << " "
              << qvec[0] << " " << qvec[1] << " " << qvec[2] << " " << qvec[3] << endl;

}