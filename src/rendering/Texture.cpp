//
// Created by karlg on 30.04.25.
//

#include "rendering/Texture.h"

void Texture::load_texture(TextureData texture_data) {
    glGenTextures(1, &handle);

    glBindTexture(GL_TEXTURE_2D, handle);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_data.width, texture_data.height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data.data.get());
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::set_texture_behaviour(const TextureBehaviour &behaviour) {
    glBindTexture(GL_TEXTURE_2D, handle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, behaviour.wrap_behaviour_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, behaviour.wrap_behaviour_t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, behaviour.wrap_behaviour_r);

    GLint min_filter = 0;
    if (behaviour.min_filter == InterpolationFilter::LINEAR) {
        if (behaviour.mipmap_filter == InterpolationFilter::LINEAR)
            min_filter = GL_LINEAR_MIPMAP_LINEAR;
        if (behaviour.mipmap_filter == InterpolationFilter::NEAREST)
            min_filter = GL_LINEAR_MIPMAP_NEAREST;
    }
    if (behaviour.min_filter == InterpolationFilter::NEAREST) {
        if (behaviour.mipmap_filter == InterpolationFilter::LINEAR)
            min_filter = GL_NEAREST_MIPMAP_LINEAR;
        if (behaviour.mipmap_filter == InterpolationFilter::NEAREST)
            min_filter = GL_NEAREST_MIPMAP_NEAREST;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, behaviour.mag_filter);
}

void Texture::bind_at(unsigned int slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, handle);
}

