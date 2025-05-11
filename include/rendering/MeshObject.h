#ifndef MESHOBJECT_H
#define MESHOBJECT_H

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "Texture.h"

struct Vertex
{
    float x, y, z;
    float nx, ny, nz;
    float r, g, b;
    float tex1, tex2;

    Vertex(float x, float y, float z, float nx, float ny, float nz, float r, float g, float b, float tex1, float tex2):
        x(x), y(y), z(z), nx(nx), ny(ny), nz(nz), r(r), g(g), b(b), tex1(tex1), tex2(tex2) {}

    Vertex(glm::vec3 position, glm::vec3 normal, glm::vec3 color, glm::vec2 texture_coordinate):
        x(position.x), y(position.y), z(position.z), nx(normal.x), ny(normal.y), nz(normal.z),
        r(color.r), g(color.g), b(color.b), tex1(texture_coordinate.x), tex2(texture_coordinate.y) {}
};

class MeshObject
{
    unsigned int vertex_array_object = 0;
    unsigned int vertex_buffer_object = 0;
    unsigned int element_buffer_object = 0;

    unsigned int index_count = 0;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

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

    unsigned int get_index_count();

    void print();
};

#endif //MESHOBJECT_H
