
#include <iostream>
#include <string>

#include <GL/glut.h>
#include <GL/gl.h>

#include "GLFW/glfw3.h"

// #include "../deps/imgui/imgui.h"

#include "deps/imgui/imgui.h"

void displayMe(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
        glVertex3f(0.5, 0.0, 0.5);
        glVertex3f(0.5, 0.0, 0.0);
        glVertex3f(0.0, 0.5, 0.0);
        glVertex3f(0.0, 0.0, 0.5);
    glEnd();
    glFlush();
}

int main(int argc, char** argv)
{
    // glutInit(&argc, argv);
    // glutInitDisplayMode(GLUT_SINGLE);
    // glutInitWindowSize(400, 300);
    // glutInitWindowPosition(100, 100);
    // glutCreateWindow("Hello world!");
    // glutDisplayFunc(displayMe);
    // glutMainLoop();

    std::cout << "Hello world!" << std::endl;

    GLFWwindow* window;
    if(!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }
    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if(!window)
    {
        fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    //  Main loop
    while(!glfwWindowShouldClose(window))
    {
        //  Get size of framebuffer
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        //  Set viewport
        glViewport(0, 0, width, height);
        //  Clear color buffer
        glClear(GL_COLOR_BUFFER_BIT);
        //  Draw one triangle
        glBegin(GL_TRIANGLES);
        glColor3f(1,0,0);
        glVertex2f(-0.6,-0.75);
        glColor3f(0,1,0);
        glVertex2f(0.6,-0.75);
        glColor3f(0,0,1);
        glVertex2f(0,0.75);
        glEnd();
        //  Swap buffers
        glfwSwapBuffers(window);
        //  Poll for events
        glfwPollEvents();
    }

    return 0;
}
