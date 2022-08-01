
cmake_minimum_required(VERSION 3.1.0)
project(AC VERSION 0.1 LANGUAGES CXX)

configure_file(ACConfig.h.in ACConfig.h)

# TODO: test if CTest is installed?
include(CTest)
enable_testing()

add_executable(${PROJECT_NAME} main.cpp)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})

##########################
## 3rd libs
##########################

# Check/Download first all the submodules
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update with latest commit")
        # check version of git
        execute_process(
            COMMAND ${GIT_EXECUTABLE} --version
            OUTPUT_VARIABLE GIT_VERSION_STRING
        )
        string(REGEX MATCH "([0-9]+)\\.([0-9]+)\\.([0-9]+)" GIT_VERSION_STRING ${GIT_VERSION_STRING})
        set(GIT_VERSION_MAJOR ${CMAKE_MATCH_1})
        set(GIT_VERSION_MINOR ${CMAKE_MATCH_2})
        set(GIT_VERSION_PATCH ${CMAKE_MATCH_3})
        if(NOT (GIT_VERSION_MAJOR GREATER 1 OR (GIT_VERSION_MAJOR EQUAL 1 AND GIT_VERSION_MINOR GREATER 8)))
            message(FATAL_ERROR "Git version 1.8 or greater is required.")
        endif()
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive --remote
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive --remote failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

# TODO: write function for this check of CMakelists.txt in each submodule
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/deps/glfw/CMakeLists.txt")
    message(FATAL_ERROR "The file deps/glfw/CMakeLists.txt does not exist. Please update or add one.")
endif()
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/deps/imgui/CMakeLists.txt")
    message(FATAL_ERROR "The file deps/imgui/CMakeLists.txt does not exist. Please update or add one.")
endif()
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/deps/spdlog/CMakeLists.txt")
    message(FATAL_ERROR "The file deps/spdlog/CMakeLists.txt does not exist. Please update or add one.")
endif()


# TODO: See if you can add/link opengl3 locally
# OpenGL
set(OpenGL_GL_PREFERENCE LEGACY)  # <-- temp fix: or GLVIND?
find_package(OpenGL REQUIRED)
message(STATUS "Is OpenGL found: ${OPENGL_FOUND}")
message(STATUS "OpenGL found at: ${OPENGL_INCLUDE_DIR}")
message(STATUS "OpenGL libraries: ${OPENGL_LIBRARIES}")

# ImGUI
set(IMGUI_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/deps/imgui)
add_subdirectory(deps/imgui)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation" FORCE)
set(GLFW_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw/include)
add_subdirectory(deps/glfw)

# spdlog
set(SPD_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/deps/spdlog/include/spdlog)
add_subdirectory(deps/spdlog)
message(STATUS "spdlog lib header only library ${spdlog}")

# TODO: Add OpenCV


target_include_directories(${PROJECT_NAME} 
    PUBLIC ${OPENGL_INCLUDE_DIRS} 
    PUBLIC ${GLFW_INCLUDE_DIRS}
    PUBLIC ${IMGUI_DIRS}
    PUBLIC ${SPD_DIRS}
    )

target_link_libraries(${PROJECT_NAME} 
                        ${OPENGL_LIBRARIES}
                        glfw
                        imgui
                        spdlog
                        spdlog
                        )


# CPack
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
