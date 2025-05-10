#pragma once

#include <string>
#include <vector>

class StringUtils {
public:
    static std::vector<std::string> split(const std::string& s, const std::string& delimiter);
};