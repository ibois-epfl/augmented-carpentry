#include "LayerLogRecorder.h"
#include "Application.h"
#include "utils/MatrixUtils.h"
#include "utils/utils.h"
#include "utils/SystemUtils.h"
#include "LayerUtils.h"

#include <utility>

void AIAC::LayerLogRecorder::OnAttach() {

}

void AIAC::LayerLogRecorder::OnFrameStart() {
    if (!m_IsRecording || m_IsPaused) return;

    bool isTracked = AIAC_APP.GetLayer<AIAC::LayerSlam>()->IsTracked();

    m_LogFile << "#" << m_FrameCount << " " << GetCurrentTimestamp() << std::endl;
    if (isTracked) LogSlamStatus();
    LogTToolHead();
    if (isTracked) LogTToolPose();
    LogACIM();
    m_FrameCount++;
}

void AIAC::LayerLogRecorder::StartRecording(std::string logRootFolderPath) {
    if (m_IsRecording) {
        AIAC_WARN("Already recording, stop the current recording first.");
        return;
    }

    // The default log file path will be './temp/log_recorders/<logName>/log.txt'
    // Where <logName> is the <acim_model_name>_<current_date_time>

    std::string acimModelName = GetFileNameFromPath(AIAC_APP.GetLayer<AIAC::LayerModel>()->GetACInfoModelPath(), false);
    std::string currentDateTime = GetCurrentDateTime();
    std::string logName = acimModelName + "_" + currentDateTime;

    if (logRootFolderPath.empty()) {
        logRootFolderPath = AIAC_APP.GetLayer<AIAC::LayerUtils>()->GetSaveFolderPath();
        if (logRootFolderPath.empty()) {
            logRootFolderPath = "./temp/";
        }
        if (logRootFolderPath.back() != '/') {
            logRootFolderPath += "/";
        }
        logRootFolderPath += "log_recorders/";
    }
    if (logRootFolderPath.back() != '/') {
        logRootFolderPath += "/";
    }

    m_LogFolderPath = logRootFolderPath + logName;

    // create the directory if not exist
    if (!std::filesystem::exists(m_LogFolderPath)) {
        std::filesystem::create_directories(m_LogFolderPath);
    }

    // copy the dependency files to the log folder
    std::string acimModelPath = AIAC_APP.GetLayer<AIAC::LayerModel>()->GetACInfoModelPath();
    std::string scannedModelPath = AIAC_APP.GetLayer<AIAC::LayerModel>()->GetScannedModelPath();
    std::string ttoolModelPath = AIAC::Config::Get<std::string>(AIAC::Config::SEC_TTOOL, AIAC::Config::CONFIG_FILE, "");
    CopyFile(acimModelPath, m_LogFolderPath + "/AC_info_model.acim");
    CopyFile(scannedModelPath, m_LogFolderPath + "/scanned_model.ply");

    // start recording
    m_LogFilePath = m_LogFolderPath + "/log.txt";

    AIAC_INFO("Start recording log to: {}", m_LogFilePath);
    m_IsRecording = true;
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
    AIAC_INFO("Stop recording log to: {}", m_LogFilePath);

    // compress to a zip file
    AIAC_INFO("Compressing the log folder...");
    std::string zipPath = m_LogFolderPath + ".zip";
    std::string cmd = "zip -r -j " + zipPath + " " + m_LogFolderPath;
    AIAC_INFO("Run zip Command: {}", cmd);
    ExecuteSystemCommand(cmd.c_str());
    AIAC_INFO("Compressed log folder to: {}", zipPath);

    // remove the original log folder
    AIAC_INFO("Removing the log folder...");
    cmd = "rm -rf " + m_LogFolderPath;
    ExecuteSystemCommand(cmd.c_str());

    AIAC_INFO("Done!");
}

void AIAC::LayerLogRecorder::PauseRecording() {
    m_IsPaused = true;
    m_LogFile << "Pause" << std::endl;
}

void AIAC::LayerLogRecorder::ResumeRecording() {
    m_IsPaused = false;
    InitACIMStatus();
    InitTToolStatus();
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
    m_LogFile << std::endl;

    m_LogFile << "[Legend]" << std::endl;
    m_LogFile << "SLAM <t.x> <t.y> <t.z> <q.x> <q.y> <q.z> <q.w>                    // SLAM Camera Pose"         << std::endl;
    m_LogFile << "TTool-head <toolhead_name>                                        // TTool Head Changed"       << std::endl;
    m_LogFile << "TTool-pose <status> <t.x> <t.y> <t.z> <q.x> <q.y> <q.z> <q.w>     // TTool Pose"               << std::endl;
    m_LogFile << "ACIM-activate-component <component_id>                            // ACIM Activated Component" << std::endl;
    m_LogFile << "ACIM-component-status <component_id> <status>                     // ACIM Component Status"    << std::endl;
    m_LogFile << "ACIM-transform <t.x> <t.y> <t.z> <q.x> <q.y> <q.z> <q.w>          // ACIM Transformation"      << std::endl;
    m_LogFile << "Pause                                                             // Paused by user"           << std::endl;

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

void AIAC::LayerLogRecorder::LogTToolHead() {
    std::string toolheadName = AIAC_APP.GetLayer<AIAC::LayerToolhead>()->ACInfoToolheadManager->GetActiveToolhead()->GetName();
    if (m_TToolPreviousToolheadName.empty() || (!toolheadName.empty() && toolheadName != m_TToolPreviousToolheadName)) {
        m_LogFile << "TTool-head " << toolheadName << endl;
        m_TToolPreviousToolheadName = toolheadName;
    }
}

void AIAC::LayerLogRecorder::LogTToolPose() {
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
    LogTToolPose();
}

void AIAC::LayerLogRecorder::LogTToolTransformation(const std::string& status){
    // Get the relative pose to the camera
    cv::Mat ttoolPose(4, 4, CV_32F);
    cv::Vec3f tvec;
    cv::Vec4f qvec;
    auto ttoolPoseGlm = AIAC_APP.GetLayer<AIAC::LayerToolhead>()->GetWorldPose();
    CvtGlmMat2CvMat(ttoolPoseGlm, ttoolPose);
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

