#ifndef FILEOPENER_H
#define FILEOPENER_H

#include <string>
#include <fstream>
#include <sstream>

class FileOpener {

    public:
        static std::string readAll(std::string filename);
        static std::string getExtension(std::string filename);
        static bool isExists(std::string filename);

    private:

};

#endif