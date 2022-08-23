#include "aiacpch.h"

#include "AIAC/Renderer.h"

#include "AIAC/Application.h"
#include "AIAC/Log.h"
#include "AIAC/Config.h"

#include "glm/glm.hpp"
#include "glm/gtx/string_cast.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtc/matrix_transform.hpp"
#include "utils/shader.hpp"

#include "utils/utils.h"

namespace AIAC
{
    void Renderer::Init()
    {
        GLuint VertexArrayID;
        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);

        // Create and compile our GLSL program from the shaders
        std::string vertexFilePath = "assets/opengl/SimpleTransform.vertexshader";
        std::string fragmentFilePath = "assets/opengl/SingleColor.fragmentshader";
        assert(IsFileExist(vertexFilePath));
        assert(IsFileExist(fragmentFilePath));
        m_ProgramId = LoadShaders(vertexFilePath.c_str(), fragmentFilePath.c_str());

        // Get a handle for our "MVP" uniform
        m_MatrixId = glGetUniformLocation(m_ProgramId, "MVP");

        // Calculate Perspective Projection Matrix based on camera intrinsic parameters
        // Reference: https://strawlab.org/2011/11/05/augmented-reality-with-OpenGL/
        cv::Mat cameraMatrix = AIAC_APP.GetLayer<LayerCamera>()->MainCamera.GetCameraMatrix();
        float camW = AIAC_APP.GetLayer<LayerCamera>()->MainCamera.GetWidth();
        float camH = AIAC_APP.GetLayer<LayerCamera>()->MainCamera.GetHeight();
        float x0 = 0, y0 = 0,zF = 100.0f, zN =0.01f;
        float fovX = cameraMatrix.at<float>(0,0);
        float fovY = cameraMatrix.at<float>(1,1);
        float cX = cameraMatrix.at<float>(0,2);
        float cY = cameraMatrix.at<float>(1,2);
        float perspectiveProjMatrixData[16] = {
                 2 * fovX / camW, 0,   (camW - 2 * cX + 2 * x0) / camW,  0,
                 0,   2 * fovY / camH, (-camH + 2 * cY + 2 * y0) / camH, 0,
                 0,   0,               (-zF - zN)/(zF - zN),             -2 * zF * zN / (zF - zN),
                 0,  0,                -1,                               0
        };

        glm::mat4 perspectiveProjMatrix = glm::transpose(glm::make_mat4(perspectiveProjMatrixData));

        // opencv and opengl has different direction on y and z axis
        glm::mat4 scalarMatrix(1.0f);
        scalarMatrix[1][1] = -1;
        scalarMatrix[2][2] = -1;

        m_ProjMatrix = perspectiveProjMatrix * scalarMatrix;

        // Load meshes
        ReloadMeshes();

        GLuint renderedTexture;
        glGenTextures(1, &renderedTexture);

        // "Bind" the newly created texture : all future texture functions will modify this texture
        glBindTexture(GL_TEXTURE_2D, renderedTexture);

