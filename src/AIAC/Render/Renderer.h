#pragma once

#include <vector>

#include "glm/glm.hpp"

#include "AIAC/Mesh.h"
#include "AIAC/GlHeader.h"
#include "AIAC/Layer.h"

#include "AIAC/Render/Viewport.h"

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

        GLuint GetGlobalView() const { return m_GlobalView.GetTexture(); };
        void SetGlobalViewSize(float w, float h);
        void UpdateGlobalViewCameraTranslation(double diffX, double diffY);
        void UpdateGlobalViewCameraRotation(double diffX, double diffY);
        void UpdateGlobalViewCameraScale(double diff);

        GLuint GetMappingView() const { return m_MappingView.GetTexture(); };
        void SetMappingViewSize(float w, float h);

        void StartCamCalib() { Meshes.clear(); ShowDigitalModel = false; ShowPointCloudMap = false; }
        void StopCamCalib() { ReloadMeshes(); ShowDigitalModel = true; ShowPointCloudMap = true; }

        void StartMapping() { Meshes.clear(); ShowDigitalModel = false; ShowPointCloudMap = false; }
        void StopMapping() { ReloadMeshes(); ShowDigitalModel = true; ShowPointCloudMap = true; }

    public:
        AIAC::Mesh PointCloudMap;
        AIAC::Mesh DigitalModel;
        std::vector<AIAC::Mesh> Meshes;

        bool ShowPointCloudMap = true;
        bool ShowDigitalModel = true;

    private:
        void RenderMainView();

        void InitGlobalView();
        void InitMappingView();
        void RenderGlobalView();
        void RenderMappingView();


        void RenderCameraFrame();

    private:
        float m_CamW, m_CamH;

        GLuint m_BasicShaderProgram;
        GLuint m_MatrixId;

        glm::mat4 m_ProjMatrix;

        // Global view
        Viewport m_GlobalView;
        glm::mat4 m_GlobalCamMatrix;
        glm::mat4 m_GlobalProjMatrix;

        Viewport m_MappingView;

        std::vector<glm::vec3> m_CamVisualizationEdges;

        glm::vec4 m_DefaultEdgeColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        glm::vec4 m_PointCloudMapColor = glm::vec4(0.9, 0.9, 0.9, 0.2);
        glm::vec4 m_DigitalModelBoundingBoxColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        glm::vec4 m_DigitalModelFaceColor = glm::vec4(0.6, 0.35, 0.2, 0.3);
    };
}