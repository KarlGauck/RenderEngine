# pragma once
#include <glm/glm.hpp>

class Camera {
public:
    glm::vec3 position;
    float pitch;
    float yaw;
    float field_of_view;
    float near_plane;
    float far_plane;
    float aspect_ratio;

    glm::mat4 get_view_matrix();
    glm::mat4 get_projection_matrix();

    glm::vec3 get_horizontal_axis();
    glm::vec3 get_view_direction();
};
