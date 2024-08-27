cmake_minimum_required(VERSION 3.16.)
project(AC VERSION 0.1.0 LANGUAGES CXX C)


set(BUILD_SHARED_LIBS ON)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(external_tools)

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
# -------------------- PREPROCESSOR VAR OPTIONS --------------------
option(HEADLESS_TEST "Build and run for headless smoke test" OFF)
option(DEPLOY_ON_TOUCH "Build AC for testing on an external touch monitor" ON)
option(ENABLE_ASSERT "Enable assertion in code" ON)
option(SILENT_LOGGING "Do not log messages in the terminal if on." ON)
# -------------------- TEST OPTIONS --------------------------------
option(TEST_GRAPHICS "Test graphics by launching opengl with glfw window." ON)
option(AC_SYNC_GIT_SUBMODULES "Sync to the latest version of submodules" ON)
mark_as_advanced(AC_SYNC_GIT_SUBMODULES)
# -------------------- DEV UI OPTIONS --------------------------------
# This preprocessor variable is used to enable the dev ui in the application.
# In order to light up the beta tester's experience, the dev ui is disabled by default.
option(ENABLE_DEV_UI "Enable the dev ui in the application" OFF)


# pre-compile variables
target_compile_definitions(${PROJECT_NAME}
    PUBLIC AC_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
    PUBLIC AC_VERSION_MINOR=${PROJECT_VERSION_MINOR}
    PUBLIC AC_VERSION_PATCH=${PROJECT_VERSION_PATCH}
)

if(HEADLESS_TEST)
    target_compile_definitions(${PROJECT_NAME} PRIVATE HEADLESS_TEST=true)
endif()
if(DEPLOY_ON_TOUCH)
    target_compile_definitions(${PROJECT_NAME} PRIVATE AIAC_DEPLOY_ON_TOUCH=true)
endif()
if(ENABLE_ASSERT)
    target_compile_definitions(${PROJECT_NAME} PRIVATE AIAC_ENABLE_ASSERTS=true)
endif()
if(SILENT_LOGGING)
    target_compile_definitions(${PROJECT_NAME} PRIVATE SILENT_LOGGING=true)
endif()
if(ENABLE_DEV_UI)
    target_compile_definitions(${PROJECT_NAME} PRIVATE ENABLE_DEV_UI=true)
endif()

#------------------------------------------------------------------------------------------------------------
# GLOBAL 3rd libs (NOT compatible with add_subdirectory())
#------------------------------------------------------------------------------------------------------------
# OpenGL
set(OpenGL_GL_PREFERENCE LEGACY)  # <-- temp fix: or GLVIND?
find_package(OpenGL REQUIRED)

set(BUILD_V4_API ON)
add_external_package(TSlam IGNORE_SYSTEM)
add_external_package(TTool IGNORE_SYSTEM)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenCV 4.5.4 REQUIRED
    COMPONENTS
      core
      imgproc
      calib3d
      videoio
      highgui
      imgcodecs
)
find_package(assimp 5.0.0 REQUIRED)
find_package(GLEW REQUIRED)


add_external_package(imgui)
add_external_package(spdlog)
add_external_package(pugixml)
add_external_package(Freetype)
add_external_package(eventpp)


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
    Freetype::Freetype
    glfw
    GLEW::GLEW
    eventpp::eventpp
    )

#------------------------------------------------------------------------------------------------------------
# CTest (unit tests)
#------------------------------------------------------------------------------------------------------------
# Testing adds
# if (TEST_PLATFORM)
#     add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests/platform)
# endif()
# if(TEST_GRAPHICS)
#     add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests/graphics)
# endif()

if(HEADLESS_TEST)
    include(tests)
endif()