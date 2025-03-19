
#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>
#include "MeshObject.h"

#endif //SHADERPROGRAM_H

class ShaderProgram
{
public:
    void set_vertex_shader(std::string shader_path);
    void set_fragment_shader(std::string shader_path);

    void set_mesh(MeshObject& mesh_object);

    void render();
};