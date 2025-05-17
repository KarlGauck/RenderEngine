#version 460 core
in vec3 color;
in vec2 texture_coords;
in mat4x4 f_transform;
out vec4 FragColor;
uniform float scalar;

uniform sampler2D t1;
uniform sampler2D t2;

layout(binding = 1, std430) readonly buffer ssbo2 {
    float lel[];
};

void main()
{
    FragColor = vec4(color, 1.f); //* texture(t1, texture_coords);
}