
cmake_minimum_required(VERSION 3.1.0)
project(cc_project VERSION 0.1.0 LANGUAGES CXX)

include(CTest)
enable_testing()

add_executable(${PROJECT_NAME} src/main.cpp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)


##########################
## 3rd libs
##########################

# OpenGL
set(OpenGL_GL_PREFERENCE LEGACY)  # <-- temp fix: or GLVIND?
find_package(OpenGL REQUIRED)
message(STATUS "Is OpenGL found: ${OPENGL_FOUND}")
message(STATUS "OpenGL found at: ${OPENGL_INCLUDE_DIR}")
message(STATUS "OpenGL libraries: ${OPENGL_LIBRARIES}")

# GLUT
find_package(GLUT REQUIRED)
message(STATUS "Is GLUT found: ${GLUT_FOUND}")
message(STATUS "GLUT found at: ${GLUT_INCLUDE_DIR}")
message("GLUT_LIB : ${GLUT_LIBRARIES}")

# ImGUI
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/imgui)

include_directories(${PROJECT_NAME}
                        ${OPENGL_INCLUDE_DIRS}
                        ${GLUT_INCLUDE_DIRS}
                        ${IMGUI_DIR}
                        )

target_link_libraries(${PROJECT_NAME} 
                        ${OPENGL_LIBRARIES}
                        ${GLUT_LIBRARIES}
                        )



# CPack
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
