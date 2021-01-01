#include "util.h"

#include <fstream>

std::string read_all(std::string path) {
    std::ifstream file{path};
    std::string content{
        std::istreambuf_iterator<char>(file),
        std::istreambuf_iterator<char>()
    };
    return content;
}
