#include "rendering/ShaderProgram.h"
#include "fileutils/FileInput.h"


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <cmath>
#include <stb_image.h>
#include <glm/gtc/type_ptr.hpp>

ShaderProgram::ShaderProgram(const std::string& vertex_path, const std::string& fragment_path) {
    this->vertexPath = vertex_path;
    this->fragmentPath = fragment_path;
}

void ShaderProgram::create_gl_program() {
    const std::string vertexCode = FileInput::read_file(vertexPath);
    const char* vertexSource = vertexCode.c_str();
    const string fragmentCode = FileInput::read_file(fragmentPath);
    const char* fragmentSource = fragmentCode.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);

    glCompileShader(vertexShader);
    print_shader_log(vertexShader);
    glCompileShader(fragmentShader);
    print_shader_log(fragmentShader);

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    print_shader_program_log(program);
}

void ShaderProgram::render(MeshObject& mesh_object, Camera &camera) {
    glUseProgram(program);
    mesh_object.load_textures(program);
    mesh_object.enable();
    glDrawElements(GL_TRIANGLES, mesh_object.get_index_count(),  GL_UNSIGNED_INT, 0);
}

void ShaderProgram::render_instanced(InstanceManager& instance_manager, Camera &camera) {
    glUseProgram(program);
    instance_manager.get_mesh_object().load_textures(program);
    instance_manager.get_mesh_object().enable();

    set_uniform_mat4f("view_matrix", camera.get_view_matrix());
    set_uniform_mat4f("projection_matrix", camera.get_projection_matrix());

    glDrawElementsInstanced(GL_TRIANGLES, instance_manager.get_mesh_object().get_index_count(),  GL_UNSIGNED_INT, 0, instance_manager.get_instance_count());
}

void ShaderProgram::print_shader_program_log(unsigned int shaderProgram) {
    int  success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADERPROGRAM::" << shaderProgram << "::LINKING_FAILED\n" << infoLog << std::endl;
    }
}

void ShaderProgram::print_shader_log(unsigned int shader) {
    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::" << shader << "::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

//UNIFORMS

unsigned int ShaderProgram::get_location(std::string name) {
    return glGetUniformLocation(program, name.c_str());
}

void ShaderProgram::set_uniform_1f(std::string name, float arg) {
    glUniform1f(get_location(name), arg);
}

void ShaderProgram::set_uniform_2f(std::string name, glm::vec2 arg) {
    glUniform2f(get_location(name), arg.x, arg.y);
}

void ShaderProgram::set_uniform_3f(std::string name, glm::vec3 arg) {
    glUniform3f(get_location(name), arg.x, arg.y, arg.z);
}

void ShaderProgram::set_uniform_4f(std::string name, glm::vec4 arg) {
    glUniform4f(get_location(name), arg.x, arg.y, arg.z, arg.w);
}

void ShaderProgram::set_uniform_mat4f(std::string name, glm::mat4 mat) {
    glUniformMatrix4fv(get_location(name), 1, GL_FALSE, glm::value_ptr(mat));
}
