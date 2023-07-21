cmake_minimum_required(VERSION 3.16.)
project(AC VERSION 0.1.0 LANGUAGES CXX C)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
if (MSVC)
    add_compile_options(/permissive-) 
endif()

#TODO: check for Opencv 4.5.4 that cannot be installed or detected


# Get hpp/cpp of AIAC module
file(GLOB AIAC_SRC  # FIXME: try to not include headers, this should be the correct way. Or try oarget include directories only.
    "src/AIAC/*.h"
    "src/AIAC/*.cpp"
    "src/AIAC/UI/*.h"
    "src/AIAC/UI/*.cpp"
    "src/AIAC/EventSys/*.h"
    "src/AIAC/EventSys/*.cpp"
    "src/AIAC/GOSys/*.h"
    "src/AIAC/GOSys/*.cpp"
    "src/AIAC/Render/*.h"
    "src/AIAC/Render/*.cpp"
    "src/utils/*"
    "src/AIAC.h"
    )


add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ACApp.cpp
    ${AIAC_SRC}
        src/AIAC/Render/Viewport.cpp src/AIAC/Render/Viewport.h src/AIAC/LayerCameraCalib.cpp src/AIAC/LayerCameraCalib.h src/utils/glob.cpp src/utils/glob.h src/AIAC/GeometryUtils.cpp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

#------------------------------------------------------------------------------------------------------------
# Pre compiled headers
#------------------------------------------------------------------------------------------------------------

target_precompile_headers(${PROJECT_NAME} PRIVATE src/aiacpch.h)


#------------------------------------------------------------------------------------------------------------
# Add options
#------------------------------------------------------------------------------------------------------------

# *As a fresh new compile, put everything ON
# -------------------- COMPILE OPTIONS -----------------------------
option(INSTALL_GLFW33 "Install glfw3 with dpkg OFF" OFF)
option(INSTALL_OPENGL "Install OpenGL with dpkg" OFF)
option(INSTALL_OPENCV455 "Install Opencv4.5.4 OFF" OFF)
option(INSTALL_ASSIMP "Install assimp with dpkg" OFF)
option(INSTALL_TSLAM "Install TSlam in case it has been updated" OFF)
option(INSTALL_TTOOL "Install TTool in case it has been updated" OFF)
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
if(UNIX AND INSTALL_OPENGL)
    message(WARNING "OpenGL not found, trying to install it...")
    execute_process(COMMAND ./cmake/install_opengl.sh)
endif()
set(OpenGL_GL_PREFERENCE LEGACY)  # <-- temp fix: or GLVIND?
find_package(OpenGL REQUIRED)
execute_process(COMMAND glxinfo -B OUTPUT_VARIABLE GLXINFO
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
# string(REGEX MATCH "OpenGL version string: ([0-9.]+)" GLXINFO ${GLXINFO})
# message(STATUS "OpenGL version: ${CMAKE_MATCH_1}")
message(STATUS "OpenGL icnlude dir: ${OPENGL_INCLUDE_DIR}")
message(STATUS "OpenGL libraries: ${OPENGL_LIBRARIES}")

#GLFW
if(UNIX AND INSTALL_GLFW33)
    execute_process(COMMAND ./cmake/install_glfw_3_3.sh
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()
find_package(glfw3 3.3 REQUIRED)

# OpenCV
if (UNIX AND INSTALL_OPENCV455)
    message(WARNING "Install OpenCV...")
    execute_process(COMMAND ./cmake/install_opencv_4_5_5.sh)
endif()
find_package(OpenCV 4.5.4 REQUIRED)   # FIXME: 4.5.4 not found (?)
if(OpenCV_FOUND)
    message(STATUS "OpenCV include dir: ${OpenCV_INCLUDE_DIRS}")
    message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")
endif()

# Assimp
if(UNIX AND INSTALL_ASSIMP)
    message(STATUS "Installing assimp")
    execute_process(COMMAND sudo apt-get install libassimp-dev)
endif()
find_package(assimp 5.0.0 REQUIRED)
message(STATUS "Assimp include dir: ${ASSIMP_INCLUDE_DIRS}")
message(STATUS "Assimp lib dir: ${ASSIMP_LIBRARIES}")

find_package(TBB REQUIRED)

# TSlam
if(UNIX AND INSTALL_TSLAM)
    message(WARNING "Re/Compiling TSlam...")
    execute_process(COMMAND ./cmake/install_TSlam.sh
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()
find_package(TSlam REQUIRED)
if(TSlam_FOUND)
    message(STATUS "TSlam version: ${TSlam_VERSION}")
    message(STATUS "TSlam include dir: ${TSlam_INCLUDE_DIRS}")
    message(STATUS "TSlam libraries dir: ${TSlam_LIB_DIR}")
    message(STATUS "TSlam libraries: ${TSlam_LIBS}")
endif()

# TTool
if(UNIX AND INSTALL_TTOOL)
    message(WARNING "Re/Compiling TTool...${INSTALL_TTOOL}")
    execute_process(COMMAND ./cmake/install_TTool.sh
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()
find_package(TTool REQUIRED)
if(TTool_FOUND)
    message(STATUS "TTool version: ${TTool_VERSION}")
    message(STATUS "TTool include dir: ${TTool_INCLUDE_DIRS}")
    message(STATUS "TTool libraries dir: ${TTool_LIBRARY_DIRS}")
    message(STATUS "TTool libraries: ${TTool_LIBRARIES}")
endif()

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/deps/TTool/deps/libtorch")
find_package(Torch REQUIRED)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${OPENGL_INCLUDE_DIRS}
    PUBLIC ${OpenCV_INCLUDE_DIRS}
    PUBLIC ${TSlam_INCLUDE_DIRS}
    PUBLIC ${TTool_INCLUDE_DIRS}
    PUBLIC ${ASSIMP_INCLUDE_DIRS}
    )

target_link_libraries(${PROJECT_NAME}
    ${OPENGL_LIBRARIES}
    ${OpenCV_LIBS}
    ${TSlam_LIBS}
    ${TTool_LIBRARIES}
    ${CMAKE_DL_LIBS}
    glfw
    assimp
    GLU
    TBB::tbb
    ${TORCH_LIBRARIES}
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
# LOCAL 3rd libs (compatible with add_subdirectory())
#------------------------------------------------------------------------------------------------------------

# Include directory of all deps, add subdir and link (if CMakeLists.txt is present)
set(DEPS_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/deps)
target_include_directories(${PROJECT_NAME} PUBLIC ${DEPS_DIRS})

file(GLOB DEPS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/deps ${CMAKE_CURRENT_SOURCE_DIR}/deps/*)
foreach(DEP ${DEPS})
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/deps/${DEP}/CMakeLists.txt)

        add_subdirectory(deps/${DEP})

        target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/deps/${DEP})

        target_link_libraries(${PROJECT_NAME} ${DEP})

    else()
        message(WARNING "No CMakeLists.txt file found in ${DEP} folder.")
    endif()
endforeach()


#------------------------------------------------------------------------------------------------------------
# Temporary Patches
#------------------------------------------------------------------------------------------------------------

# FIXME: to be replaced for healthier solution (without it doesnt indlue -ldl, math gcc libs) --> test without
if(UNIX)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})
endif()


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
