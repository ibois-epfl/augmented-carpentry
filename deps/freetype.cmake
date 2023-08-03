download_external_project(freetype
    URL "https://gitlab.freedesktop.org/freetype/freetype"
    BACKEND GIT)

add_subdirectory(deps/freetype)
