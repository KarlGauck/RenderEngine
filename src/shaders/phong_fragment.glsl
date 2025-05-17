#version 460 core
in vec3 position;
in vec3 color;
in vec3 normal;
in vec2 texture_coords;
in mat4x4 f_transform;

out vec4 FragColor;
uniform float scalar;

uniform vec3 view_position;

uniform sampler2D t1;
uniform sampler2D t2;

struct Light {
    vec4 position;
    vec4 color;
};

layout(binding = 1, std430) readonly buffer ssbo2 {
    Light lights[];
};

void main()
{
    float ambient_strength = 0.1;
    float specular_strength = 0.5;
    float shininess = 32;

    vec3 object_color = vec3(0.537, 0.612, 0.31);
    vec3 ambient_light = vec3(0);
    vec3 diffuse_light = vec3(0);
    vec3 specular_light = vec3(0);

    vec3 real_normal = normalize(normal);

    vec3 view_direction = normalize(position - view_position);

    for (int i = 0; i < lights.length(); i++) {
        vec3 light_dir = normalize(lights[i].position.xyz - position);
        vec3 light_color = lights[i].color.xyz;

        diffuse_light += max(dot(light_dir, real_normal), 0) * light_color;
        vec3 reflect_dir = reflect(light_dir, real_normal);
        specular_light += pow(max(dot(view_direction, reflect_dir), 0), shininess) * light_color;

        ambient_light += light_color;
    }
    ambient_light /= lights.length();
    ambient_light *= ambient_strength;
    specular_light *= specular_strength;

    FragColor = vec4((ambient_light + diffuse_light + specular_light) * object_color, 1);
}