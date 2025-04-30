//
// Created by karlg on 29.04.25.
//

#ifndef TEXTUREINFO_H
#define TEXTUREINFO_H
#include <glad/glad.h>

enum WrapBehaviour {
    CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
    CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
    MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
    REPEAT = GL_REPEAT
};

enum InterpolationFilter {
    NEAREST = GL_NEAREST,
    LINEAR = GL_LINEAR,
};

struct TextureBehaviour {
    WrapBehaviour wrap_behaviour_s;
    WrapBehaviour wrap_behaviour_t;
    WrapBehaviour wrap_behaviour_r;
    InterpolationFilter min_filter;
    InterpolationFilter mag_filter;
    InterpolationFilter mipmap_filter;
    float border_color[4];
};

#endif //TEXTUREINFO_H

