#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>
#include "MeshObject.h"

#endif //SHADERPROGRAM_H

class ShaderProgram
{
    std::string vertexPath;
    std::string fragmentPath;

    unsigned int program;

    void print_shader_program_log(unsigned int shaderProgram);
    void print_shader_log(unsigned int shader);

public:
    ShaderProgram(const std::string& vertex_path, const std::string& fragment_path);

    void create_gl_program();

    void render(MeshObject& mesh_object);
};