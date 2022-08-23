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

        GLuint GetGlobalView() { return m_GlobalViewTexture; };
        void UpdateGlobalViewCameraTranslation(double diffX, double diffY);
        void UpdateGlobalViewCameraRotation(double diffX, double diffY);

    public:
        AIAC::Mesh PointCloudMap;
        AIAC::Mesh DigitalModel;
        std::vector<AIAC::Mesh> Meshes;

        bool ShowPointCloudMap = true;
        bool ShowDigitalModel = true;

    private:
        void m_InitGlobalView();
        void m_RenderGlobalView();

    private:
        float m_CamW, m_CamH;

        GLuint m_ProgramId;
        GLuint m_MatrixId;

        glm::mat4 m_ProjMatrix;

        GLuint m_GlobalViewFrameBuffer;
        GLuint m_GlobalViewTexture;
        glm::mat4 m_GlobalCamMatrix;
        glm::mat4 m_GlobalProjMatrix;

        std::vector<glm::vec3> m_CamVisualizationEdges;

        glm::vec4 m_DefaultEdgeColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        glm::vec4 m_PointCloudMapColor = glm::vec4(0.9, 0.9, 0.9, 0.2);
        glm::vec4 m_DigitalModelBoundingBoxColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        glm::vec4 m_DigitalModelFaceColor = glm::vec4(0.6, 0.35, 0.2, 0.3);
    };
}