#include "stdextentions/StringUtils.h"

#include <iostream>

std::vector<std::string> StringUtils::split(const std::string& s, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    std::string temp = s;
    while ((pos = temp.find(delimiter)) != std::string::npos) {
        token = temp.substr(0, pos);
        tokens.push_back(token);
        temp.erase(0, pos + delimiter.length());
    }
    tokens.push_back(temp);
    return tokens;
}

std::string StringUtils::remove_first(const std::string &s, const std::string &target) {
    size_t pos = s.find(target);
    return s.substr(0, pos) + s.substr(pos+target.length(), std::string::npos);
}

