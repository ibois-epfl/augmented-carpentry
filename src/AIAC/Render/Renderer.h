#pragma once

#include <vector>

#include "glm/glm.hpp"

#include "AIAC/GlHeader.h"
#include "AIAC/Layer.h"

#include "AIAC/Render/Viewport.h"

#include "AIAC/Render/GLObject.h"

namespace AIAC
{
    class Renderer
    {
    public:
        // For navigating the global view
        enum class StandardView
        {
            TOP,
            BOTTOM,
            NW,
            NE,
            SW,
            SE
        };

    public:
        Renderer() = default;
        virtual ~Renderer() = default;

        void Init();
        void InitProjMatrix();
        void OnRender();

        GLuint GetGlobalView() const { return m_GlobalView.GetTexture(); };
        void SetGlobalViewSize(float w, float h);
        void SetGlobalViewToActivatedComponent(StandardView standardView);
        void UpdateGlobalViewCameraTranslation(double diffX, double diffY);
        void UpdateGlobalViewCameraRotation(double diffX, double diffY);
        void UpdateGlobalViewCameraScale(double diff);

        // Mapping View
        GLuint GetMappingView() const { return m_MappingView.GetTexture(); };
        void SetMappingViewSize(float w, float h);

        // CamCalib view
        GLuint GetCamCalibView() const { return m_CamCalibView.GetTexture(); };
        void SetCamCalibViewSize(float w, float h);

        // Camera Frame rendering type
        enum class CameraFrameType
        {
            RAW,
            UNDISTORTED,
            SLAM_PROCESSED
        };

    private:
        void RenderMainView();

        void InitGlobalView();
        void InitMappingView() { m_MappingView.Init(600, 442); }
        void InitCamCalibView() { m_CamCalibView.Init(600, 442); }

        void RenderGlobalView();
        void RenderMappingView();
        void RenderCamCalibView();

        void RenderCameraFrame(int w, int h, CameraFrameType frameType=CameraFrameType::UNDISTORTED);


    private:
        std::shared_ptr<GLObject> m_TestGLObject;

        float m_CamW, m_CamH;

        GLuint m_BasicShaderProgram;
        GLuint m_MatrixId;
        GLuint m_VAO;

        glm::mat4 m_ProjMatrix;

        // Global view
        Viewport m_GlobalView;
        glm::vec3 m_GlobalCamLookAtCenter = glm::vec3(0, 0, 0);
        glm::mat4 m_GlobalCamMatrix;
        glm::mat4 m_GlobalProjMatrix;
        float m_GlobalProjOrthoSize = 15.f;

        // Mapping view
        Viewport m_MappingView;

        // Camera calib view
        Viewport m_CamCalibView;

        std::vector<glm::vec3> m_CamVisualizationEdges;

        glm::vec4 m_DefaultEdgeColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        glm::vec4 m_PointCloudMapColor = glm::vec4(0.9, 0.9, 0.9, 0.2);
        glm::vec4 m_DigitalModelBoundingBoxColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        glm::vec4 m_DigitalModelFaceColor = glm::vec4(0.6, 0.35, 0.2, 0.3);
    };
}