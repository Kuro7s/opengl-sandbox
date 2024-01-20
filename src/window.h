#pragma once

#include <string_view>

#include <glm/glm.hpp>

struct WindowInfo
{
    std::string_view title;
    glm::vec2 size = { 1280, 720 };
    glm::vec2 position = { 100, 100 };
    bool visible = true;
    bool vsync_enabled = true;
};

/// Absolutely necessary window abstraction (yikes!).
class Window
{
public:
    Window(const WindowInfo& info);
    ~Window();

    void create();

    void close();
    bool should_close() const;

    void swap_buffers();
    void poll_events();

    WindowInfo info() const
    {
        return m_window_info;
    }

    void set_info(WindowInfo& info)
    {
        m_window_info = info;
    }

    void update_info() const;

    void* native_window() const
    {
        return m_native_window;
    }

private:
    WindowInfo m_window_info;
    void* m_native_window;
};
