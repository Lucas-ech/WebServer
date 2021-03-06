#include "FileOpener.h"

std::string FileOpener::readAll(std::string filename) {
    std::ifstream fp(filename);
    if (fp.is_open() == false) {
        throw std::runtime_error("Unable to open file");
    }

    std::stringstream str;
    str << fp.rdbuf();
    fp.close();

    return str.str();
}

std::string FileOpener::getExtension(std::string filename) {
    std::size_t pos;
    pos = filename.find_last_of(".");
    if (pos == std::string::npos) {
        return "";
    }
    return filename.substr(pos + 1);
}

bool FileOpener::isExists(std::string filename) {
    std::ifstream fp(filename);
    if (fp.is_open()) {
        fp.close();
        return true;
    }
    return false;
}
