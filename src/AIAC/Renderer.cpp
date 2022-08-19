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
                 0,   0,              (-zF - zN)/(zF - zN),            -2 * zF * zN / (zF - zN),
                0,  0,               -1,                              0
        };

        glm::mat4 perspectiveProjMatrix = glm::transpose(glm::make_mat4(perspectiveProjMatrixData));

        // opencv and opengl has different direction on y and z axis
        glm::mat4 scalarMatrix(1.0f);
        scalarMatrix[1][1] = -1;
        scalarMatrix[2][2] = -1;

        m_ProjMatrix = perspectiveProjMatrix * scalarMatrix;

        // Load meshes

        ReloadMeshes();

        // Meshes.emplace_back("/home/tpp/UCOSlam-IBOIS/build/utils/long_new_param_comb.ply");
        // Meshes.emplace_back("/home/tpp/UCOSlam-IBOIS/build/utils/long_new_param_comb_mesh.ply");


        // Init framebuffer
        glGenFramebuffers(1, &m_OverlayFrameBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, m_OverlayFrameBuffer);

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

        // Save variable for later use
        m_CamW = AIAC_APP.GetLayer<LayerCamera>()->MainCamera.GetWidth();
        m_CamH = AIAC_APP.GetLayer<LayerCamera>()->MainCamera.GetHeight();

    }

    void Renderer::ReloadMeshes()
    {
        std::vector<std::string> defaultMeshPaths = {"assets/tslam/example3dModel.ply", "assets/tslam/examplePointCloud.ply"};
        std::vector<std::string> meshPaths = AIAC::Config::GetVector<string>("Renderer", "MeshPaths", defaultMeshPaths);
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
        for (auto& mesh : Meshes) {
            mesh.Draw();
        }
        // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    }
}