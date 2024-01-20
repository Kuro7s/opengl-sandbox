cmake_minimum_required(VERSION 3.28.1)

project(learning-opengl VERSION 0.1.0)

add_subdirectory(lib/glfw)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

file(
    GLOB VENDORS_SOURCES
    lib/glew/src/glew.c
    lib/imgui/backends/imgui_impl_glfw.cpp
    lib/imgui/backends/imgui_impl_opengl3.cpp
    lib/imgui/imgui*.cpp)

add_executable(gl-sandbox ${VENDORS_SOURCES} src/main.cc)

target_link_libraries(gl-sandbox glfw opengl32)

target_compile_definitions(gl-sandbox PUBLIC GLEW_STATIC)

target_include_directories(gl-sandbox PUBLIC
    third_party/glew/include
    third_party/glfw/include
    third_party/imgui/
    third_party/imgui/backends
    third_party/)

