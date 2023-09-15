#[[find_package(PkgConfig)

pkg_check_modules(imgui imgui IMPORTED_TARGET)]]

#[[
message("IMGUI ${imgui_INCLUDE_DIRS}")
message("IMGUI LIBS ${imgui_LIBRARIES}")
message("IMGUI LINK LIBS ${imgui_LINK_LIBRARIES}")

target_include_directories(PkgConfig::imgui INTERFACE ${imgui_INCLUDE_DIRS})


add_library(imgui IMPORTED GLOBAL)
set_target_properties(imgui PROPERTIES
    IMPORTED_LOCATION "${imgui_LIBRARIES}"
    INTERFACE_INCLUDE_DIRECTORIES "${imgui_INCLUDE_DIRS}")
]]

#[[
add_library(imgui::imgui ALIAS imgui)
]]


find_package(PkgConfig)

pkg_check_modules(imgui imgui IMPORTED_TARGET)

if (imgui_FOUND)
    add_library(imgui::imgui ALIAS PkgConfig::imgui)
endif ()