#pragma once

#include <string>

#include <glm/glm.hpp>

#include "rendering/MeshObject.h"

class MeshParser {

public:
    static glm::vec3 strings_to_vec(std::vector<std::string> strings, int first);
    static glm::vec3 parse_vertex_position(std::string line);
    static glm::vec3 parse_vertex_color(std::string line);
    static glm::vec3 parse_vertex_normal(std::string line);
    static MeshObject parse_wavefront_obj(std::string data);
};