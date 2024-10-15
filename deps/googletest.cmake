download_external_project(googletest
    URL "https://github.com/google/googletest.git"
    TAG "v1.15.2"
    BACKEND GIT)

add_subdirectory(deps/googletest)