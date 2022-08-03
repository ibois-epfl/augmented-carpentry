
cmake_minimum_required(VERSION 3.1.0)
project(AC VERSION 0.1.0 LANGUAGES CXX)

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

####################################################
## GLOBAL 3rd libs
####################################################

# TODO: See if you can add/link opengl3 locally
# OpenGL
set(OpenGL_GL_PREFERENCE LEGACY)  # <-- temp fix: or GLVIND?
find_package(OpenGL 4.6.0 REQUIRED)

message(STATUS "OpenGL found at: ${OPENGL_INCLUDE_DIR}")
message(STATUS "OpenGL libraries: ${OPENGL_LIBRARIES}")

execute_process(COMMAND glxinfo -B OUTPUT_VARIABLE GLXINFO)
string(REGEX MATCH "OpenGL version string: ([0-9.]+)" GLXINFO ${GLXINFO})
message(STATUS "OpenGL version: ${CMAKE_MATCH_1}")



# # TODO: Add OpenCV
# find_package(OpenCV 2.5.5 REQUIRED)



target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})


####################################################
## Add preprocessor definitions
####################################################

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

####################################################
## LOCAL 3rd libs (sub-modules)
####################################################

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





# CPack
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
