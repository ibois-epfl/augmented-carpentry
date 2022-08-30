#pragma once

#include <vector>

#include "glm/glm.hpp"

#include "AIAC/Mesh.h"
#include "AIAC/GlHeader.h"
#include "AIAC/Layer.h"


namespace AIAC
{
    class Renderer
    {
    public:
        Renderer() = default;
        virtual ~Renderer() = default;

        void Init();
        void OnRender();

        void ReloadMeshes();

        GLuint GetGlobalView() const { return m_GlobalViewTexture; };
        void SetGlobalViewSize(float w, float h);
        void UpdateGlobalViewCameraTranslation(double diffX, double diffY);
        void UpdateGlobalViewCameraRotation(double diffX, double diffY);
        void UpdateGlobalViewCameraScale(double diff);

        GLuint GetMappingView() const { return m_MappingViewTexture; };
        void SetMappingViewSize(float w, float h);

        void StartMapping() { Meshes.clear(); ShowDigitalModel = false; ShowPointCloudMap = false; }
        void StopMapping() { ReloadMeshes(); ShowDigitalModel = true; ShowPointCloudMap = true; }

    public:
        AIAC::Mesh PointCloudMap;
        AIAC::Mesh DigitalModel;
        std::vector<AIAC::Mesh> Meshes;

        bool ShowPointCloudMap = true;
        bool ShowDigitalModel = true;

    private:
        void InitGlobalView();
        void InitMappingView();
        void RenderGlobalView();
        void RenderMappingView();

        void RenderCameraFrame();

    private:
        float m_CamW, m_CamH;

        GLuint m_VAO;
        GLuint m_BasicShaderProgram;
        GLuint m_MatrixId;

        glm::mat4 m_ProjMatrix;

        // Global view
        GLuint m_GlobalViewFrameBuffer;
        GLuint m_GlobalViewTexture;
        glm::mat4 m_GlobalCamMatrix;
        glm::mat4 m_GlobalProjMatrix;
        float m_GlobalViewWidth=400, m_GlobalViewHeight=300;

        // Mapping view
        GLuint m_MappingViewFrameBuffer;
        GLuint m_MappingViewTexture;
        float m_MappingViewWidth=640, m_MappingViewHeight=480;

        std::vector<glm::vec3> m_CamVisualizationEdges;

        glm::vec4 m_DefaultEdgeColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        glm::vec4 m_PointCloudMapColor = glm::vec4(0.9, 0.9, 0.9, 0.2);
        glm::vec4 m_DigitalModelBoundingBoxColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        glm::vec4 m_DigitalModelFaceColor = glm::vec4(0.6, 0.35, 0.2, 0.3);
    };
}