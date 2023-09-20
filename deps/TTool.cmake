download_submodule_project(TTool)

set(TTOOL_BUILD_TTOOL_EXE OFF)
add_subdirectory(deps/TTool)

find_package(Torch)

