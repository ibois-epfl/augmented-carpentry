#include <iostream>

#include "AIAC/LayerRender.h"

#include "AIAC/Application.h"
#include "AIAC/Log.h"

#include "glm/glm.hpp"
#include "glm/gtx/string_cast.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtc/matrix_transform.hpp"
#include "utils/shader.hpp"

// only for test
#include "glm/gtc/type_ptr.hpp"
#include "AIAC/Mesh.h"

GLuint programID;
GLuint MatrixID;
glm::mat4 Projection;
glm::mat4 View, Model, MVP;
AIAC::Mesh bonny;

namespace AIAC
{
    void LayerRender::OnAttach()
    {
        // Create and compile our GLSL program from the shaders
        programID = LoadShaders("assets/opengl/SimpleTransform.vertexshader", "assets/opengl/SimpleFragmentShader.fragmentshader");

        // Get a handle for our "MVP" uniform
        // MatrixID = glGetUniformLocation(programID, "MVP");

        //        // Projection matrix : 45 degree Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
        //        Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
        //
        //        // Camera matrix
        //        View       = glm::lookAt(
        //                            glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
        //                            glm::vec3(0,0,0), // and looks at the origin
        //                            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
        //                    );
        //        // Model matrix : an identity matrix (model will be at the origin)
        //        Model      = glm::mat4(1.0f);
        //        // Our ModelViewProjection : multiplication of our 3 matrices
        //        MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around

        bonny = AIAC::Mesh("assets/tslam/example.ply");
    }

    void LayerRender::OnUIRender()
    {
        glUseProgram(programID);

        glm::mat4 camPose = AIAC_APP.GetLayer<LayerSlam>()->GetCamPoseGlm();
        glm::mat4 finalPose = camPose;

        finalPose[0][1] *= 0.1f;
        finalPose[0][2] *= 0.1f;

        finalPose[1][0] *= 0.1f;
        finalPose[1][2] *= 0.1f;

        finalPose[2][0] *= 0.1f;
        finalPose[2][1] *= 0.1f;

        finalPose[3][0] *= 0.1f;
        finalPose[3][1] *= 0.1f;
        finalPose[3][2] *= 0.1f;

        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &finalPose[0][0]);

        bonny.Draw();
    }
}