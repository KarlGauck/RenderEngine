#version 330 core
in vec3 color;
in vec2 texture_coords;
out vec4 FragColor;
uniform vec4 ourColor;

uniform sampler2D tex;

void main()
{
    FragColor = vec4(color, 1.f) * ourColor * texture(tex, texture_coords);
}