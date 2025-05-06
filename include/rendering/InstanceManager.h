//
// Created by karlg on 02.05.25.
//

#ifndef INSTANCEMANAGER_H
#define INSTANCEMANAGER_H

#include <glm/glm.hpp>
#include "MeshObject.h"

struct Instance {
    glm::mat4 x;
};

class InstanceManager {
    unsigned int shader_storage_buffer = 0;
    unsigned int instance_count = 0;

    MeshObject mesh_object;

public:
    explicit InstanceManager(MeshObject &mesh_object);

    void set_instances(std::vector<Instance> &instances);

    void create_buffer();
    void delete_buffer();

    void bind();
    void unbind();

    unsigned int get_instance_count();
    MeshObject& get_mesh_object();
};

#endif //INSTANCEMANAGER_H
