#include "rendering/ShaderStorageBuffer.h"

#include <glad/glad.h>

void ShaderStorageBuffer::create_buffer() {
    glGenBuffers(1, &buffer);
}

void ShaderStorageBuffer::bind(unsigned int binding) {
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, buffer);
}
