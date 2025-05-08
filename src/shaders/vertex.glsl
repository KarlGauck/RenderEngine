#version 460 core
layout (location = 0) in vec3 i_position;
layout (location = 1) in vec3 i_normal;
layout (location = 2) in vec3 i_color;
layout (location = 3) in vec2 i_texture_coords;
out vec3 color;
out vec2 texture_coords;
out mat4x4 f_transform;

uniform mat4 view_matrix;
uniform mat4 projection_matrix;

layout(binding = 0, std430) readonly buffer ssbo1 {
    mat4 i_transform[];
};

void main()
{
    gl_Position = projection_matrix * view_matrix * i_transform[gl_InstanceID] * vec4(i_position, 1.0);
    vec4 pos = projection_matrix * view_matrix * i_transform[gl_InstanceID] * vec4(i_position, 1.0);
    color = i_normal;
    texture_coords = i_texture_coords;
    f_transform = i_transform[gl_InstanceID];
}