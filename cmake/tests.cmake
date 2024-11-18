include(CTest)
include(external_tools)
enable_testing()
add_external_package(googletest)

# ------------------------------------------------------------------------------
# c++
# ------------------------------------------------------------------------------
# add new test suites .cc here
set(AC_TESTSUITE ac_tests)

file(GLOB_RECURSE AIAC_SRC "src/*.cpp")
list(REMOVE_ITEM AIAC_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/ACApp.cpp)

file(GLOB_RECURSE AIAC_TEST_SRC "tests/*.cc")

add_executable(${AC_TESTSUITE}
    ${AIAC_SRC}
    ${AIAC_TEST_SRC}
    )

# pre-compile variables
target_compile_definitions(${AC_TESTSUITE}
        PUBLIC AC_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
        PUBLIC AC_VERSION_MINOR=${PROJECT_VERSION_MINOR}
        PUBLIC AC_VERSION_PATCH=${PROJECT_VERSION_PATCH}
        )

if(HEADLESS_TEST)
    target_compile_definitions(${AC_TESTSUITE} PRIVATE HEADLESS_TEST=true)
endif()
if(DEPLOY_ON_TOUCH)
    target_compile_definitions(${AC_TESTSUITE} PRIVATE AIAC_DEPLOY_ON_TOUCH=true)
endif()
if(ENABLE_ASSERT)
    target_compile_definitions(${AC_TESTSUITE} PRIVATE AIAC_ENABLE_ASSERTS=true)
endif()
if(SILENT_LOGGING)
    target_compile_definitions(${AC_TESTSUITE} PRIVATE SILENT_LOGGING=true)
endif()
if(ENABLE_DEV_UI)
    target_compile_definitions(${AC_TESTSUITE} PRIVATE ENABLE_DEV_UI=true)
endif()

target_include_directories(${AC_TESTSUITE}
    PUBLIC ${OpenCV_INCLUDE_DIRS}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_precompile_headers(${AC_TESTSUITE} PRIVATE src/aiacpch.h)

target_link_libraries(${AC_TESTSUITE} 
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
    gtest gtest_main
    )

add_test(NAME ${AC_TESTSUITE} COMMAND ${AC_TESTSUITE})


# ------------------------------------------------------------------------------
# Run all tests
# ------------------------------------------------------------------------------
add_custom_command(
                TARGET ${AC_TESTSUITE} POST_BUILD
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --verbose --gtest_color=yes
                COMMENT "Running all tests"
            )