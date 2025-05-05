//
// Created by karlg on 02.05.25.
//

#include <iostream>
#include "rendering/InstanceManager.h"

InstanceManager::InstanceManager(MeshObject &mesh_object): mesh_object(mesh_object) {};

void InstanceManager::create_buffer() {
    glGenBuffers(1, &instance_buffer_object);
}

void InstanceManager::set_instances(std::vector<Instance> instances) {
    instance_count = instances.size();
    unsigned int attrib_size = sizeof(Instance)/sizeof(float);
    unsigned int stride = sizeof(Instance);

    mesh_object.enable();
    glBindBuffer(GL_ARRAY_BUFFER, instance_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Instance)*instances.size(), instances.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, attrib_size, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glVertexAttribDivisor(3, 1);
    std::cout << sizeof(float) << std::endl;
    std::cout << instances.size() << std::endl;
    mesh_object.disable();
}

unsigned int InstanceManager::get_instance_count() {
    return instance_count;
}


MeshObject& InstanceManager::get_mesh_object() {
    return mesh_object;
}



