#include "aiacpch.h"

#include "AIAC/Config.h"

#include "AIAC/LayerSlam.h"
#include "AIAC/Log.h"
#include "AIAC/Application.h"

//for test
#include "glm/gtx/string_cast.hpp"

namespace AIAC
{
    // TODO: maybe we should define these const somewhere else?
    const std::string TSLAM_CONF_SEC = "TSlam"; 

    void LayerSlam::OnAttach()
    {
        AIAC_INFO(AIAC::Config::Get<string>(TSLAM_CONF_SEC, "MapFile", "assets/tslam/example.map"));
        Slam.setMap(AIAC::Config::Get<string>(TSLAM_CONF_SEC, "MapFile", "assets/tslam/example.map"));
        Slam.setVocabulary(AIAC::Config::Get<string>(TSLAM_CONF_SEC, "VocFile", "assets/tslam/orb.fbow"));
        Slam.setCamParams(AIAC::Config::Get<string>("AIAC", "CamParamsFile", "assets/tslam/calibration_webcam.yml"));
        Slam.setInstancing(true);
    }

    void LayerSlam::OnFrameStart()
    {
        cv::Mat currentFrame;
        AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetCurrentFrame().GetCvMat().copyTo(currentFrame);

        m_IsTracked = Slam.process(currentFrame, m_CamPose);

        if(m_IsTracked) { m_LastTrackedCamPose = m_CamPose; }
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

    glm::mat4 LayerSlam::GetInvCamPoseGlm()
    {
        glm::mat4 glmMat;
        if (m_CamPose.cols != 4 ||m_CamPose.rows != 4 ||m_CamPose.type() != CV_32FC1) {
            throw std::invalid_argument("GetInvCamPose() error.");
        }
        memcpy(glm::value_ptr(glmMat),m_CamPose.data, 16 * sizeof(float));
        glmMat = glm::transpose(glmMat);

        glm::mat3 RT;
        glm::vec3 d;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                RT[i][j] = glmMat[i][j]; // Transpose is inverse(R) because R is rotation matrix
            }
            d[i] = glmMat[3][i];
        }
        d = -RT * d;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                glmMat[i][j] = RT[i][j];
            }
            glmMat[3][i] = d[i];
        }
        glmMat[3][3] = 1.0f;

        return glmMat;
    }
}