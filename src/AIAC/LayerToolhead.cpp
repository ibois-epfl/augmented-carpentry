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
        TTool = std::make_shared<ttool::TTool>(
            AIAC::Config::Get<std::string>(AIAC::Config::SEC_TTOOL, AIAC::Config::CONFIG_FILE, "Aie Aie aie, y a rien de configurer"),
            AIAC::Config::Get<std::string>(AIAC::Config::SEC_AIAC, AIAC::Config::CAM_PARAMS_FILE, "Oh la la la, tu dois metre un fichier de parametre de camera")
            );
        
        // TODO: ObjectTracker needs modelID2Pose to be set, but it is not done during the initialization of object tracker
        TTool->ManipulateModel('e');
        TTool->ManipulateModel('q');

        this->ACInfoToolheadManager->LoadToolheadModels();
        this->ACInfoToolheadManager->SetActiveToolhead("twist_drill_bit_32_165");
        // this->ACInfoToolheadManager->GetActiveToolhead()->SetVisibility(true);
    }

    void LayerToolhead::OnFrameStart()
    {
        UpdateToolheadState();
        if (m_TtoolState == ttool::EventType::PoseInput)
        {
            OnPoseManipulation();
        }

        if (m_TtoolState == ttool::EventType::Tracking)
        {
            cv::Mat currentFrame;
            AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetCurrentFrame().GetCvMat().copyTo(currentFrame);
            TTool->RunOnAFrame(currentFrame);
            m_Pose = TTool->GetPose();
        }

        glm::mat4x4 toWorld = GetWorldPose();
        this->ACInfoToolheadManager->GetActiveToolhead()->Transform(toWorld);
    }

    /**
     * @brief Reload the camera calibration file
    */
    void LayerToolhead::ReloadCameraFromFile()
    {
        TTool->DestrolView();
        OnAttach();
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

    void LayerToolhead::OnPoseManipulation()
    {
        char key = cv::waitKey(1);
        while (key != 'x')
        {
            cv::Mat currentFrame;
            AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetCurrentFrame().GetCvMat().copyTo(currentFrame);
            TTool->ShowSilhouette(currentFrame, -1);
            TTool->ManipulateModel(key);
            key = cv::waitKey(1);
            AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetNextFrame();
        }
        cv::destroyAllWindows();
        AIAC_INFO("Pose manipulation done");
        m_TtoolState = ttool::EventType::None;
        ToolheadStateUI = -1;

        // load the ACIT models from the dataset
        this->ACInfoToolheadManager->LoadToolheadModels();

    }

    /**
     * @brief Update the toolhead state on every frame
     * This will be called from OnFrameStart()
     * It will check if the toolhead is tracking, and count the number of frames it has been tracking for
     * If it has been tracking for TRACK_FOR frames, it will stop tracking
     * If it has not been tracking for TRACK_EVERY frames, it will start tracking
     * 
     */
    void LayerToolhead::UpdateToolheadState()
    {
        switch (ToolheadStateUI)
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

    /**
     * @brief Get the world pose of the toolhead
     * 
     * @return The transformation matrix that transforms from the toolhead frame to the world frame
    */
    glm::mat4x4 LayerToolhead::GetWorldPose()
    {
        glm::mat4x4 cameraPose = AIAC_APP.GetLayer<LayerSlam>()->GetInvCamPoseGlm();

        cv::Matx44f toolheadPose = TTool->GetPose();
        cv::Matx44f toolheadNormalization = TTool->GetModelManager()->GetObject()->getNormalization();
        
        glm::mat4x4 toolheadPoseGlm = glm::make_mat4x4(toolheadPose.val) * glm::make_mat4x4(toolheadNormalization.val);

        glm::mat4x4 worldPose = cameraPose * glm::transpose(toolheadPoseGlm);
        return worldPose;
    }
}