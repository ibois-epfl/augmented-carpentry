if(AC_SYNC_GIT_SUBMODULES)
  download_submodule_project(TSlam)
endif()

set(TSLAM_QUIET ON)
add_subdirectory(deps/TSlam)
