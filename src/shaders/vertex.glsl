#version 330 core
layout (location = 0) in vec3 i_position;
layout (location = 1) in vec3 i_color;
layout (location = 2) in vec2 i_texture_coords;
layout (location = 3) in vec2 transform;
out vec3 color;
out vec2 texture_coords;

void main()
{
    gl_Position = vec4(i_position, 1.0) + vec4(transform, 0.f, 0.f);
    color = i_color;
    texture_coords = i_texture_coords;
}