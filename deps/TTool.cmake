if(AC_SYNC_GIT_SUBMODULES)
  download_submodule_project(TTool)
endif()

set(TTOOL_BUILD_TTOOL_EXE OFF)
add_subdirectory(deps/TTool)

find_package(Torch)
