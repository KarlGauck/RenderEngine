//
// Created by karlg on 02.05.25.
//

#ifndef INSTANCEMANAGER_H
#define INSTANCEMANAGER_H

#include <glm/vec3.hpp>
#include "MeshObject.h"

struct Instance {
    glm::vec3 position;
    glm::vec3 scale;
};

class InstanceManager {
    unsigned int instance_buffer_object{};

    MeshObject mesh_object;

public:
    explicit InstanceManager(MeshObject &mesh_object);

    void set_instances(std::vector<Instance> instances) const;

    void create_buffer();
    void delete_buffer();
};

#endif //INSTANCEMANAGER_H
