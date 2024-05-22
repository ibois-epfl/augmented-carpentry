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
    m_LogACIMStatus();
    m_FrameCount++;
}

void AIAC::LayerLogRecorder::StartRecording(std::string logFilename) {
    if (m_IsRecording) {
        AIAC_WARN("Already recording, stop the current recording first.");
        return;
    }

    // init variables storing the state
    m_TToolPreviousToolheadName.clear();
    m_ACIMPreviousActivatedComponentID.clear();
    m_ACIMOffset = INFINITY;
    m_ACIMRotation = INT_MAX;
    m_ACIMComponentStatus.clear();

    // start recording
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

    m_TToolPreviousToolheadName.clear();

    AIAC_INFO("Stop recording log to: {}", m_LogFilename);
}

void AIAC::LayerLogRecorder::m_LogHeader() {
    m_LogFile << "[Header]" << std::endl;
    m_LogFile << "Created Time: " << GetCurrentTimestamp() << std::endl;
    m_LogFile << "SLAM format: " << "SLAM <isTracked> [<t.x> <t.y> <t.z> <q.x> <q.y> <q.z> <q.w>]" << std::endl;
    m_LogFile << std::endl;

    m_LogFile << "[Init]" << std::endl;
    InitACIMStatus();
    m_LogTToolStatus();
    m_LogFile << std::endl;
}

void AIAC::LayerLogRecorder::m_LogSlamStatus() {
    bool isTracked = AIAC_APP.GetLayer<AIAC::LayerSlam>()->IsTracked();

    if (!isTracked) {
//        m_LogFile << "0" << endl;
        return;
    }
    // tracked
    m_LogFile << "SLAM ";
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
    if (m_TToolPreviousToolheadName.empty() || (!toolheadName.empty() && toolheadName != m_TToolPreviousToolheadName)) {
        toolheadChanged = true;

        m_LogFile << "TTool-head " << toolheadName << endl;
        m_TToolPreviousToolheadName = toolheadName;
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

    // The status is not "PoseInput" or "Tracking", meaning that the position is the same, no need to log
    if (m_TToolStatusToLog.find(status) == m_TToolStatusToLog.end() && !toolheadChanged) {
        return;
    }

    // Get the relative pose to the camera
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

    m_LogFile << "TTool-pose " << status << " " << tvec[0] << " " << tvec[1] << " " << tvec[2] << " "
              << qvec[0] << " " << qvec[1] << " " << qvec[2] << " " << qvec[3] << endl;

}



void AIAC::LayerLogRecorder::m_LogACIMStatus() {
    // activated component changed event
    bool componentChanged = false;
    std::string componentID = AIAC_APP.GetLayer<AIAC::LayerModel>()->GetACInfoModel().GetTimberInfo().GetCurrentComponentID();
    if (m_ACIMPreviousActivatedComponentID.empty() || (!componentID.empty() && componentID != m_ACIMPreviousActivatedComponentID)) {
        componentChanged = true;

        m_LogFile << "ACIM-activate-component " << componentID << endl;
        m_ACIMPreviousActivatedComponentID = componentID;
    }
}

void AIAC::LayerLogRecorder::InitACIMStatus() {
    m_ACIMPreviousActivatedComponentID = AIAC_APP.GetLayer<AIAC::LayerModel>()->GetACInfoModel().GetTimberInfo().GetCurrentComponentID();
    m_LogFile << "ACIM-activate-component " << m_ACIMPreviousActivatedComponentID << endl;

    auto allComponentIDs = AIAC_APP.GetLayer<AIAC::LayerModel>()->GetACInfoModel().GetTimberInfo().GetAllComponentsIDs();
    for (const auto &componentID : allComponentIDs) {
        bool isDone = AIAC_APP.GetLayer<AIAC::LayerModel>()->GetACInfoModel().GetTimberInfo().GetComponent(componentID)->IsMarkedDone;
        m_ACIMComponentStatus[componentID] = isDone;
        m_LogFile << "ACIM-component-status " << componentID << " " << (isDone ? "Done" : "NotDone") << endl;
    }

    m_ACIMOffset = AIAC_APP.GetLayer<AIAC::LayerModel>()->GetAlignOffset();
    m_ACIMRotation = AIAC_APP.GetLayer<AIAC::LayerModel>()->GetAlignRotation();
    m_ACIMFlip = AIAC_APP.GetLayer<AIAC::LayerModel>()->GetAlignFlip();

    glm::mat4x4 transformMat = AIAC_APP.GetLayer<AIAC::LayerModel>()->GetTransformMat();
    cv::Mat transformMatCv;
    CvtGlmMat2CvMat(transformMat, transformMatCv);
    cv::Vec3f tvec;
    cv::Vec4f qvec;
    ConvertTransMatToTvecAndQvec(transformMatCv, tvec, qvec);
    m_LogFile << "ACIM-transform " << tvec[0] << " " << tvec[1] << " " << tvec[2] << " "
              << qvec[0] << " " << qvec[1] << " " << qvec[2] << " " << qvec[3] << endl;
}
