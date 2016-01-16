#include "FileOpener.h"

std::string FileOpener::readAll(std::string filename) {
	std::ifstream fp(filename);
	if(!fp.is_open()) {
		throw std::runtime_error("Unable to open file");
	}

	std::stringstream str;
	str << fp.rdbuf();
	fp.close();

	return str.str();
}