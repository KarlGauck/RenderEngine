#ifndef MESHOBJECT_H
#define MESHOBJECT_H
#include "Texture.h"

#endif //MESHOBJECT_H


struct Vertex
{
    float x, y, z;
};

class MeshObject
{
    unsigned int vertex_array_object = 0;
    unsigned int vertex_buffer_object = 0;
    unsigned int element_buffer_object = 0;

public:
    void set_vertices(float *vertices);
    void set_indices(unsigned int *indices);
    void set_texture_coords(float *texture_coords);
    void set_texture(unsigned int texture_id, Texture& texture);

    void createBuffers();
    void deleteBuffers();

    void enable();
    void disable();
};