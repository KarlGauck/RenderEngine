#include "rendering/ShaderProgram.h"
#include "fileutils/FileInput.h"


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <cmath>
#include <stb_image.h>

ShaderProgram::ShaderProgram(const std::string& vertex_path, const std::string& fragment_path) {
    this->vertexPath = vertex_path;
    this->fragmentPath = fragment_path;
}

void ShaderProgram::create_gl_program() {

    const std::string vertexCode = FileInput::read_file(vertexPath);
    std::cout << vertexPath << std::endl;
    std::cout << "vertex: " << vertexCode << std::endl;
    const char* vertexSource = vertexCode.c_str();
    const string fragmentCode = FileInput::read_file(fragmentPath);
    std::cout << "fragment: " << fragmentCode << std::endl;
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

void ShaderProgram::render(MeshObject& mesh_object) {
float timeValue = glfwGetTime();
        float greenValue = (::sin(timeValue) / 2.0f) + 0.5f;

        glUseProgram(program);
        mesh_object.load_textures(program);

        int vertexColorLocation = glGetUniformLocation(program, "ourColor");
        glUniform4f(vertexColorLocation, greenValue, greenValue, greenValue, greenValue);

        //int tex1loc = glGetUniformLocation(program, "t1");
        //int tex2loc = glGetUniformLocation(program, "t2");

        //glUniform1i(tex1loc, 0);
        //glUniform1i(tex2loc, 1);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        mesh_object.enable();
        glDrawElements(GL_TRIANGLES, 6,  GL_UNSIGNED_INT, 0);
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