#ifndef FILEINPUT_H
#define FILEINPUT_H

#include <memory>
#include <string>

using namespace std;

struct TextureData {
    int width;
    int height;
    int channels;
    unique_ptr<unsigned char> data;
};

class FileInput {
public:
    static string read_file(const string &file_path);
    static TextureData read_texture(const string &file_path);
};

#endif //FILEINPUT_H
