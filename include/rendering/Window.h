#pragma once

#include "GLFW/glfw3.h"

class Window {
    GLFWwindow *window_handle;

    int (*on_close)();
    float clearcolor[4] = {0.f, 0.f, 0.f, 1.f};

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

public:
    void (*process_input)(GLFWwindow* window);
    void (*loop)();
    int width;
    int height;

    void init_graphics();
    void create_window();
    void set_clear_color();
    void start_loop();
    void set_loop(int (*loop)());
    void set_on_close(int (*on_close)());
};