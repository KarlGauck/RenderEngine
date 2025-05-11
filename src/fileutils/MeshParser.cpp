#include "fileutils/MeshParser.h"

#include <iostream>
#include <map>
#include <glm/glm.hpp>

#include "stdextentions/StringUtils.h"

glm::vec3 MeshParser::parse_vertex_position(std::string line) {
    std::string data = StringUtils::remove_first(line, "v ");
    std::vector values = StringUtils::split(data, " ");
    return strings_to_vec(values, 0);
}

glm::vec3 MeshParser::parse_vertex_color(std::string line) {
    std::string data = StringUtils::remove_first(line, "v ");
    std::vector values = StringUtils::split(data, " ");
    return strings_to_vec(values, 4);
}

glm::vec3 MeshParser::parse_vertex_normal(std::string line) {
    std::string data = StringUtils::remove_first(line, "vn ");
    std::vector values = StringUtils::split(data, " ");
    return strings_to_vec(values, 0);
}

glm::vec3 MeshParser::strings_to_vec(std::vector<std::string> strings, int first) {
    auto result = glm::vec3(0.f);
    int index = 0;
    for (const std::string& str: strings) {
        std::cout << "i: " << index << std::endl;
        if (index < first) {
            index ++;
            continue;
        }
        if (index > first + 2)
            break;
        std::cout << str << std::endl;
        result[index-first] = std::stof(str);
        index ++;
    }
    return result;
}


MeshObject MeshParser::parse_wavefront_obj(std::string data) {
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> colors;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> position_indices;
    std::vector<unsigned int> texture_indices;
    std::vector<unsigned int> normal_indices;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    std::vector lines = StringUtils::split(data, "\n");
    std::map<std::string, unsigned int> element_indices;  // which vertex (calculatet from input) is at which position in the generated meshobject
    for (std::string line: lines) {
        std::cout << line << std::endl;
        if (line.find("v ") == 0) {
            std::cout << "position" << std::endl;
            positions.push_back(parse_vertex_position(line));
            colors.push_back(parse_vertex_color(line));
        }
        if (line.find("vn ") == 0) {
            std::cout << "normal" << std::endl;
            normals.push_back(parse_vertex_normal(line));
        }
        if (line.find("f ") == 0) {
            std::cout << "element" << std::endl;
            std::string raw = StringUtils::remove_first(line, "f ");
            std::vector data = StringUtils::split(raw, " ");
            for (int element_index = 0; element_index < 3; element_index++) {
                if (element_index >= data.size())
                    break;
                if (element_indices.contains(data[element_index]))
                    indices.push_back(element_indices[data[element_index]]);
                else {
                    indices.push_back(element_indices.size());
                    element_indices[data[element_index]] = element_indices.size();
                    std::vector attribute_indices = StringUtils::split(data[element_index], "/");
                    std::cout << "hey" << std::endl;
                    std::cout << attribute_indices[0] << std::endl;
                    std::cout << (!attribute_indices.empty() && !attribute_indices[0].empty() ? 0 : 1) << std::endl;
                    std::cout << (attribute_indices.size() > 1 && !attribute_indices[1].empty() ? 0 : 1) << std::endl;
                    std::cout << (attribute_indices.size() > 2 && !attribute_indices[2].empty() ? 0 : 1) << std::endl;
                    std::cout << stoi(attribute_indices[0])-1 << std::endl;
                    vertices.emplace_back(
                        !attribute_indices.empty() && !attribute_indices[0].empty() ? positions[stoi(attribute_indices[0])-1] : glm::vec3(0.f),
                        attribute_indices.size() > 2 && !attribute_indices[2].empty() ? normals[stoi(attribute_indices[2])-1] : glm::vec3(0.f),
                        !attribute_indices.empty() && !attribute_indices[0].empty() ? colors[stoi(attribute_indices[0])-1] : glm::vec3(0.f),
                        glm::vec2(0.f, 0.f)
                    );
                    std::cout << "hi" << std::endl;
                }
            }
        }
    }

    std::cout << vertices.size() << std::endl;
    std::cout << indices.size() << std::endl;
    return {vertices, indices};
}
