#include <cmath>
#include <fileutils/FileInput.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
# include <stb_image.h>

#include <iostream>

#include "rendering/InstanceManager.h"
#include "rendering/ShaderProgram.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

unsigned int shaderProgram;
unsigned int vao;

MeshObject *mesh_object = nullptr;
InstanceManager *instance_manager = nullptr;
ShaderProgram *shader_program = nullptr;
Camera camera;

void initGLFW() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
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


    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    return 0;
}

void initGLStructures() {
    glEnable(GL_DEPTH_TEST);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    std::vector<Vertex> vertices {
        Vertex(
            0.5f,  0.5f, 0.5f, 1.f, 0.f, 0.f, 1.f, 1.f
        ),
        Vertex(
            0.5f, -0.5f, 0.5f, 1.f, 0.f, 0.f, 1.f, 0.f
        ),
        Vertex(
            -0.5f, -0.5f, 0.5f, 1.f, 0.f, 0.f, 0.f, 0.f
        ),
        Vertex(
            -0.5f,  0.5f, 0.5f,  1.f, 0.f, 0.f, 0.f, 1.f
        ),
        Vertex(
            0.5f,  0.5f, -0.5f, 1.f, 0.f, 0.f, 1.f, 1.f
        ),
        Vertex(
            0.5f, -0.5f, -0.5f, 1.f, 0.f, 0.f, 1.f, 0.f
        ),
        Vertex(
            -0.5f, -0.5f, -0.5f, 1.f, 0.f, 0.f, 0.f, 0.f
        ),
        Vertex(
            -0.5f,  0.5f, -0.5f,  1.f, 0.f, 0.f, 0.f, 1.f
        ),
    };

    std::vector<unsigned int> indices {
        0, 1, 3,
        1, 2, 3,
        0, 1, 4,
        1, 5, 4,
        1, 5, 2,
        2, 5, 6,
        0, 4, 3,
        3, 4, 7,
        2, 7, 6,
        2, 3, 7,
        4, 5, 6,
        4, 6, 7
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
    mesh_object->set_texture(1, "t2",void_texture);

    int size = 100;
    float scale = 0.1;
    float spacing = 1;
    float offset = spacing + scale * 2;
    std::vector<Instance> instances(size*size*size);
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            for (int z = 0; z < size; z++) {
               instances.push_back (
                    Instance {
                       glm::translate(glm::scale(glm::mat4(1.f), glm::vec3(scale)), glm::vec3(x*offset, y*offset, z*offset))
                    }
               );
            }
        }
    }

    instance_manager = new InstanceManager(*mesh_object);
    instance_manager->create_buffer();
    instance_manager->set_instances(instances);

    float timeValue = glfwGetTime();
    float greenValue = (::sin(timeValue) / 2.0f) + 0.5f;
    shader_program->set_uniform_4f("ourColor", glm::vec4(greenValue));

    camera = {
        glm::vec3(3, 3, 3),
        glm::radians(-45.f),
        glm::radians(-45.f),
        glm::radians(45.f),
        0.1f,
        1000.f,
        1
    };
}

void loop(GLFWwindow* window) {
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        float timeValue = glfwGetTime()*3;
        float greenValue = (::sin(timeValue) / 2.0f) + 0.5f;

        glm::mat4 view = camera.get_view_matrix();
        glm::mat4 rot = glm::rotate(glm::mat4(1.f), greenValue, glm::vec3(0, 1, 0));
        shader_program->set_uniform_1f("scalar", greenValue);
        shader_program->render_instanced(*instance_manager, camera);

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

    float vel = 0.02f;
    float angular_vel = 0.02f;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.position += vel*camera.get_view_direction();
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.position -= vel*camera.get_view_direction();
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.position -= vel*camera.get_horizontal_axis();
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.position += vel*camera.get_horizontal_axis();
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        camera.yaw -= angular_vel;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        camera.yaw += angular_vel;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        camera.pitch += angular_vel;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        camera.pitch -= angular_vel;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.position.y += vel;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.position.y -= vel;
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        camera.field_of_view = glm::radians(20.f);
    else
        camera.field_of_view = glm::radians(45.f);

//    glm::vec3 pos = glm::vec3(sin(angle)*radius, camera.position.y, cos(angle)*radius);
//    camera.position = pos;
//    camera.yaw = -angle;
//    std::cout << camera.position.x << std::endl;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    camera.aspect_ratio = (float)width/height;
}