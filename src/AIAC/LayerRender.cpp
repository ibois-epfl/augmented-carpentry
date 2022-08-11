#include <iostream>

#include "AIAC/LayerRender.h"

#include "AIAC/Application.h"
#include "AIAC/Log.h"

#include "utils/shader.hpp"

GLuint programID;
GLuint vertexbuffer;

namespace AIAC
{
    void LayerRender::OnAttach()
    {
        GLuint VertexArrayID;
        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);

        // Create and compile our GLSL program from the shaders
        programID = LoadShaders( "/home/tpp/ogl-master/tutorial02_red_triangle/SimpleVertexShader.fragmentshader", "/home/tpp/ogl-master/tutorial02_red_triangle/SimpleFragmentShader.fragmentshader" );

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