#include "AIAC/Config.h"

#include "AIAC/LayerSlam.h"
#include "AIAC/Log.h"
#include "AIAC/Application.h"

#include <iostream>


namespace AIAC
{
    // TODO: maybe we should define these const somewhere else?
    const std::string TSLAM_CONF_SEC = "TSlam"; 

    void LayerSlam::OnAttach()
    {
        AIAC_INFO(AIAC::Config::Get<string>(TSLAM_CONF_SEC, "MapFile", "assets/tslam/example.map"));

        Slam.setMap(AIAC::Config::Get<string>(TSLAM_CONF_SEC, "MapFile", "assets/tslam/example.map"));
        Slam.setVocabulary(AIAC::Config::Get<string>(TSLAM_CONF_SEC, "VocFile", "assets/tslam/orb.fbow"));
        Slam.setCamParams(AIAC::Config::Get<string>(TSLAM_CONF_SEC, "CamParamsFile", "assets/tslam/calibration_webcam.yml"));
        Slam.setInstancing(true);
    }

    void LayerSlam::OnFrameStart()
    {
        cv::Mat currentFrame;
        AIAC_APP().GetLayer<AIAC::LayerCamera>()->MainCamera.GetCurrentFrame().GetCvMat().copyTo(currentFrame);

        m_IsTracked = Slam.process(currentFrame, m_CamPose);

        AIAC_INFO(m_IsTracked);
        cout << "\n" << m_CamPose << endl;;
    }

    glm::mat4 LayerSlam::GetCamPoseGlm()
    {
        glm::mat4 glmmat;
        if (m_CamPose.cols != 4 ||m_CamPose.rows != 4 ||m_CamPose.type() != CV_32FC1) {
            throw std::invalid_argument("GetCamPose() error.");
        }
        memcpy(glm::value_ptr(glmmat),m_CamPose.data, 16 * sizeof(float));
        glmmat = glm::transpose(glmmat);
        return glmmat;
    }
}