enable_testing()


if (TEST_PLATFORM)
    add_subdirectory(platform)
endif()

if (TEST_GRAPHICS)
    add_subdirectory(graphics)
endif()