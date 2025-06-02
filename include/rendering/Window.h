#pragma once

class Window {
    unsigned int window_handle;
    int (*loop)();
    int (*on_close)();

public:
    void init_graphics();
    void create_window();
    void start_loop();
    void set_loop(int (*loop)());
    void on_close(int (*on_close)());
    bool check_key(int key, int status);
};