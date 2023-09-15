download_external_project(imgui
    URL "https://github.com/ibois-epfl/imgui2.git"
    TAG "features/cmake_modif_for_ac_intergration_guli"
    BACKEND GIT)
download_external_project(stb
    URL "https://github.com/ibois-epfl/stb.git"
    BACKEND GIT)

#add_subdirectory(stb)
add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/deps)

add_subdirectory(deps/imgui)
#list(APPEND AC_INSTALL_TARGETS imgui::imgui)
