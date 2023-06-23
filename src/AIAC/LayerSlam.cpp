#include "aiacpch.h"

#include "AIAC/Config.h"

#include "AIAC/LayerSlam.h"
#include "AIAC/Log.h"
#include "AIAC/Application.h"

#include "utils/utils.h"

//for test
#include "glm/gtx/string_cast.hpp"

namespace AIAC
{
    void LayerSlam::OnAttach()
    {
        // load camera calibration file (mainly for distortion matrix)
        auto calibFilePath = AIAC::Config::Get<std::string>(AIAC::Config::SEC_AIAC, AIAC::Config::CAM_PARAMS_FILE, "assets/tslam/calibration_webcam.yml");
        Slam.setCamParams(calibFilePath);
        Slam.imageParams.Distorsion.setTo(cv::Scalar::all(0));
        Slam.systemParams.enableLoopClosure = false;
        Slam.systemParams.aruco_minerrratio_valid = 15;
        Slam.systemParams.KPNonMaximaSuppresion=true;
        Slam.systemParams.markersOptWeight=1.0; // maximum importance of markers in the final error. Value in range [0,1]. The rest if assigned to points
        Slam.systemParams.minMarkersForMaxWeight=3;
        Slam.systemParams.detectKeyPoints=false;


        // load map, the camera matrix will be replaced by the one in the map
        auto pathToMapFile = AIAC::Config::Get<std::string>(AIAC::Config::SEC_TSLAM, AIAC::Config::MAP_FILE, "assets/tslam/example.map");
        AIAC_EBUS->EnqueueEvent(std::make_shared<SLAMMapLoadedEvent>(pathToMapFile));

        // load vocabulary
        Slam.setVocabulary(AIAC::Config::Get<std::string>(AIAC::Config::SEC_TSLAM, AIAC::Config::VocFile, "assets/tslam/orb.fbow"));
        Slam.setInstancing(true);
    }

    void LayerSlam::OnFrameStart()
    {
        if(!ToProcess){
            return;
        }

        cv::Mat currentFrame;
        cv::Mat resizedFrame;

        AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetCurrentFrame().GetCvMat().copyTo(currentFrame);
        auto targetSize = Slam.imageParams.CamSize;
        cv::resize(currentFrame, resizedFrame, targetSize);
        currentFrame = resizedFrame;

        if(ToEnhance){
            //Get Intensity image
            cv::Mat Lab_image;
            cvtColor(currentFrame, Lab_image, cv::COLOR_BGR2Lab);
            std::vector<cv::Mat> Lab_planes(3);
            cv::split(Lab_image, Lab_planes);  // now we have the L image in lab_planes[0]

            // apply the CLAHE algorithm to the L channel
            cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
            clahe->setClipLimit(4);
            // clahe->setTilesGridSize(cv::Size(10, 10));
            cv::Mat clahe_L;
            clahe->apply(Lab_planes[0], clahe_L);

            // Merge the color planes back into a Lab image
            clahe_L.copyTo(Lab_planes[0]);
            cv::merge(Lab_planes, Lab_image);

            // convert back to RGB
            cv::cvtColor(Lab_image, currentFrame, cv::COLOR_Lab2BGR);
        }

        m_IsTracked = Slam.process(currentFrame, m_CamPose);
        if(m_IsTracked) {
            auto poseDifference = cv::norm(m_CamPose - m_LastTrackedCamPose);
            if (poseDifference < 1.0) {
                m_LastTrackedCamPose = m_CamPose * 0.2 + m_LastTrackedCamPose * 0.8;
            }
            m_LastTrackedCamPose = m_CamPose;
        }
    }

    glm::mat4 LayerSlam::GetCamPoseGlm()
    {
        glm::mat4 glmMat;
        if (m_LastTrackedCamPose.cols != 4 ||m_LastTrackedCamPose.rows != 4 ||m_LastTrackedCamPose.type() != CV_32FC1) {
            throw std::invalid_argument("GetCamPose() error.");
        }
        memcpy(glm::value_ptr(glmMat), m_LastTrackedCamPose.data, 16 * sizeof(float));
        glmMat = glm::transpose(glmMat);
        return glmMat;
    }

    void LayerSlam::GetCamPoseInObjCoord(cv::Mat &rotMat, cv::Mat &tvec){
        rotMat(cv::Rect(0, 0, 3, 3)) = m_LastTrackedCamPose(cv::Rect(0, 0, 3, 3)).t();
        tvec(cv::Rect(0, 0, 3, 1)) = m_LastTrackedCamPose(cv::Rect(3, 0, 3, 1));
        tvec = -rotMat * tvec;
    }

    glm::mat4 LayerSlam::GetInvCamPoseGlm()
    {
        glm::mat4 glmMat;
        if (m_LastTrackedCamPose.cols != 4 ||m_LastTrackedCamPose.rows != 4 ||m_LastTrackedCamPose.type() != CV_32FC1) {
            throw std::invalid_argument("GetCamPose() error.");
        }
        memcpy(glm::value_ptr(glmMat), m_LastTrackedCamPose.data, 16 * sizeof(float));
        glmMat = glm::transpose(glmMat);

        glm::mat3 RT; // rotation matrix
        glm::vec3 tvec; // transpose vector
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                RT[i][j] = glmMat[j][i]; // Transpose is inverse(R) because R is rotation matrix
            }
            tvec[i] = glmMat[3][i];
        }

        tvec = -RT * tvec;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                glmMat[i][j] = RT[i][j];
            }
            glmMat[3][i] = tvec[i];
        }
        glmMat[3][3] = 1.0f;

        return glmMat;
    }

    void LayerSlam::StartMapping()
    {
        ToProcess = true;
        m_IsMapping = true;
        Slam.clearMap();
        Slam.setInstancing(false);
    }
}