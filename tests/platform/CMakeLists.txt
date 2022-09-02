add_executable(platform_test tester.cpp)

# <--- add here all the linking --->

add_test(NAME "PlatformTest" COMMAND "platform_test" arg1 WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
