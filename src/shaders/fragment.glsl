#version 330 core
in vec3 color;
in vec2 texture_coords;
out vec4 FragColor;
uniform vec4 ourColor;

uniform sampler2D t1;
uniform sampler2D t2;

void main()
{
    FragColor = texture(t2, texture_coords);
}