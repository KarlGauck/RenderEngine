//
// Created by karlg on 02.05.25.
//

#include <iostream>
#include "rendering/InstanceManager.h"

InstanceManager::InstanceManager(MeshObject &mesh_object): mesh_object(mesh_object) {};

void InstanceManager::create_buffer() {
    std::cout << "buffer created" << std::endl;
    glGenBuffers(1, &shader_storage_buffer);
}

void InstanceManager::set_instances(std::vector<Instance> &instances) {
    instance_count = instances.size();

    mesh_object.enable();
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shader_storage_buffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(Instance)*instances.size(), instances.data(), GL_DYNAMIC_DRAW);
    glNamedBufferStorage(shader_storage_buffer, sizeof(Instance)*instances.size(), instances.data(), GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT);
    std::cout << "data uploaded" << std::endl;
    bind();
    mesh_object.disable();
}

void InstanceManager::bind() {
    std::cout << "buffer bound" << std::endl;
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, shader_storage_buffer);
}

void InstanceManager::unbind() {
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, 0);
}


unsigned int InstanceManager::get_instance_count() {
    return instance_count;
}


MeshObject& InstanceManager::get_mesh_object() {
    return mesh_object;
}



