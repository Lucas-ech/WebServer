#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <sstream>
#include <functional>
#include "Request.h"
#include "Router.h"
#include "HttpHeader.h"
#include "WebServer.h"
#include "URI.h"

void readFile(std::string file, URI &uri, Request &request) {
	std::fstream fp(file);
	if(fp.is_open()) {
		std::stringstream pubKey;
		pubKey << fp.rdbuf();
		fp.close();
		request.setHeader("Content-Type", "text/html; charset=UTF-8");
		request.send(pubKey.str());
	} else {
		request.send("", 404);
	}
}

void readDir(std::string path, std::string basedir, URI &uri, Request &request) {
	std::size_t pathBeginPos = uri.getUrl().find(basedir) + basedir.size();
	std::string file = path + uri.getUrl().substr(pathBeginPos);
	readFile(file, uri, request);
}

int main(int argc, char const *argv[])
{
	using namespace std::placeholders;

	Router router;
	//router.connect("/", std::bind(readFile, "www/index.html", _1, _2));
	//router.connect("/*", std::bind(readDir, "www/", "/", _1, _2));

	WebServer(8080, &router);

	return 0;
}
