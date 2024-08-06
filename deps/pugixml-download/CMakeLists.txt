cmake_minimum_required(VERSION 3.1)
project(pugixml-download NONE)
include(ExternalProject)
ExternalProject_Add(pugixml
    SOURCE_DIR /home/ibois/augmented-carpentry/deps/pugixml
    BINARY_DIR /home/ibois/augmented-carpentry/deps/pugixml-download
    GIT_REPOSITORY "https://github.com/zeux/pugixml.git"
    
    CONFIGURE_COMMAND ""
    BUILD_COMMAND     ""
    INSTALL_COMMAND   ""
    TEST_COMMAND      ""
    
LOG_BUILD 1)