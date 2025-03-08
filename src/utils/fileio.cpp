//
// Created by ssj5v on 27-09-2024.
//

#include "fileio.h"

bool readFile(const std::string& path, std::string &data) {
    std::ifstream ifs(path);
    if(ifs.is_open()) {
        std::ostringstream oss;
        oss << ifs.rdbuf();
        data = oss.str();
        return true;
    }
    return false;
}

std::string getFileExtension(const std::string& path) {
    std::string str = path;
    size_t dotPos = str.find_last_of('.');

    if (dotPos == std::string::npos || dotPos == 0 || dotPos == path.length() - 1) {
        return "";
    }

    return str.substr(dotPos + 1);
}