        // Give an empty image to OpenGL ( the last "0" )
        glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, AIAC_APP.GetWindow()->GetDisplayW(), AIAC_APP.GetWindow()->GetDisplayH(), 0,GL_RGB, GL_UNSIGNED_BYTE, 0);

        // Poor filtering. Needed !
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        // The depth buffer
        GLuint depthrenderbuffer;
        glGenRenderbuffers(1, &depthrenderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, AIAC_APP.GetWindow()->GetDisplayW(), AIAC_APP.GetWindow()->GetDisplayH());
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

        // Set "renderedTexture" as our colour attachment #0
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

        // Set the list of draw buffers.
        GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
        glDrawBuffers(1, DrawBuffers);

        // Enable alpha channel for transparency
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);

        // Save variable for later use
        m_CamW = AIAC_APP.GetLayer<LayerCamera>()->MainCamera.GetWidth();
        m_CamH = AIAC_APP.GetLayer<LayerCamera>()->MainCamera.GetHeight();

        m_InitGlobalView();
    }

    void Renderer::m_InitGlobalView() {
        glGenFramebuffers(1, &m_GlobalViewFrameBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, m_GlobalViewFrameBuffer);

        // The texture we're going to render to
        glGenTextures(1, &m_GlobalViewTexture);

        // "Bind" the newly created texture : all future texture functions will modify this texture
        glBindTexture(GL_TEXTURE_2D, m_GlobalViewTexture);

        // Give an empty image to OpenGL ( the last "0" )
        glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, 640, 480, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);

        // Poor filtering. Needed !
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        // The depth buffer
        GLuint depthrenderbuffer;
        glGenRenderbuffers(1, &depthrenderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 640, 480);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

        // Set "renderedTexture" as our colour attachement #0
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_GlobalViewTexture, 0);

        // Set the list of draw buffers.
        GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
        glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

        // build camera visualization object, which is a pyramid
        float bW = 1.0f / 2, bH = 0.75f / 2, h = 0.5f;
        m_CamVisualizationEdges.emplace_back( bW,  bH, 0);
        m_CamVisualizationEdges.emplace_back( bW, -bH, 0);
        m_CamVisualizationEdges.emplace_back( bW, -bH, 0);
        m_CamVisualizationEdges.emplace_back(-bW, -bH, 0);
        m_CamVisualizationEdges.emplace_back(-bW, -bH, 0);
        m_CamVisualizationEdges.emplace_back(-bW,  bH, 0);
        m_CamVisualizationEdges.emplace_back(-bW,  bH, 0);
        m_CamVisualizationEdges.emplace_back( bW,  bH, 0);
        m_CamVisualizationEdges.emplace_back(  0,   0,-h);
        m_CamVisualizationEdges.emplace_back( bW,  bH, 0);
        m_CamVisualizationEdges.emplace_back(  0,   0,-h);
        m_CamVisualizationEdges.emplace_back(-bW,  bH, 0);
        m_CamVisualizationEdges.emplace_back(  0,   0,-h);
        m_CamVisualizationEdges.emplace_back(-bW, -bH, 0);
        m_CamVisualizationEdges.emplace_back(  0,   0,-h);
        m_CamVisualizationEdges.emplace_back( bW, -bH, 0);

        m_GlobalProjMatrix = glm::perspective(
                glm::radians(45.0f),
                4.0f / 3.0f, 0.1f,100.0f
        );

        m_GlobalCamMatrix = glm::lookAt(
                glm::vec3(30, 30, 30), // the position of your camera, in world space
                DigitalModel.BoundingBoxCenter,   // where you want to look at, in world space
                glm::vec3(0, 1, 0)        // probably glm::vec3(0,1,0), but (0,-1,0) would make you looking upside-down, which can be great too
        );
    }

    void Renderer::ReloadMeshes()
    {
        auto pointCloudMapPath = AIAC::Config::Get<string>("Renderer", "PointCloudMapPath", "assets/tslam/examplePointCloud.ply");
        auto digitalModelPath = AIAC::Config::Get<string>("Renderer", "DigitalModelPath", "assets/tslam/example3dModel.ply");

        PointCloudMap = Mesh(pointCloudMapPath);
        DigitalModel = Mesh(digitalModelPath);

        std::vector<std::string> meshPaths = AIAC::Config::GetVector<string>("Renderer", "MeshPaths", {});
        for(auto path : meshPaths) {
            Meshes.emplace_back(path);
        }
    }

    void Renderer::OnRender()
    {
        // Renderer to our framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        GLuint readFboIdFrame = 0;
        glGenFramebuffers(1, &readFboIdFrame);
        glBindFramebuffer(GL_READ_FRAMEBUFFER, readFboIdFrame);
        glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                               GL_TEXTURE_2D, AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetCurrentFrame().GetGlTextureObj(), 0);

        glBlitFramebuffer(0, 0, m_CamW, m_CamH,
                          0, 0, AIAC_APP.GetWindow()->GetDisplayW(), AIAC_APP.GetWindow()->GetDisplayH(),
                          GL_COLOR_BUFFER_BIT, GL_LINEAR);
        glDeleteFramebuffers(1, &readFboIdFrame);

        // Renderer to our framebuffer
        glViewport(0,0,AIAC_APP.GetWindow()->GetDisplayW(),AIAC_APP.GetWindow()->GetDisplayH()); // Renderer on the whole framebuffer, complete from the lower left corner to the upper right

        glUseProgram(m_ProgramId);

        // Get Cam pose
        glm::mat4 finalPoseMatrix = m_ProjMatrix * AIAC_APP.GetLayer<LayerSlam>()->GetCamPoseGlm();
        glUniformMatrix4fv(m_MatrixId, 1, GL_FALSE, &finalPoseMatrix[0][0]);

        // Draw the triangle !
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glm::vec4 edgeColor;
        if(AIAC_APP.GetLayer<LayerSlam>()->IsTracked()) {
            if(ShowPointCloudMap){
                PointCloudMap.DrawVertices(m_PointCloudMapColor, 1);
            }
            if(ShowDigitalModel){
                DigitalModel.DrawBoundingBoxEdges(m_DigitalModelBoundingBoxColor);
                DigitalModel.DrawFaces(m_DigitalModelFaceColor);
            }
            for (auto& mesh : Meshes) {
                mesh.DrawEdges(m_DefaultEdgeColor);
            }
        }
        // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        m_RenderGlobalView();
    }

    void Renderer::UpdateGlobalViewCameraRotation(double diffX, double diffY){
        auto t1 = glm::translate(glm::mat4(1),-DigitalModel.BoundingBoxCenter);
        auto rx = glm::rotate(glm::mat4(1), float(-diffX / 100), glm::vec3(0,1,0));
        auto ry = glm::rotate(glm::mat4(1), float(-diffY / 100), glm::vec3(1,0,0));
        auto t2 = glm::translate(glm::mat4(1), DigitalModel.BoundingBoxCenter);
        m_GlobalCamMatrix = m_GlobalCamMatrix * t2 * rx * ry * t1;
    }

    void Renderer::UpdateGlobalViewCameraTranslation(double diffX, double diffY){
        m_GlobalCamMatrix[3][0] += float(diffX) / 10;
        m_GlobalCamMatrix[3][1] -= float(diffY) / 10;
    }

    void Renderer::m_RenderGlobalView() {
        glBindFramebuffer(GL_FRAMEBUFFER, m_GlobalViewFrameBuffer);
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // visualize map
        glm::mat4 finalPoseMatrix = m_GlobalProjMatrix * m_GlobalCamMatrix;
        glUniformMatrix4fv(m_MatrixId, 1, GL_FALSE, &finalPoseMatrix[0][0]);

        PointCloudMap.DrawVertices(m_PointCloudMapColor, 1);
        DigitalModel.DrawBoundingBoxEdges(m_DigitalModelBoundingBoxColor);
        DigitalModel.DrawFaces(m_DigitalModelFaceColor);
        for (auto& mesh : Meshes) {
            mesh.DrawEdges(m_DefaultEdgeColor);
        }

        // visualize camera
        auto camPoseInv = AIAC_APP.GetLayer<LayerSlam>()->GetInvCamPoseGlm(); // camera pose in world space
        glm::mat4 cameraSpaceMVP = m_GlobalProjMatrix * m_GlobalCamMatrix * camPoseInv;
        glUniformMatrix4fv(m_MatrixId, 1, GL_FALSE, &cameraSpaceMVP[0][0]);
        DrawLines3d(m_CamVisualizationEdges, glm::vec4(0, 0, 1, 1));

        // Bind back to the main framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

    }
}