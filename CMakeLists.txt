cmake_minimum_required(VERSION 3.28.1)

project(learning-opengl VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(third_party/glfw)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

file(GLOB THIRD_PARTY_SRCS
    third_party/glew/src/glew.c
    third_party/imgui/backends/imgui_impl_glfw.cpp
    third_party/imgui/backends/imgui_impl_opengl3.cpp
    third_party/imgui/imgui*.cpp)

file(GLOB ALL_SRCS src/**.cpp)

add_executable(opengl-sandbox ${THIRD_PARTY_SRCS} ${ALL_SRCS})

target_link_libraries(opengl-sandbox glfw opengl32)
target_compile_definitions(opengl-sandbox PUBLIC GLEW_STATIC)
target_include_directories(opengl-sandbox PUBLIC
    third_party/glew/include
    third_party/glfw/include
    third_party/imgui/
    third_party/imgui/backends
    third_party/)

