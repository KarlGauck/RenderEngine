#version 460 core
in vec3 color;
in vec2 texture_coords;
in mat4x4 f_transform;
out vec4 FragColor;
uniform float scalar;

uniform sampler2D t1;
uniform sampler2D t2;

void main()
{
    FragColor = texture(t2, texture_coords);
}