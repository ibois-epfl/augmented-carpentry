#include "aiacpch.h"

#include "AIAC/Config.h"

#include "AIAC/Log.h"
#include "AIAC/Application.h"
#include "AIAC/LayerToolhead.h"

namespace AIAC
{
    void LayerToolhead::OnAttach()
    {
        // init ttool
        TTool = std::make_shared<ttool::TTool>(
            AIAC::Config::Get<std::string>(AIAC::Config::SEC_TTOOL, AIAC::Config::CONFIG_FILE, "Missing config file path"),
            AIAC::Config::Get<std::string>(AIAC::Config::SEC_AIAC, AIAC::Config::CAM_PARAMS_FILE, "Missign camera calib file path")
            );
        
        // load the datasets acits
        this->ACInfoToolheadManager->LoadToolheadModels();
    }

    void LayerToolhead::OnFrameStart()
    {
        UpdateToolheadStateUI();

        cv::Mat currentFrame;
        AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetCurrentFrame().GetCvMat().copyTo(currentFrame);

        if (m_TtoolState == ttool::EventType::PoseInput)
        {
            // FIXME: (?) if it is not called x2 it does not work on setting pose (?)
            if (IsShowSilouhette)
            {
                TTool->DrawSilhouette(currentFrame, glm::vec3(255.0f, 153.0f, 255.0f));
                TTool->DrawSilhouette(currentFrame, glm::vec3(255.0f, 153.0f, 255.0f));
            }
        }

        if (m_TtoolState == ttool::EventType::Tracking)
        {
            TTool->RunOnAFrame(currentFrame);
            if (IsShowSilouhette)
            {
                TTool->DrawSilhouette(currentFrame);
            }
            m_Pose = TTool->GetPose();
        }

        if (m_TtoolState == ttool::EventType::None)
        {
            if (IsShowSilouhette)
            {
                TTool->DrawSilhouette(currentFrame, glm::vec3(0.0f, 128.0f, 255.0f));
            }
        }

        AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetCurrentFrame().ReplaceCvMat(currentFrame);
    }

    void LayerToolhead::ReloadCameraFromFile()
    {
        TTool->DestrolView();
        TTool = std::make_shared<ttool::TTool>(
            AIAC::Config::Get<std::string>(AIAC::Config::SEC_TTOOL, AIAC::Config::CONFIG_FILE, "Missing config file path"),
            AIAC::Config::Get<std::string>(AIAC::Config::SEC_AIAC, AIAC::Config::CAM_PARAMS_FILE, "Missign camera calib file path")
            );
    }

    void LayerToolhead::ReloadCameraFromMatrix(cv::Mat cameraMatrix, cv::Size cameraSize)
    {
        TTool->DestrolView();
        TTool = std::make_shared<ttool::TTool>(
            AIAC::Config::Get<std::string>(AIAC::Config::SEC_TTOOL, AIAC::Config::CONFIG_FILE, "Aie Aie aie, y a rien de configurer"),
            cameraMatrix,
            cameraSize
            );
    }

    glm::mat4x4 LayerToolhead::GetWorldPose()
    {
        glm::mat4x4 cameraPose = AIAC_APP.GetLayer<LayerSlam>()->GetInvCamPoseGlm();

        cv::Matx44f projectionMatrix = TTool->GetProjectionMatrix();
        cv::Matx44f toolheadPose = TTool->GetPose();
        cv::Matx44f toolheadNormalization = TTool->GetModelManager()->GetObject()->getNormalization();
        glm::mat4x4 toolheadPoseGlm = glm::make_mat4x4((projectionMatrix * toolheadNormalization * toolheadPose).val);

        std::stringstream ss;
        ss << "Pose Matrix: " << toolheadNormalization * toolheadPose;
        AIAC_INFO(ss.str());

        glm::mat4x4 worldPose = cameraPose * glm::transpose(toolheadPoseGlm);
        return worldPose;
    }

    void LayerToolhead::UpdateToolheadStateUI()
    {
        switch (this->ToolheadStateUI)
        {
        case 0:
            m_TtoolState = ttool::EventType::Tracking;
            break;
        case 1:
            m_TtoolState = ttool::EventType::PoseInput;
            break;
        default:
            m_TtoolState = ttool::EventType::None;
            break;
        }
        return;
    }

    //FIXME: @hong-bin render: solve flickering when changing
    void LayerToolhead::SetCurrentObject(std::string name)
    {
        this->ACInfoToolheadManager->SetActiveToolhead(name);

        int id = this->ACInfoToolheadManager->GetActiveToolhead()->GetId();

        cv::Mat currentFrame;
        AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetCurrentFrame().GetCvMat().copyTo(currentFrame);
        TTool->DrawSilhouette(currentFrame);
        TTool->DrawSilhouette(currentFrame);

        this->TTool->SetObjectID(id);
    }
}