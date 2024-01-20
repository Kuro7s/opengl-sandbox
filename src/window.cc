#include "window.h"

#include "util.h"

#include <stdint.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

static void glfw_error_callback(int error, const char* description)
{
    util::die("GLFW Error (%d) %s", error, description);
}

Window::Window(const WindowInfo& info)
    : m_window_info(info)
    , m_native_window(nullptr)
{
    static int window_count = 0;
    if (window_count != 0)
    {
        util::die("Only one window is allowed, for now...");
    }

    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
    {
        util::die("Failed to initialize GLFW!");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    window_count++;
}

void Window::create()
{
    m_native_window = glfwCreateWindow(
        m_window_info.size.x, m_window_info.size.y, m_window_info.title.data(), NULL, NULL);

    glfwMakeContextCurrent((GLFWwindow*)m_native_window);

    uint32_t glew_init_result = glewInit();
    if (glew_init_result != GLEW_OK)
    {
        util::die(
            "Failed to initialize GLEW. %s (%d).",
            glew_init_result,
            glewGetErrorString(glew_init_result)
        );
    }

    glfwSwapInterval(m_window_info.vsync_enabled);
}

Window::~Window()
{
    if (m_native_window) {
        glfwDestroyWindow((GLFWwindow*)m_native_window);
        m_native_window = nullptr;
    }

    glfwTerminate();
}

void Window::swap_buffers()
{
    glfwSwapBuffers((GLFWwindow*)m_native_window);
}

void Window::poll_events()
{
    glfwPollEvents();
}

bool Window::should_close() const
{
    return glfwWindowShouldClose((GLFWwindow*)m_native_window) != GLFW_FALSE;
}

void Window::close()
{
    glfwSetWindowShouldClose((GLFWwindow*)m_native_window, GLFW_TRUE);
}

void Window::update_info() const
{
    auto glfw_window = (GLFWwindow*)m_native_window;
    auto& info = m_window_info;

    glfwSetWindowTitle(glfw_window, info.title.data());

    // TODO: Make this happen.
    // glfwSetWindowSize(glfw_window, info.size.x, info.size.y);
    // glfwSetWindowPos(glfw_window, info.position.x, info.position.y);

    if (info.visible)
    {
        glfwShowWindow(glfw_window);
    }
    else
    {
        glfwHideWindow(glfw_window);
    }

    glfwSwapInterval(info.vsync_enabled);
}
