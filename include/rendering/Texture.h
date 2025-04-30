//
// Created by karlg on 29.04.25.
//

#ifndef TEXTURE_H
#define TEXTURE_H
#include <fileutils/FileInput.h>

#include "TextureBehaviour.h"

class Texture {
public:
    unsigned int handle;

    void load_texture(TextureData texture_data);
    void set_texture_behaviour(const TextureBehaviour &behaviour);
    void bind_at(unsigned int slot);
};

#endif //TEXTURE_H
