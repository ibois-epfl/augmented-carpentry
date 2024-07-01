cmake_minimum_required(VERSION 3.1)
project(eventpp-download NONE)
include(ExternalProject)
ExternalProject_Add(eventpp
    SOURCE_DIR /home/ibois/augmented-carpentry/deps/eventpp
    BINARY_DIR /home/ibois/augmented-carpentry/deps/eventpp-download
    GIT_REPOSITORY "https://www.github.com/ibois-epfl/eventpp.git"
    
    CONFIGURE_COMMAND ""
    BUILD_COMMAND     ""
    INSTALL_COMMAND   ""
    TEST_COMMAND      ""
    
LOG_BUILD 1)