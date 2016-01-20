#ifndef REQUEST_HANDLER
#define REQUEST_HANDLER

#include <string>

#include "Request.h"

class RequestHandler {

	public:
		static void file(std::string file, Request &request);
		static void directory(std::string path, std::string basedir, Request &request);

	private:

};

#endif