add_executable(graphics_test tester.cpp)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)


target_include_directories(graphics_test PUBLIC ${OPENGL_INCLUDE_DIRS})

target_link_libraries(graphics_test
    ${OPENGL_LIBRARIES}
    ${CMAKE_DL_LIBS}
    glfw
    GLU
    )

add_test(NAME "GraphicsTest" COMMAND "graphics_test" WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
