#include <glad/glad.h>
#include <iostream>

#include "rendering/MeshObject.h"

template <typename Vertex>
MeshObject<Vertex>::MeshObject(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices):
    vertices(vertices), indices(indices) {
}

template <typename Vertex>
void MeshObject<Vertex>::set_vertices(std::vector<Vertex>& vertices)
{
    this->vertices = vertices;
}

void MeshObject<>::set_indices(std::vector<unsigned int>& indices)
{
    this->indices = indices;
}

void MeshObject<>::set_texture(unsigned int texture_id, const std::string &texture_name, Texture &texture) {
    texture_names[texture_id] = texture_name;
    textures[texture_id] = texture;
    used_textures[texture_id] = true;
}

void MeshObject<>::remove_texture(unsigned int texture_id) {
    used_textures[texture_id] = false;
}


void MeshObject<>::load_textures(unsigned int program_id) {
    for (int i = 0; i < 16; i++) {
        if (!used_textures[i])
            continue;
        textures[i].bind_at(i);
        glUniform1i(glGetUniformLocation(program_id, texture_names[i].c_str()), i);
    }
}

void MeshObject<>::enable()
{
    glBindVertexArray(vertex_array_object);
}

void MeshObject<>::disable()
{
    glBindVertexArray(0);
}

void MeshObject<>::create_buffers()
{
    glGenVertexArrays(1, &vertex_array_object);
    this->enable();

    glGenBuffers(1, &vertex_buffer_object);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex<>), vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &element_buffer_object);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    unsigned int stride = 8;
    glVertexAttribPointer(0, 3, GL_FLOAT, false, stride*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, false, stride*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, false, stride*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    disable();
}

void MeshObject<>::delete_buffers() const {
    glDeleteVertexArrays(1, &vertex_array_object);
    glDeleteBuffers(1, &vertex_buffer_object);
    glDeleteBuffers(1, &element_buffer_object);
}
