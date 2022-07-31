
cmake_minimum_required(VERSION 3.1.0)
project(AC VERSION 0.1.0 LANGUAGES CXX)

include(CTest)
enable_testing()

add_executable(${PROJECT_NAME} main.cpp)

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


# # ImGUI
# set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/imgui)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation" FORCE)
set(GLFW_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw/include)
add_subdirectory(deps/glfw)


target_include_directories(${PROJECT_NAME} 
    PUBLIC ${OPENGL_INCLUDE_DIRS} 
    PUBLIC ${GLFW_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} 
                        ${OPENGL_LIBRARIES}
                        glfw
                        )



# CPack
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
