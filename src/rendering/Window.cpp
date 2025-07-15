#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "rendering/Window.h"

void initGLFW() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);

    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
}

int initGlad() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    return 0;
}

void debug_message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                            const GLchar * message, const void * user_param) {
    std::cout << "OpenGL Error: " << message << std::endl;
}

int initGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(debug_message_callback, 0);
    return 0;
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void Window::init_graphics() {
    initGLFW();
}

void Window::create_window() {
    window_handle = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if (window_handle == NULL)
    {
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window_handle);
    glfwSetFramebufferSizeCallback(window_handle, framebuffer_size_callback);

    initGlad();
    initGL();

    std::cout << window_handle << std::endl;
    std::cout << std::endl;
}

void Window::start_loop() {
    while (!glfwWindowShouldClose(window_handle)) {
        glfwPollEvents();
        process_input(window_handle);
        glClearColor(clearcolor[0], clearcolor[1], clearcolor[2], clearcolor[3]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        loop();
        glfwSwapBuffers(window_handle);
    }
    on_close();
}



