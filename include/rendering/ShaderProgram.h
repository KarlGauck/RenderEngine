#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>
#include "MeshObject.h"
#include "InstanceManager.h"

#endif //SHADERPROGRAM_H

class ShaderProgram
{
    std::string vertexPath;
    std::string fragmentPath;

    unsigned int program;

    void print_shader_program_log(unsigned int shaderProgram);
    void print_shader_log(unsigned int shader);

    unsigned int get_location(std::string name);

public:
    ShaderProgram(const std::string& vertex_path, const std::string& fragment_path);

    void create_gl_program();

    void render(MeshObject& mesh_object);
    void render_instanced(InstanceManager &instance_manager);

    void set_uniform_1f(std::string name, float arg);
    void set_uniform_2f(std::string name, glm::vec2 arg);
    void set_uniform_3f(std::string name, glm::vec3 arg);
    void set_uniform_4f(std::string name, glm::vec4 arg);
};