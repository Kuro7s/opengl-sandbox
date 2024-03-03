#include "window.h"

#include "util.h"

#include <stdint.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

static void glfw_error_callback(int error, const char* description) {
    util::die("GLFW Error (%d) %s", error, description);
}



Window::Window(Window_Info info)
    : info(info),
      native_window_handle(nullptr) {

    static int WINDOW_COUNT = 0;

    if (WINDOW_COUNT != 0) util::die("Only one window is allowed, for now...");

    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) util::die("Failed to initialize GLFW!");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    WINDOW_COUNT++;
}

Window::~Window() {
    if (native_window_handle) {
        glfwDestroyWindow((GLFWwindow*)native_window_handle);
        native_window_handle = nullptr;
    }

    glfwTerminate();
}

void Window::create() {
    native_window_handle = glfwCreateWindow(info.size.x, info.size.y, info.title.data(), NULL, NULL);

    glfwMakeContextCurrent((GLFWwindow*)native_window_handle);

    uint32_t glew_init_result = glewInit();
    if (glew_init_result != GLEW_OK)
        util::die("Failed to initialize GLEW. %s (%d).", glew_init_result, glewGetErrorString(glew_init_result));

    glfwSwapInterval(info.vsync_enabled);
}


void Window::swap_buffers() {
    glfwSwapBuffers((GLFWwindow*)native_window_handle);
}

void Window::poll_events() {
    glfwPollEvents();
}

bool Window::should_close() const {
    return glfwWindowShouldClose(static_cast <GLFWwindow *>(native_window_handle)) != GLFW_FALSE;
}

void Window::close() {
    glfwSetWindowShouldClose(static_cast <GLFWwindow *>(native_window_handle), GLFW_TRUE);
}

void Window::update_info() const {
    auto glfw_window = static_cast <GLFWwindow *>(native_window_handle);

    glfwSetWindowTitle(glfw_window, info.title.data());

    // TODO: Make this happen.
    // glfwSetWindowSize(glfw_window, info.size.x, info.size.y);
    // glfwSetWindowPos(glfw_window, info.position.x, info.position.y);

    if (info.visible) {
        glfwShowWindow(glfw_window);
    } else {
        glfwHideWindow(glfw_window);
    }

    glfwSwapInterval(info.vsync_enabled);
}
