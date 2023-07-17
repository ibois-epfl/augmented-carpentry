cmake_minimum_required(VERSION 3.16.)
project(AC VERSION 0.1.0 LANGUAGES CXX C)

include(CTest)
enable_testing()

set(BUILD_SHARED_LIBS ON)
#set(CMAKE_CXX_STANDARD 17)
#TODO: check for Opencv 4.5.4 that cannot be installed or detected
file(GLOB_RECURSE AIAC_SRC "src/*.cpp")


add_executable(${PROJECT_NAME}
    ${AIAC_SRC})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

#-------------------------------------------------------------------------------
# Pre compiled headers
#-------------------------------------------------------------------------------
target_precompile_headers(${PROJECT_NAME} PRIVATE src/aiacpch.h)

#-------------------------------------------------------------------------------
# Add options
#-------------------------------------------------------------------------------

# *As a fresh new compile, put everything ON
# -------------------- COMPILE OPTIONS -----------------------------
# option(INSTALL_TSLAM "Install TSlam in case it has been updated" OFF)
# option(INSTALL_TTOOL "Install TTool in case it has been updated" OFF)
# ------------------------------------------------------------------------------
# option(INSTALL_GLFW33 "Install glfw3 with dpkg" OFF)
# option(INSTALL_OPENGL "Install OpenGL with dpkg" OFF)
# option(INSTALL_OPENCV455 "Install Opencv4.5.4" OFF)
# option(INSTALL_ASSIMP "Install assimp with dpkg" OFF)
# -------------------- PREPROCESSOR VAR OPTIONS --------------------
option(DEPLOY_ON_TOUCH "Build AC for testing on an external touch monitor" OFF)
option(ENABLE_ASSERT "Enable assertion in code" ON)
option(SILENT_LOGGING "Do not log messages in the terminal if on." ON)
# -------------------- TEST OPTIONS --------------------------------
option(TEST_GRAPHICS "Test graphics by launching opengl with glfw window." ON)

# pre-compile variables
target_compile_definitions(${PROJECT_NAME}
    PUBLIC AC_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
    PUBLIC AC_VERSION_MINOR=${PROJECT_VERSION_MINOR}
    PUBLIC AC_VERSION_PATCH=${PROJECT_VERSION_PATCH}
)

if(DEPLOY_ON_TOUCH)
    target_compile_definitions(${PROJECT_NAME} PRIVATE AIAC_DEPLOY_ON_TOUCH=true)
endif()
if(ENABLE_ASSERT)
    target_compile_definitions(${PROJECT_NAME} PRIVATE AIAC_ENABLE_ASSERTS=true)
endif()
if(SILENT_LOGGING)
    target_compile_definitions(${PROJECT_NAME} PRIVATE SILENT_LOGGING=true)
endif()

#------------------------------------------------------------------------------------------------------------
# GLOBAL 3rd libs (NOT compatible with add_subdirectory())
#------------------------------------------------------------------------------------------------------------
# OpenGL
# if(UNIX AND INSTALL_OPENGL)
#     message(WARNING "OpenGL not found, trying to install it...")
#     execute_process(COMMAND ./cmake/install_opengl.sh)
# endif()
set(OpenGL_GL_PREFERENCE LEGACY)  # <-- temp fix: or GLVIND?
find_package(OpenGL REQUIRED)

# execute_process(COMMAND glxinfo -B OUTPUT_VARIABLE GLXINFO
#                 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
# string(REGEX MATCH "OpenGL version string: ([0-9.]+)" GLXINFO ${GLXINFO})
# message(STATUS "OpenGL version: ${CMAKE_MATCH_1}")
message(STATUS "OpenGL icnlude dir: ${OPENGL_INCLUDE_DIR}")
message(STATUS "OpenGL libraries: ${OPENGL_LIBRARIES}")

set(BUILD_V4_API ON)
add_subdirectory(deps/TSlam)
add_subdirectory(deps/TTool)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenCV 4.5.4 REQUIRED)   # FIXME: 4.5.4 not found (?)
find_package(assimp 5.0.0 REQUIRED)

add_subdirectory(deps/imgui)
add_subdirectory(deps/spdlog)
add_subdirectory(deps/pugixml)
add_subdirectory(deps/freetype)


# Pytorch
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/deps/TTool/deps/libtorch")
find_package(Torch REQUIRED)

target_include_directories(${PROJECT_NAME}
    PUBLIC
      ${OpenCV_INCLUDE_DIRS}
    )

target_link_libraries(${PROJECT_NAME}
    ${OpenCV_LIBS}
    ${TSlam_LIBS}
    TTool::ttool
    TSlam::tslam
    OpenGL::GL
    OpenGL::GLU
    imgui::imgui
    spdlog::spdlog
    pugixml::pugixml
    freetype
    glfw
    )

#------------------------------------------------------------------------------------------------------------
# Check and update git submodules
#------------------------------------------------------------------------------------------------------------

# Download and update submodules with latest remote version
# find_package(Git QUIET)
# if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
#     option(GIT_SUBMODULE "Check submodules during build" ON)
#     if(GIT_SUBMODULE)
#         message(STATUS "Submodule update with latest commit")

#         execute_process(
#             COMMAND ${GIT_EXECUTABLE} --version
#             OUTPUT_VARIABLE GIT_VERSION_STRING
#         )
#         string(REGEX MATCH "([0-9]+)\\.([0-9]+)\\.([0-9]+)" GIT_VERSION_STRING ${GIT_VERSION_STRING})
#         set(GIT_VERSION_MAJOR ${CMAKE_MATCH_1})
#         set(GIT_VERSION_MINOR ${CMAKE_MATCH_2})
#         set(GIT_VERSION_PATCH ${CMAKE_MATCH_3})

#         if(NOT (GIT_VERSION_MAJOR GREATER 1 OR (GIT_VERSION_MAJOR EQUAL 1 AND GIT_VERSION_MINOR GREATER 8)))
#             message(FATAL_ERROR "Git version 1.8 or greater is required.")
#         endif()
#         execute_process(COMMAND ${GIT_EXECUTABLE} submodule sync
#                         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
#         execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive --remote
#                         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#                         RESULT_VARIABLE GIT_SUBMOD_RESULT)
#         if(NOT GIT_SUBMOD_RESULT EQUAL "0")
#             message(FATAL_ERROR "git submodule update --init --recursive --remote failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
#         endif()
#     endif()
# endif()

#------------------------------------------------------------------------------------------------------------
# CTest (unit tests)
#------------------------------------------------------------------------------------------------------------

# Testing adds
if (TEST_PLATFORM)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests/platform)
endif()
if(TEST_GRAPHICS)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests/graphics)
endif()
