include(CTest)
include(external_tools)
enable_testing()
add_external_package(googletest)

# ------------------------------------------------------------------------------
# c++
# ------------------------------------------------------------------------------
# add new test suites .cc here
set(AC_TESTSUITE ac_tests)
add_executable(${AC_TESTSUITE}
    tests/smoke_tests/dry_run_test.cc
    tests/allCppTests.cc
    )

target_include_directories(${AC_TESTSUITE}
PUBLIC
    ${OpenCV_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/src
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
                COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --verbose
                COMMENT "Running all tests"
            )