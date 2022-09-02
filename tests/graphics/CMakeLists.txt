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


# # print the macro definition CMAKE SOURCE
# set(CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR})
# set(CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
# set(CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
# set(CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR})
# message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
# message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
# message(STATUS "CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
# message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")

# add_subdirectory(${CMAKE_SOURCE_DIR}/deps/imgui graphics_test)
# target_include_directories(graphics_test PUBLIC ${CMAKE_SOURCE_DIR}/deps/imgui)
# target_link_libraries(graphics_test ${CMAKE_SOURCE_DIR}/deps/imgui)

add_test(NAME "GraphicsTest" COMMAND "graphics_test" WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
