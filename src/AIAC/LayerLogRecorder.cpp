#include "LayerLogRecorder.h"
#include "Application.h"
#include "utils/MatrixUtils.h"
#include "utils/utils.h"
#include "utils/SystemUtils.h"

#include <utility>

void AIAC::LayerLogRecorder::OnAttach() {

}

void AIAC::LayerLogRecorder::OnFrameStart() {
    if (!m_IsRecording) return;

    m_LogFile << "#" << m_FrameCount << " " << GetCurrentTimestamp() << std::endl;
    LogSlamStatus();
    LogTTool();
    LogACIM();
    m_FrameCount++;
}

void AIAC::LayerLogRecorder::StartRecording(std::string logFilePath) {
    if (m_IsRecording) {
        AIAC_WARN("Already recording, stop the current recording first.");
        return;
    }

    std::string acimModelName = GetFileNameFromPath(AIAC_APP.GetLayer<AIAC::LayerModel>()->GetACInfoModelPath(), false);
    std::string currentDateTime = GetCurrentDateTime();
    std::string logFilename = acimModelName + "_" + currentDateTime + ".txt";

    if (logFilePath.empty()) {
        logFilePath = "./temp/log_recorder/";
    } else {
        if (logFilePath.back() != '/') {
            logFilePath += "/";
        }
    }

    // create the directory if not exist
    if (!std::filesystem::exists(logFilePath)) {
        std::filesystem::create_directories(logFilePath);
    }

    logFilePath += logFilename;


    // start recording
    AIAC_INFO("Start recording log to: {}", logFilePath);
    m_IsRecording = true;
    m_LogFilePath = std::move(logFilePath);
    m_LogFile.open(m_LogFilePath, std::ios::out);
    m_FrameCount = 0;

    LogHeader();
    m_LogFile << "[Content]" << std::endl;
}

void AIAC::LayerLogRecorder::StopRecording() {
    if (!m_IsRecording) return;

    m_IsRecording = false;
    m_LogFile << "[End]" << std::endl;
    m_LogFile.close();

    m_TToolPreviousToolheadName.clear();

    AIAC_INFO("Stop recording log to: {}", m_LogFilePath);
}

void AIAC::LayerLogRecorder::LogHeader() {
    // get the latest version of the TTool files on Zenodo
    std::string cmd = "curl -Ls -o /dev/null -w %{url_effective} https://zenodo.org/doi/10.5281/zenodo.7956930";
    std::string ttoolZenodoVersion = ExecuteSystemCommand(cmd.c_str());


    m_LogFile << "[Header]" << std::endl;
    m_LogFile << "Created Time: " << GetCurrentTimestamp() << std::endl;
    m_LogFile << "AC Info Model path: " << AIAC_APP.GetLayer<AIAC::LayerModel>()->GetACInfoModelPath() << std::endl;
    m_LogFile << "Scanned Model path: " << AIAC_APP.GetLayer<AIAC::LayerModel>()->GetScannedModelPath() << std::endl;
    m_LogFile << "TTool Zenodo Version: " << ttoolZenodoVersion << std::endl;

    // m_LogFile << "SLAM format: " << "SLAM <isTracked> [<t.x> <t.y> <t.z> <q.x> <q.y> <q.z> <q.w>]" << std::endl;
    m_LogFile << std::endl;

    m_LogFile << "[Init]" << std::endl;
    InitACIMStatus();
    InitTToolStatus();
    m_LogFile << std::endl;
}

void AIAC::LayerLogRecorder::LogSlamStatus() {
    bool isTracked = AIAC_APP.GetLayer<AIAC::LayerSlam>()->IsTracked();

    if (!isTracked) {
        return;
    }

    // get pose
    cv::Vec4f quaternion;
    cv::Vec3f tvec;
    AIAC_APP.GetLayer<AIAC::LayerSlam>()->GetCamPoseQuaternionAndTvec(quaternion, tvec);

    // pose[x, y, z] = (0, 0, 0) and quaternion[x, y, z, w]
    m_LogFile << "SLAM " << tvec[0] << " " << tvec[1] << " " << tvec[2] << " "
              << quaternion[0] << " " << quaternion[1] << " " << quaternion[2] << " " << quaternion[3] << endl;
}

