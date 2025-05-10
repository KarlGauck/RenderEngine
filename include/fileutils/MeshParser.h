#pragma once

#include <string>

#include "rendering/MeshObject.h"

class MeshParser {
public:
    static MeshObject parse_wavefront_obj(std::string data);
};