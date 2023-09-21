find_package(PkgConfig)

pkg_check_modules(imgui imgui IMPORTED_TARGET)

if (imgui_FOUND)
    add_library(imgui::imgui ALIAS PkgConfig::imgui)
endif ()