void AIAC::LayerLogRecorder::LogTTool() {
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
    if (status[0] == 'N' && !toolheadChanged) { // 'N' for "None"
        return;
    }

    LogTToolTransformation(status);
}

void AIAC::LayerLogRecorder::InitTToolStatus() {
    m_TToolPreviousToolheadName = AIAC_APP.GetLayer<AIAC::LayerToolhead>()->ACInfoToolheadManager->GetActiveToolhead()->GetName();
    m_LogFile << "TTool-head " << m_TToolPreviousToolheadName << endl;
    LogTToolTransformation("Init");
}

void AIAC::LayerLogRecorder::LogTToolTransformation(const std::string& status){
    // Get the relative pose to the camera
    auto ttoolPose = AIAC_APP.GetLayer<AIAC::LayerToolhead>()->TTool->GetPose();
    cv::Vec3f tvec;
    cv::Vec4f qvec;
    ConvertTransMatToTvecAndQvec(ttoolPose, tvec, qvec);

    m_LogFile << "TTool-pose " << status << " " << tvec[0] << " " << tvec[1] << " " << tvec[2] << " "
              << qvec[0] << " " << qvec[1] << " " << qvec[2] << " " << qvec[3] << endl;
}



void AIAC::LayerLogRecorder::LogACIM() {
    // if activated component changed
    std::string componentID = AIAC_APP.GetLayer<AIAC::LayerModel>()->GetACInfoModel().GetTimberInfo().GetCurrentComponentID();
    if (m_ACIMPreviousActivatedComponentID.empty() || (!componentID.empty() && componentID != m_ACIMPreviousActivatedComponentID)) {
        m_LogFile << "ACIM-activate-component " << componentID << endl;
        m_ACIMPreviousActivatedComponentID = componentID;

        m_IsActivatedComponentDone = AIAC_APP.GetLayer<AIAC::LayerModel>()->GetACInfoModel().GetTimberInfo().GetComponent(componentID)->IsMarkedDone;
    }

    // if activated is activated done / not done
    bool isActivatedComponentDone = AIAC_APP.GetLayer<AIAC::LayerModel>()->GetACInfoModel().GetTimberInfo().GetCurrentComponent()->IsMarkedDone;
    if (m_IsActivatedComponentDone != isActivatedComponentDone) {
        m_LogFile << "ACIM-component-status " << AIAC_APP.GetLayer<AIAC::LayerModel>()->GetACInfoModel().GetTimberInfo().GetCurrentComponentID() << " "
                  << (isActivatedComponentDone ? "Done" : "NotDone") << endl;
        m_IsActivatedComponentDone = isActivatedComponentDone;
    }

    // if transformation changed
    float offset = AIAC_APP.GetLayer<AIAC::LayerModel>()->GetAlignOffset();
    int rotation = AIAC_APP.GetLayer<AIAC::LayerModel>()->GetAlignRotation();
    bool flip = AIAC_APP.GetLayer<AIAC::LayerModel>()->GetAlignFlip();
    if (m_ACIMOffset != offset || m_ACIMRotation != rotation || m_ACIMFlip != flip) {
        m_ACIMOffset = offset;
        m_ACIMRotation = rotation;
        m_ACIMFlip = flip;

        LogACIMTransformation();
    }

}

void AIAC::LayerLogRecorder::InitACIMStatus() {
    // init variables storing the state
    m_ACIMComponentStatus.clear();

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

    LogACIMTransformation();
}

void AIAC::LayerLogRecorder::LogACIMTransformation() {
    glm::mat4x4 transformMat = AIAC_APP.GetLayer<AIAC::LayerModel>()->GetTransformMat();
    cv::Mat transformMatCv;
    CvtGlmMat2CvMat(transformMat, transformMatCv);
    cv::Vec3f tvec;
    cv::Vec4f qvec;
    ConvertTransMatToTvecAndQvec(transformMatCv, tvec, qvec);
    m_LogFile << "ACIM-transform " << tvec[0] << " " << tvec[1] << " " << tvec[2] << " "
              << qvec[0] << " " << qvec[1] << " " << qvec[2] << " " << qvec[3] << endl;
}

