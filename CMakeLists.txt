cmake_minimum_required(VERSION 3.26.0)

project(gfx-sandbox)

add_subdirectory(lib/glfw)

file(
    GLOB VENDORS_SOURCES
    lib/glew/src/glew.c
    lib/imgui/backends/imgui_impl_glfw.cpp
    lib/imgui/backends/imgui_impl_opengl3.cpp
    lib/imgui/imgui*.cpp
)

add_executable(gl-sandbox ${VENDORS_SOURCES} src/main.cpp)

target_link_libraries(gl-sandbox glfw opengl32)

target_compile_definitions(gl-sandbox PUBLIC GLEW_STATIC)

target_include_directories(gl-sandbox PUBLIC
    lib/glew/include
    lib/glfw/include
    lib/imgui/
    lib/imgui/backends
    lib/)
