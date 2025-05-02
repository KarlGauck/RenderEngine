#ifndef MESHOBJECT_H
#define MESHOBJECT_H

#include <memory>
#include <vector>
#include <tuple>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "Texture.h"
template<typename>
struct is_tuple : std::false_type {};

template<typename ... Types>
struct is_tuple<std::tuple<Types...>> : std::true_type {};

template <typename Vertex>
requires is_tuple<Vertex>::value
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

    void set_vertices(std::vector<Vertex>& vertices);
    void set_indices(std::vector<unsigned int>& indices);
    void set_texture(unsigned int texture_id, const std::string &texture_name, Texture& texture);
    void remove_texture(unsigned int texture_id);

    void create_buffers();
    void delete_buffers() const;
    void load_textures(unsigned int program_id);

    void enable();
    void disable();
};

#define DEFAULT_VERTEX_ATTRIBS glm::vec3, glm::vec3, glm::vec2
typedef MeshObject<std::tuple<DEFAULT_VERTEX_ATTRIBS>> DefaultMeshObject;

#include "MeshObject.inc"

#endif //MESHOBJECT_H
