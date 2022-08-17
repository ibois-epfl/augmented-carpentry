#include "aiacpch.h"

#include "AIAC/LayerRender.h"

#include "AIAC/Application.h"
#include "AIAC/Log.h"

#include "glm/glm.hpp"
#include "glm/gtx/string_cast.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtc/matrix_transform.hpp"
#include "utils/shader.hpp"

#include "utils/utils.h"

// only for test
#include "glm/gtc/type_ptr.hpp"
#include "AIAC/Mesh.h"

namespace AIAC
{
    void LayerRender::OnAttach()
    {

        // Create and compile our GLSL program from the shaders
        std::string vertexFilePath = "assets/opengl/SimpleTransform.vertexshader";
        std::string fragmentFilePath = "assets/opengl/SingleColor.fragmentshader";
        assert(IsFileExist(vertexFilePath));
        assert(IsFileExist(fragmentFilePath));
        m_ProgramId = LoadShaders(vertexFilePath.c_str(), fragmentFilePath.c_str());

        // Get a handle for our "MVP" uniform
        m_MatrixId = glGetUniformLocation(m_ProgramId, "MVP");

        // Init projection matrix
        // int displayW, displayH;
        AIAC_APP.GetWindow()->OnUpdate();
        // glfwGetFramebufferSize(AIAC_APP.GetWindow()->GetGLFWWindow(), &displayW, &displayH);
        glm::mat4 perspectiveProjMatrix = glm::perspective(
                                    AIAC_APP.GetLayer<LayerCamera>()->MainCamera.GetFov().second,
                                    (float)AIAC_APP.GetWindow()->GetDisplayW() / (float)AIAC_APP.GetWindow()->GetDisplayH(),
                                    0.01f,
                                    100.0f );

        // opencv and opengl has different direction on y and z axis
        glm::mat4 scalarMatrix(1.0f);
        scalarMatrix[1][1] = -1;
        scalarMatrix[2][2] = -1;

        m_ProjMatrix = perspectiveProjMatrix * scalarMatrix;

        // Load meshes
        Meshes.emplace_back("assets/tslam/example3dModel.ply");
        Meshes.emplace_back("assets/tslam/examplePointCloud.ply");

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

        // Set "renderedTexture" as our colour attachement #0
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

        // Set the list of draw buffers.
        GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
        glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

//        // Always check that our framebuffer is ok
//        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//            return false;
    }

    void LayerRender::OnUIRender()
    {
        // Render to our framebuffer
        // int displayW, displayH;
        // glfwGetFramebufferSize(AIAC_APP.GetWindow()->GetGLFWWindow(), &displayW, &displayH);

        // Render to our framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, m_OverlayFrameBuffer);
        glViewport(0,0,AIAC_APP.GetWindow()->GetDisplayW(),AIAC_APP.GetWindow()->GetDisplayH()); // Render on the whole framebuffer, complete from the lower left corner to the upper right

        // Clear the screen
        glClearColor(0.0f,0.0f,0.0f,0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


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

        // Combine the camera frame with the rendered frame
        // Bind Back to default framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);


        GLuint readFboIdFrame = 0;
        glGenFramebuffers(1, &readFboIdFrame);
        glBindFramebuffer(GL_READ_FRAMEBUFFER, readFboIdFrame);
//
//        GLuint readFboId = 0;
//        glGenFramebuffers(1, &readFboId);
//        glBindFramebuffer(GL_READ_FRAMEBUFFER, readFboId);

        glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                               GL_TEXTURE_2D, AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetCurrentFrame().GetGlTextureId(), 0);
        glBlitFramebuffer(0, 0, 640, 480,
                          0, 0, AIAC_APP.GetWindow()->GetDisplayW(), AIAC_APP.GetWindow()->GetDisplayH(),
                          GL_COLOR_BUFFER_BIT, GL_LINEAR);
//        glBindFramebuffer(GL_READ_FRAMEBUFFER, readFboId);


//
//        glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
//                               GL_TEXTURE_2D, m_OverlayFrameBuffer, 0);
//        glBlitFramebuffer(0, 0, AIAC_APP.GetWindow()->GetDisplayW(), AIAC_APP.GetWindow()->GetDisplayH(),
//                          0, 0, AIAC_APP.GetWindow()->GetDisplayW(), AIAC_APP.GetWindow()->GetDisplayH(),
//                          GL_COLOR_BUFFER_BIT, GL_LINEAR);
//        glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);


//        glDeleteFramebuffers(1, &readFboIdFrame);

    }
}