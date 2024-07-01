cmake_minimum_required(VERSION 3.1)
project(spdlog-download NONE)
include(ExternalProject)
ExternalProject_Add(spdlog
    SOURCE_DIR /home/ibois/augmented-carpentry/deps/spdlog
    BINARY_DIR /home/ibois/augmented-carpentry/deps/spdlog-download
    GIT_REPOSITORY "https://github.com/ibois-epfl/spdlog.git"
    GIT_TAG v1.x
    CONFIGURE_COMMAND ""
    BUILD_COMMAND     ""
    INSTALL_COMMAND   ""
    TEST_COMMAND      ""
    
LOG_BUILD 1)