//
// Created by karlg on 18.03.25.
//

#include <cstring>
#include <fstream>
#include <sstream>
#include "FileInput.h"

string FileInput::readFile(const string &filePath) {
    ifstream stream(filePath);
    string line;
    stringstream ss;
    while (getline(stream, line)) {
        ss << line << "\n";
    }
    return ss.str();
}

