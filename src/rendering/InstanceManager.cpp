//
// Created by karlg on 02.05.25.
//

#include "rendering/InstanceManager.h"

InstanceManager::InstanceManager(MeshObject &mesh_object): mesh_object(mesh_object) {};

void InstanceManager::create_buffer() {
    glGenBuffers(1, &instance_buffer_object);
}

void InstanceManager::set_instances(std::vector<Instance> instances) const {
    glBindBuffer(GL_ARRAY_BUFFER, instance_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Instance)*instances.size(), instances.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


