#ifndef WINDOW_H_
#define WINDOW_H_

#include <string_view>

#include <glm/glm.hpp>

struct Window_Info {
    std::string_view title;

    glm::vec2 size     = { 1280, 720 };
    glm::vec2 position = { 100, 100 };

    bool visible        = true;
    bool vsync_enabled  = true;
};

struct Window {
    Window(Window_Info info);
    ~Window();

    void create();

    void close();
    bool should_close() const;

    void swap_buffers();
    void poll_events();

    void update_info() const;

    Window_Info info;
    void* native_window_handle;
};

#endif // WINDOW_H_
