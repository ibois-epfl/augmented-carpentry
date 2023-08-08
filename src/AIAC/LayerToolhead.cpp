#include "aiacpch.h"

#include "AIAC/Config.h"

#include "AIAC/Log.h"
#include "AIAC/Application.h"
#include "AIAC/LayerToolhead.h"
#include "GeometryUtils.h"

namespace AIAC
{
    void LayerToolhead::OnAttach()
    {
        // init ttool
        TTool = std::make_shared<ttool::TTool>(
            AIAC::Config::Get<std::string>(AIAC::Config::SEC_TTOOL, AIAC::Config::TTOOL_ROOT_PATH, "Missing TTool root path"),
            AIAC::Config::Get<std::string>(AIAC::Config::SEC_TTOOL, AIAC::Config::CONFIG_FILE, "Missing config file path"),
            AIAC::Config::Get<std::string>(AIAC::Config::SEC_AIAC, AIAC::Config::CAM_PARAMS_FILE, "Missign camera calib file path")
            );

        // load the datasets acits
        this->ACInfoToolheadManager->LoadToolheadModels();
        if (this->IsShowToolheadGOInfo)
            this->ACInfoToolheadManager->GetActiveToolhead()->SetVisibility(true);

        syncTToolAndACInfoToolhead();
    }

    void LayerToolhead::OnFrameStart()
    {
        UpdateToolheadStateUI();

        cv::Mat currentFrame;
        AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetCurrentFrame().GetCvMat().copyTo(currentFrame);
        
        cv::Mat currentFramePure;
        AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetCurrentFrame().GetCvMat().copyTo(currentFramePure);

        if (m_TtoolState == ttool::EventType::PoseInput)
        {
            // (?) if it is not called x2 it does not work on setting pose (?)
            if (IsShowSilouhette)
            {
                TTool->DrawSilhouette(currentFrame, glm::vec3(255.0f, 153.0f, 255.0f));
                TTool->DrawSilhouette(currentFrame, glm::vec3(255.0f, 153.0f, 255.0f));
            }
            if (IsShowShaded)
            {
                TTool->DrawShaded(currentFrame);
            }
        }

        if (m_TtoolState == ttool::EventType::Tracking)
        {
            TTool->RunOnAFrame(currentFrame);
            if (IsShowSilouhette)
            {
                TTool->DrawSilhouette(currentFrame);
            }
            if (IsShowShaded)
            {
                TTool->DrawShaded(currentFrame);
            }
            m_Pose = TTool->GetPose();
        }

        glm::mat4x4 toWorld = GetWorldPose();
        this->ACInfoToolheadManager->GetActiveToolhead()->Transform(toWorld);

        if (m_TtoolState == ttool::EventType::None)
        {
            if (IsShowSilouhette)
            {
                TTool->DrawSilhouette(currentFrame, glm::vec3(0.0f, 128.0f, 255.0f));
            }
            if (IsShowShaded)
            {
                TTool->DrawShaded(currentFrame);
            }
        }

        if (IsSavePoseLog) { TTool->WritePoseToFile(currentFramePure); }
        else { TTool->ResetPoseWriter(); }

        AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetCurrentFrame().ReplaceCvMat(currentFrame);
    }

    void LayerToolhead::DetectToolhead()
    {
        cv::Mat currentFrame;
        AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetCurrentFrame().GetPureCvMat().copyTo(currentFrame);

        std::string toolhead = TTool->Classify(currentFrame);

        this->ACInfoToolheadManager->SetActiveToolhead(toolhead);
        this->ACInfoToolheadManager->GetActiveToolhead()->SetVisibility(this->IsShowToolheadGOInfo);

        int id = this->ACInfoToolheadManager->GetActiveToolhead()->GetId();
        this->TTool->SetObjectID(id);
    }

    void LayerToolhead::ReloadCameraFromFile()
    {
        TTool->DestrolView();
        TTool = std::make_shared<ttool::TTool>(
            AIAC::Config::Get<std::string>(AIAC::Config::SEC_TTOOL, AIAC::Config::TTOOL_ROOT_PATH, "Missing TTool root path"),
            AIAC::Config::Get<std::string>(AIAC::Config::SEC_TTOOL, AIAC::Config::CONFIG_FILE, "Missing config file path"),
            AIAC::Config::Get<std::string>(AIAC::Config::SEC_AIAC, AIAC::Config::CAM_PARAMS_FILE, "Missign camera calib file path")
            );
        syncTToolAndACInfoToolhead();
    }

    void LayerToolhead::ReloadCameraFromMatrix(cv::Mat cameraMatrix, cv::Size cameraSize)
    {
        TTool->DestrolView();
        TTool = std::make_shared<ttool::TTool>(
            AIAC::Config::Get<std::string>(AIAC::Config::SEC_TTOOL, AIAC::Config::TTOOL_ROOT_PATH, "Missing TTool root path"),
            AIAC::Config::Get<std::string>(AIAC::Config::SEC_TTOOL, AIAC::Config::CONFIG_FILE, "Missing config file path"),
            cameraMatrix,
            cameraSize
            );
        syncTToolAndACInfoToolhead();
    }

    /**
     * @brief Get the world pose of the toolhead
     * 
     * @return The transformation matrix that transforms from the toolhead frame to the world frame
    */
    glm::mat4x4 LayerToolhead::GetWorldPose()
    {
        glm::mat4x4 cameraPose = AIAC_APP.GetLayer<LayerSlam>()->GetInvCamPoseGlm();

        cv::Matx44f toolheadPose = TTool->GetPose();
        toolheadPose(0, 3) *= this->m_ACScaleFactor;
        toolheadPose(1, 3) *= this->m_ACScaleFactor;
        toolheadPose(2, 3) *= this->m_ACScaleFactor;

        cv::Matx44f toolheadNormalization = TTool->GetModelManager()->GetObject()->getNormalization();
        toolheadNormalization(0, 3) *= this->m_ACScaleFactor;
        toolheadNormalization(1, 3) *= this->m_ACScaleFactor;
        toolheadNormalization(2, 3) *= this->m_ACScaleFactor;

        glm::mat4x4 toolheadPoseGlm = glm::make_mat4x4((toolheadPose * toolheadNormalization).val);

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

    void LayerToolhead::SetCurrentObject(std::string name)
    {
        this->ACInfoToolheadManager->SetActiveToolhead(name);
        this->ACInfoToolheadManager->GetActiveToolhead()->SetVisibility(this->IsShowToolheadGOInfo);

        int id = this->ACInfoToolheadManager->GetActiveToolhead()->GetId();

        cv::Mat currentFrame;
        AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetCurrentFrame().GetCvMat().copyTo(currentFrame);
        TTool->DrawSilhouette(currentFrame);
        TTool->DrawSilhouette(currentFrame);

        this->TTool->SetObjectID(id);
    }

    void LayerToolhead::SavePose()
    {
        this->TTool->ManipulateModel('y');

        m_TtoolState = ttool::EventType::None;
        this->ToolheadStateUI = -1;

    }

    void LayerToolhead::ResetPoseFromConfig()
    {
        this->TTool->GetModelManager()->ResetObjectToInitialPose();
    }

    void LayerToolhead::syncTToolAndACInfoToolhead()
    {
        int id = this->ACInfoToolheadManager->GetActiveToolhead()->GetId();
        this->TTool->SetObjectID(id);
    }
}