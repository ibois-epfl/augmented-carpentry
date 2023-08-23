download_external_project(spdlog
    URL "https://github.com/ibois-epfl/spdlog.git"
    TAG "v1.x"
    BACKEND GIT)

add_subdirectory(deps/spdlog)
