#include "rendering/Camera.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Camera::get_view_matrix() {
    std::cout << position.x << " " << position.z << std::endl;
    return glm::translate(
        glm::rotate(
            glm::rotate (
                glm::mat4(1.f),
                -pitch,
                glm::vec3(1.f, 0.f, 0.f)
            ),
            yaw,
            glm::vec3(0.f, 1.f, 0.f)
        ),
        -position
    );
}

glm::mat4 Camera::get_projection_matrix() {
    return glm::perspective(field_of_view, aspect_ratio, near_plane, far_plane);
}

glm::vec3 Camera::get_horizontal_axis() {
    glm::vec4 result = glm::rotate(glm::mat4(1.f), -yaw, glm::vec3(0, 1, 0)) * glm::vec4(1, 0, 0, 0);
    return glm::vec3(result.x, result.y, result.z);
}

glm::vec3 Camera::get_view_direction() {
    return glm::cross(glm::vec3(0, 1, 0), get_horizontal_axis());
}


