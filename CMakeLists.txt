
cmake_minimum_required(VERSION 3.1.0)
project(AC VERSION 0.1.0 LANGUAGES CXX)

include(CTest)
enable_testing()

add_executable(${PROJECT_NAME} main.cpp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)



##########################
## 3rd libs
##########################

# Check/Download first all the submodules
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} git submodule update --init --recursive --remote
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/deps/glfw/CMakeLists.txt")
    message(FATAL_ERROR "The file deps/glfw/CMakeLists.txt does not exist. Please update or add one.")
endif()
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/deps/imgui/CMakeLists.txt")
    message(FATAL_ERROR "The file deps/imgui/CMakeLists.txt does not exist. Please update or add one.")
endif()

# OpenGL
set(OpenGL_GL_PREFERENCE LEGACY)  # <-- temp fix: or GLVIND?
find_package(OpenGL REQUIRED)
message(STATUS "Is OpenGL found: ${OPENGL_FOUND}")
message(STATUS "OpenGL found at: ${OPENGL_INCLUDE_DIR}")
message(STATUS "OpenGL libraries: ${OPENGL_LIBRARIES}")


# ImGUI
# set(IMGUI_DIRs
#     ${CMAKE_CURRENT_SOURCE_DIR}/deps/imgui
#     ${CMAKE_CURRENT_SOURCE_DIR}/deps/imgui/backends)
set(IMGUI_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/deps/imgui)
add_subdirectory(deps/imgui)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation" FORCE)
set(GLFW_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw/include)
add_subdirectory(deps/glfw)


target_include_directories(${PROJECT_NAME} 
    PUBLIC ${OPENGL_INCLUDE_DIRS} 
    PUBLIC ${GLFW_INCLUDE_DIRS}
    PRIVATE ${IMGUI_DIRS}
    )

target_link_libraries(${PROJECT_NAME} 
                        ${OPENGL_LIBRARIES}
                        glfw
                        imgui
                        )



# CPack
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
