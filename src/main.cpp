#include <cmath>
#include <fileutils/FileInput.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>

#include "fileutils/MeshParser.h"
#include "rendering/InstanceManager.h"
#include "rendering/ShaderProgram.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "rendering/ShaderStorageBuffer.h"
#include "stdextentions/StringUtils.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

unsigned int shaderProgram;

MeshObject cat_mesh = MeshParser::parse_wavefront_obj(FileInput::read_file("../assets/meshes/blender_monkey.obj"));
MeshObject light_mesh = MeshParser::parse_wavefront_obj(FileInput::read_file("../assets/meshes/test.obj"));
InstanceManager *cat_instancer = nullptr;
InstanceManager *light_instancer = nullptr;
ShaderStorageBuffer light_buffer;
ShaderProgram *scene_program = nullptr;
ShaderProgram *light_program = nullptr;
Camera camera;

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

void debug_message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                            const GLchar * message, const void * user_param) {
    std::cout << "OpenGL Error: " << message << std::endl;
}

void initGLStructures() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(debug_message_callback, 0);

    cat_mesh.create_buffers();
    light_mesh.create_buffers();

    scene_program = new ShaderProgram("../src/shaders/phong_vertex.glsl",
        "../src/shaders/phong_fragment.glsl");
    scene_program->create_gl_program();

    light_program = new ShaderProgram("../src/shaders/lightsource_vertex.glsl",
        "../src/shaders/lightsource_fragment.glsl");
    light_program->create_gl_program();

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

    cat_mesh.set_texture(0, "t1", debris_texture);
    cat_mesh.set_texture(1, "t2",void_texture);

    light_mesh.set_texture(0, "t1", debris_texture);
    light_mesh.set_texture(1, "t2",void_texture);

    std::vector<Instance> light_instances {
         Instance {
            glm::translate(glm::scale(glm::mat4(1.f), glm::vec3(0.05f)), glm::vec3(0.f))
         },
         Instance {
            glm::translate(glm::scale(glm::mat4(1.f), glm::vec3(0.05f)), glm::vec3(0.f))
         }
    };

    std::vector cat_instances = {
        Instance {
            glm::translate(glm::scale(glm::mat4(1.f), glm::vec3(1.f)), glm::vec3(0.f))
        },
        /*
        Instance {
            glm::translate(glm::scale(glm::mat4(1.f), glm::vec3(1.f)), glm::vec3(1.f))
        },
        Instance {
            glm::translate(glm::scale(glm::mat4(1.f), glm::vec3(1.f)), glm::vec3(2.f))
        }
        */
    };

    struct LightData {
        glm::vec4 pos;
        glm::vec4 color;
    };

    std::vector<LightData> lights {
     {
            glm::vec4(2.f, 0.f, 0.f, 0.f),
            glm::vec4(1.f, 1.f, 1.f, 1.f)
        },
     {
            glm::vec4(0.f, 2.f, 0.f, 0.f),
            glm::vec4(1.f, 0.2f, 0.2f, 1.f)
        }
    };

    light_buffer.create_buffer();
    light_buffer.set_data(lights);

    light_instancer = new InstanceManager(light_mesh);
    light_instancer->create_buffer();
    light_instancer->set_instances(light_instances);

    cat_instancer = new InstanceManager(cat_mesh);
    cat_instancer->create_buffer();
    cat_instancer->set_instances(cat_instances);

    float timeValue = glfwGetTime();
    float greenValue = (::sin(timeValue) / 2.0f) + 0.5f;
    scene_program->set_uniform_4f("ourColor", glm::vec4(greenValue));

    camera = {
        glm::vec3(0, 0, 0),
        glm::radians(45.f),
        glm::radians(-225.f),
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
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        light_buffer.bind(1);
        light_program->render_instanced(*light_instancer, camera);
        scene_program->render_instanced(*cat_instancer, camera);

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
        camera.position += vel*camera.get_horizontal_view_direction();
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.position -= vel*camera.get_horizontal_view_direction();
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

