#include <iostream>

#include "AIAC/LayerRender.h"

#include "AIAC/Application.h"
#include "AIAC/Log.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "utils/shader.hpp"

// only for test
#include "glm/gtc/type_ptr.hpp"

GLuint programID;
GLuint vertexbuffer;
GLuint MatrixID;
glm::mat4 Projection;
glm::mat4 View, Model, MVP;

namespace AIAC
{
    void LayerRender::OnAttach()
    {
        GLuint VertexArrayID;
        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);

        // Create and compile our GLSL program from the shaders
        programID = LoadShaders("assets/opengl/SimpleTransform.vertexshader", "assets/opengl/SimpleFragmentShader.fragmentshader");

        // Get a handle for our "MVP" uniform
        MatrixID = glGetUniformLocation(programID, "MVP");

        // Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
        Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
        
        // Camera matrix
        View       = glm::lookAt(
                            glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
                            glm::vec3(0,0,0), // and looks at the origin
                            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                    );
        // Model matrix : an identity matrix (model will be at the origin)
        Model      = glm::mat4(1.0f);
        // Our ModelViewProjection : multiplication of our 3 matrices
        MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around


        static const GLfloat g_vertex_buffer_data[] = { 
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f,  1.0f, 0.0f,
        };

        glGenBuffers(1, &vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    }

    void LayerRender::OnFrameAwake()
    {
    }

    void LayerRender::OnFrameStart()
    {
        // Clear the screen
		// glClear( GL_COLOR_BUFFER_BIT );

		// Use our shader
		
		// Swap buffers
		// glfwSwapBuffers(AIAC_APP().GetWindow());
		// glfwPollEvents();
    }

    void LayerRender::OnFrameEnd()
    {
    }

    void LayerRender::OnUIRender()
    {
        glUseProgram(programID);

        // MVP[0][0] += 0.01f;
        // MVP[1][1] += 0.01f;
        // MVP[2][2] += 0.01f;

        glm::mat4 camPose = AIAC_APP().GetLayer<LayerSlam>()->GetCamPoseGlm();
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

        cv::Mat cvmat = cv::Mat(4, 4, CV_32F);
        memcpy(cvmat.data, glm::value_ptr(finalPose), 16 * sizeof(float));
        cvmat = cvmat.t();

        cout << cvmat << endl;

        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &finalPose[0][0]);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

		glDisableVertexAttribArray(0);
    }

    void LayerRender::OnFrameFall()
    {
    }

    void LayerRender::OnDetach()
    {
    }
}