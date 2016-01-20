#include "RequestHandler.h"

void RequestHandler::file(std::string file, Request &request) {
	std::string fileContent;
	try {
		fileContent = FileOpener::readAll(file);
	}
	catch(const std::exception& e) {
        request.error(404);
	}

    std::string extension = FileOpener::getExtension(file);
    if (extension.empty() == false) {
        auto pos = Mime::Type.find(extension);
        if (pos != Mime::Type.end()) {
            request.setHeader("Content-Type", pos->second);
        }
    }

    request.send(fileContent);
}

void RequestHandler::directory(std::string path, std::string basedir, Request &request) {
	std::size_t pathBeginPos = request.getUrl().find(basedir) + basedir.size();
    std::string file = path + request.getUrl().substr(pathBeginPos);

    RequestHandler::file(file, request);
}