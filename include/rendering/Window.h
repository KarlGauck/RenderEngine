#pragma once

#include "GLFW/glfw3.h"

class Window {
    unsigned int window_handle;
    int width;
    int height;
    int (*loop)();
    int (*on_close)();
    static int (*on_resize)(int width, int height);

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

public:
    void init_graphics();
    void create_window();
    void start_loop();
    void set_loop(int (*loop)());
    void set_on_close(int (*on_close)());
};