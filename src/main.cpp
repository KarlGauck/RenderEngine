#include <cmath>
#include <fileutils/FileInput.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
# include <stb_image.h>

#include <iostream>

#include "rendering/ShaderProgram.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

unsigned int shaderProgram;
unsigned int vao;

MeshObject *mesh_object = nullptr;
ShaderProgram *shader_program = nullptr;

void initGLFW() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
}

GLFWwindow* initWindow() {
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return window;
}

int initGlad() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    return 0;
}





void initGLStructures() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    std::vector<Vertex> vertices {
        Vertex(
            0.5f,  0.5f, 0.0f, 1.f, 0.f, 0.f, 1.f, 1.f
        ),
        Vertex(
            0.5f, -0.5f, 0.0f, 1.f, 0.f, 0.f, 1.f, 0.f
        ),
        Vertex(
            -0.5f, -0.5f, 0.0f, 1.f, 0.f, 0.f, 0.f, 0.f
        ),
        Vertex(
            -0.5f,  0.5f, 0.0f,  1.f, 0.f, 0.f, 0.f, 1.f
        ),
    };

    std::vector<unsigned int> indices {
        0, 1, 3,
        1, 2, 3
    };

    mesh_object = new MeshObject(vertices, indices);
    mesh_object->create_buffers();

    shader_program = new ShaderProgram("../src/shaders/vertex.glsl",
        "../src/shaders/fragment.glsl");
    shader_program->create_gl_program();

    TextureBehaviour texture_behaviour {
        REPEAT,
        REPEAT,
        REPEAT,
        LINEAR,
        LINEAR,
        LINEAR,
        {1.f, 1.f, 1.f, 1.f}
    };

    Texture void_texture{};
    void_texture.load_texture(FileInput::read_texture("../assets/textures/void.jpg"));
    void_texture.set_texture_behaviour(texture_behaviour);

    Texture debris_texture{};
    debris_texture.load_texture(FileInput::read_texture("../assets/textures/ancient_debris.png"));
    debris_texture.set_texture_behaviour(texture_behaviour);

    mesh_object->set_texture(0, "t1", debris_texture);
    mesh_object->set_texture(1, "t2", void_texture);
}

void loop(GLFWwindow* window) {
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        shader_program->render(*mesh_object);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

int main()
{
    initGLFW();
    GLFWwindow* window = initWindow();
    if (!window)
        return -1;

    if (initGlad() == -1)
        return -1;


    initGLStructures();

    loop(window);

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}