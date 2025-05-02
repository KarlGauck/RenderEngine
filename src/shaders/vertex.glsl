#version 330 core
layout (location = 0) in vec3 i_position;
layout (location = 1) in vec3 i_color;
layout (location = 2) in vec2 i_texture_coords;
out vec3 color;
out vec2 texture_coords;

void main()
{
    gl_Position = vec4(i_position, 1.0) + vec4(0.1, 0.1, 0.f, 0.f) * gl_InstanceID;
    color = i_color;
    texture_coords = i_texture_coords;
}