#include <iostream>

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
        int displayW, displayH;
        glfwGetFramebufferSize(AIAC_APP.GetWindow(), &displayW, &displayH);
        glm::mat4 perspectiveProjMatrix = glm::perspective(
                                    AIAC_APP.GetLayer<LayerCamera>()->MainCamera.GetFov().second,
                                    (float)displayW / (float)displayH,
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
    }

    void LayerRender::OnUIRender()
    {
        glUseProgram(m_ProgramId);

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