#pragma once

// TODO: put this in the precompiled aiacpch.h file (?)

// <GL/glew.h> has to be included before <GLFW/glfw3.h>
#include "glew/include/GL/glew.h"

#include <GL/glut.h>
#include <GL/freeglut.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"