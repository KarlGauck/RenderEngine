#pragma once
#include <vector>

#include <glad/glad.h>

class ShaderStorageBuffer {
    unsigned int buffer;
public:
    void create_buffer();
    template <typename T>
    void set_data(std::vector<T> data) {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer);
        glNamedBufferStorage(buffer, sizeof(T)*data.size(), data.data(), GL_DYNAMIC_STORAGE_BIT);
    };
    void bind(unsigned int binding);
};
