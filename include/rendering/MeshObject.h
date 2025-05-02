#ifndef MESHOBJECT_H
#define MESHOBJECT_H

#include <memory>
#include <vector>
#include "Texture.h"

#endif //MESHOBJECT_H


struct Vertex
{
    float x, y, z;
    float r, g, b;
    float tex1, tex2;
};

class MeshObject
{
    unsigned int vertex_array_object = 0;
    unsigned int vertex_buffer_object = 0;
    unsigned int element_buffer_object = 0;

    std::vector<Vertex>& vertices;
    std::vector<unsigned int>& indices;

    std::string texture_names[16];
    Texture textures[16];
    bool used_textures[16];

public:
    MeshObject(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);

    void set_vertices(std::vector<Vertex> &vertices);
    void set_indices(std::vector<unsigned int> &indices);
    void set_texture(unsigned int texture_id, const std::string &texture_name, Texture& texture);
    void remove_texture(unsigned int texture_id);

    void create_buffers();
    void delete_buffers() const;
    void load_textures(unsigned int program_id);

    void enable();
    void disable();
};