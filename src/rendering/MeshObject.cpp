#include <glad/glad.h>
#include <iostream>

#include "rendering/MeshObject.h"

MeshObject::MeshObject(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices):
    vertices(vertices), indices(indices) {
}

void MeshObject::set_vertices(std::vector<Vertex>& vertices)
{
    this->vertices = vertices;
}

void MeshObject::set_indices(std::vector<unsigned int>& indices)
{
    this->indices = indices;
}

void MeshObject::enable()
{
    glBindVertexArray(vertex_array_object);
}

void MeshObject::disable()
{
    glBindVertexArray(0);
}



void MeshObject::create_buffers()
{
    glGenVertexArrays(1, &vertex_array_object);
    this->enable();

    glGenBuffers(1, &vertex_buffer_object);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &element_buffer_object);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    unsigned int stride = 8;
    glVertexAttribPointer(0, 3, GL_FLOAT, false, stride*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, false, stride*sizeof(float), (void*)3);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, false, stride*sizeof(float), (void*)6);
    glEnableVertexAttribArray(2);

    disable();
}

void MeshObject::delete_buffers() const {
    glDeleteVertexArrays(1, &vertex_array_object);
    glDeleteBuffers(1, &vertex_buffer_object);
    glDeleteBuffers(1, &element_buffer_object);
}
