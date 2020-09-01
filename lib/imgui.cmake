# Imgui

cmake_minimum_required(VERSION 3.1)
project(Imgui)

SET(IMGUI_SRC
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_widgets.cpp
    imgui/examples/imgui_impl_glfw.cpp
    imgui/examples/imgui_impl_opengl3.cpp
)

add_library(imgui ${IMGUI_SRC})
add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)
target_link_libraries(imgui glad glfw)
target_include_directories(imgui PUBLIC imgui imgui/examples)