
cmake_minimum_required(VERSION 3.1.0)
project(AC VERSION 0.1.0 LANGUAGES CXX C)

include(CTest)
enable_testing()

# Get hpp/cpp of AIAC module
file(GLOB AIAC_SRC
    "src/AIAC/*.hpp"
    "src/AIAC/*.cpp"
)

add_executable(${PROJECT_NAME}
    src/main.cpp
    ${AIAC_SRC}
    )

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

#------------------------------------------------------------------------------------------------------------
# Add preprocessor definitions
#------------------------------------------------------------------------------------------------------------

option(SILENT_LOGGING "Do not log messages in the terminal of on." ON)

if(SILENT_LOGGING)
    target_compile_definitions(${PROJECT_NAME} PUBLIC SILENT_LOGGING=true)
endif()

# pre-compile macros versions
target_compile_definitions(${PROJECT_NAME}
    PUBLIC AC_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
    PUBLIC AC_VERSION_MINOR=${PROJECT_VERSION_MINOR}
    PUBLIC AC_VERSION_PATCH=${PROJECT_VERSION_PATCH}
    )


#------------------------------------------------------------------------------------------------------------
# GLOBAL 3rd libs
#------------------------------------------------------------------------------------------------------------

# OpenGL
set(OpenGL_GL_PREFERENCE LEGACY)  # <-- temp fix: or GLVIND?
find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND AND UNIX)
    message(WARNING "OpenGL not found, trying to install it...")
    execute_process(COMMAND ./cmake/install_opengl.sh)
elseif(NOT OPENGL_FOUND AND (WIN32 OR MSVC))
    message(FATAL_ERROR "augmented_carpentry does not support Windows yet.")
endif()
execute_process(COMMAND glxinfo -B OUTPUT_VARIABLE GLXINFO)
string(REGEX MATCH "OpenGL version string: ([0-9.]+)" GLXINFO ${GLXINFO})
message(STATUS "OpenGL version: ${CMAKE_MATCH_1}")
message(STATUS "OpenGL icnlude dir: ${OPENGL_INCLUDE_DIR}")
message(STATUS "OpenGL libraries: ${OPENGL_LIBRARIES}")

# OpenCV
find_package(OpenCV 4.5.5 REQUIRED)
if (NOT OpenCV_FOUND AND UNIX)
    message(WARNING "Right version of OpenCV not found, trying to install it...")
    execute_process(COMMAND ./cmake/install_opencv_4_5_5.sh)
elseif(NOT OpenCV_FOUND AND (WIN32 OR MSVC))
    message(FATAL_ERROR "augmented_carpentry does not support Windows yet.")
endif()
execute_process(COMMAND pkg-config --modversion opencv4 OUTPUT_VARIABLE OPENCV_VERSION)
message(STATUS "OpenCV version: ${OPENCV_VERSION}")
message(STATUS "OpenCV include dir: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")

# TSlam
find_package(TSlam REQUIRED)
if(TSlam_FOUND)
    message(STATUS "TSlam version: ${TSlam_VERSION}")
    message(STATUS "TSlam include dir: ${TSlam_INCLUDE_DIRS}")
    message(STATUS "TSlam libraries dir: ${TSlam_LIB_DIR}")
    message(STATUS "TSlam libraries: ${TSlam_LIBS}")
else()
    message(FATAL_ERROR "TSlam not found")
endif()

target_include_directories(${PROJECT_NAME}
    PUBLIC ${OPENGL_INCLUDE_DIRS}
    PUBLIC ${OpenCV_INCLUDE_DIRS}
    PUBLIC ${TSlam_INCLUDE_DIRS}
    )

target_link_libraries(${PROJECT_NAME} 
    ${OPENGL_LIBRARIES}
    ${OpenCV_LIBS}
    ${TSlam_LIBS}
    )


#------------------------------------------------------------------------------------------------------------
# LOCAL 3rd libs (sub-modules)
#------------------------------------------------------------------------------------------------------------

# Check/Download first all the submodules
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update with latest commit")

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

# add subdirectory() for each submodule + specific options for each(CMakeLists.txt needs to be present in each submodule)
file(GLOB DEPS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/deps ${CMAKE_CURRENT_SOURCE_DIR}/deps/*)
foreach(DEP ${DEPS})
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/deps/${DEP}/CMakeLists.txt)

        add_subdirectory(deps/${DEP})

        if(${DEP}=="glfw")
            message(STATUS "${DEP} is a submodule, setting up options for GLFW")
            set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation" FORCE)
            set(GLFW_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw/include)
            target_include_directories(${PROJECT_NAME} PUBLIC ${GLFW_INCLUDE_DIRS})
        elseif(${DEP}=="imgui")
            set(IMGUI_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/deps/imgui)
            target_include_directories(${PROJECT_NAME} PUBLIC ${IMGUI_DIRS})
        elseif(${DEP}=="spdlog")
            set(SPD_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/deps/spdlog/include/spdlog)
            target_include_directories(${PROJECT_NAME} PUBLIC ${SPD_DIRS})
        endif()
        target_link_libraries(${PROJECT_NAME} ${DEP})

    else()
        message(FATAL_ERROR "No CMakeLists.txt file found in ${DEP} folder. Exiting CMake...")
    endif()
endforeach()


#------------------------------------------------------------------------------------------------------------
# C-Packaging
#------------------------------------------------------------------------------------------------------------

# # CPack
# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

# include(CPack)
