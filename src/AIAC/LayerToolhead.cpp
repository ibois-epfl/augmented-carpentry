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
        // for(auto& goObj : m_GOObjects)
        //     GOPrimitive::Remove(goObj);

        // for (auto& point : m_Points)
        //     m_GOObjects.push_back(GOPoint::Add(point, 10.5f));

        TTool = std::make_shared<ttool::TTool>(
            AIAC::Config::Get<std::string>(AIAC::Config::SEC_TTOOL, AIAC::Config::CONFIG_FILE, "Aie Aie aie, y a rien de configurer"),
            AIAC::Config::Get<std::string>(AIAC::Config::SEC_AIAC, AIAC::Config::CAM_PARAMS_FILE, "Oh la la la, tu dois metre un fichier de parametre de camera")
            );
        
        // TODO: ObjectTracker needs modelID2Pose to be set, but it is not done during the initialization of object tracker
        TTool->ManipulateModel('e');
        TTool->ManipulateModel('q');

        this->ACInfoToolheadManager->LoadToolheadModels();
        this->ACInfoToolheadManager->SetActiveToolhead("axes");
        // this->ACInfoToolheadManager->SetActiveToolhead("twist_drill_bit_32_165");
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

        // === BEGIN TEST GO Rendering ===
        glm::mat4x4 toWorld = GetWorldPose();
        this->ACInfoToolheadManager->GetActiveToolhead()->Transform(toWorld);

        // Testing why the translation seems to not be working.
        // for (auto& point : m_Points)
        // {
        //     cv::Matx44f translate = cv::Matx44f(1, 0, 0, 0,
        //                                         0, 1, 0, 0,
        //                                         0, 0, 1, 0.01,
        //                                         0, 0, 0, 1);
        //     glm::mat4x4 translateX = glm::make_mat4x4(translate.val);
        //     point = glm::vec4(point, 1.0f) * translateX;
        // }

        // for(auto& goObj : m_GOObjects)
        //     GOPrimitive::Remove(goObj);

        // for (auto point : m_Points)
        // {
        //     std::stringstream ss;
        //     ss << "\n" << "==============================\n";
        //     ss << "To world: \n" << toWorld[0][0] << ", " << toWorld[0][1] << ", " << toWorld[0][2] << ", " << toWorld[0][3] << "\n"
        //                         << toWorld[1][0] << ", " << toWorld[1][1] << ", " << toWorld[1][2] << ", " << toWorld[1][3] << "\n"
        //                         << toWorld[2][0] << ", " << toWorld[2][1] << ", " << toWorld[2][2] << ", " << toWorld[2][3] << "\n"
        //                         << toWorld[3][0] << ", " << toWorld[3][1] << ", " << toWorld[3][2] << ", " << toWorld[3][3] << "\n";
        //     ss << "Point_before: " << point[0] << ", " << point[1] << ", " << point[2] << "\n";
        //     glm::vec4 point_4d = glm::vec4(point, 1.0f);
        //     ss << "Point_4d: " << point_4d[0] << ", " << point_4d[1] << ", " << point_4d[2] << ", " << point_4d[3] << "\n";
        //     glm::vec4 point_2 =  toWorld * glm::vec4(point, 1.0f);
        //     ss << "Point_after: " << point_2[0] << ", " << point_2[1] << ", " << point_2[2] <<  ", " << point_2[3] << "\n";
        //     ss << "\n" << "==============================\n";
        //     AIAC_INFO(ss.str());
        //     point = glm::vec3(point_2);
        //     m_GOObjects.push_back(GOPoint::Add(point, 10.5f));
        // }
        // === END TEST GO Rendering ===

        // std::stringstream ss;
        // ss << "Pose: " << m_Pose;
        // AIAC_INFO(ss.str());
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

    glm::mat4x4 LayerToolhead::GetWorldPose()
    {
        glm::mat4x4 cameraPose = AIAC_APP.GetLayer<LayerSlam>()->GetInvCamPoseGlm();

        // cv::Matx44f projectionMatrix = TTool->GetProjectionMatrix();
        cv::Matx44f toolheadPose = TTool->GetPose();
        // toolheadPose += cv::Matx44f(0 ,0 ,0 ,0
        //                             ,0 ,0 ,0 ,0
        //                             ,0 ,0 ,0 ,10
        //                             ,0 ,0 ,0 ,0);
        // Multiply toolheadPose translation by 10 to match the scale of the model
        // toolheadPose = toolheadPose * cv::Matx44f(1 ,0 ,0 ,10
        //                                          ,0 ,1 ,0 ,10
        //                                          ,0 ,0 ,1 ,10
        //                                          ,0 ,0 ,0 ,1);
        cv::Matx44f toolheadNormalization = TTool->GetModelManager()->GetObject()->getNormalization();
        glm::vec3 rotationAxis = glm::vec3(1, 0, 0);
        // glm::vec3 globalRotationAxis = ???
        
        glm::mat3x3 rotationMatrix = GetRotationMatrix(rotationAxis, -90.0f * M_PI / 180.0f);
        glm::highp_mat4x4 rotationMatrix4 = glm::highp_mat4x4(rotationMatrix);
        
        glm::mat4x4 toolheadPoseGlm = glm::make_mat4x4(toolheadPose.val) * glm::make_mat4x4(toolheadNormalization.val);


        // std::stringstream ss;
        // ss << "Pose Matrix: " << toolheadPose;
        // AIAC_INFO(ss.str());


        glm::mat4x4 worldPose = cameraPose * glm::transpose(toolheadPoseGlm);
        return worldPose;
    }
}