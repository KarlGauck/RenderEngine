//
// Created by karlg on 18.03.25.
//

#include <cstring>
#include <fstream>
#include <sstream>
#include <stb_image.h>
#include <iostream>
#include "fileutils/FileInput.h"

#include "stdextentions/StringUtils.h"

string FileInput::read_file(const string &file_path) {
    ifstream stream(file_path);
    stringstream ss;
    /*
    while (!ss.eof()) {
        string s = stream.read();
        std::cout << c;
        if (c != '\r' && !ss.eof())
            ss << c;
    }
    */
    /*
    for (string line; getline(stream, line);) {
        ss.eof();
        std::cout << StringUtils::remove_first(line, "\r") << std::endl;
        ss << line << "\n";
    }
    //stream.seekg(0, ios::beg);
    */
    stream >> ss.rdbuf();
    stream.close();
    std::cout << "hey";
    std::cout << ss.str() << std::endl;
    return ss.str();
}

TextureData FileInput::read_texture(const string &file_path) {
    int width, height, channels;
    std::unique_ptr<unsigned char> data(stbi_load(file_path.c_str(), &width, &height, &channels, 0));
    return {width, height, channels, (std::move(data))};
}

