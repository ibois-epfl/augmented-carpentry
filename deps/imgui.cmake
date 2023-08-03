download_external_project(imgui
    URL "https://github.com/ibois-epfl/imgui.git"
    TAG "release_1_88"
    BACKEND GIT)
download_external_project(stb
    URL "https://github.com/ibois-epfl/stb.git"
    BACKEND GIT)

add_subdirectory(stb)
add_subdirectory(imgui)
#list(APPEND AC_INSTALL_TARGETS imgui::imgui)
