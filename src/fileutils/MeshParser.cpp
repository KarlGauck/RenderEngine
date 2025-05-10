#include "fileutils/MeshParser.h"

#include <glm/glm.hpp>

MeshObject MeshParser::parse_wavefront_obj(std::string data) {
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> position_indices;
    std::vector<unsigned int> texture_indices;
    std::vector<unsigned int> normal_indices;
}
