#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <sstream>
#include <string>
#include <functional>
#include "Request.h"
#include "Router.h"
#include "HttpHeader.h"
#include "WebServer.h"
#include "URI.h"
#include "Log.h"

void readFile(std::string file, Request &request) {
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

void readDir(std::string path, std::string basedir, Request &request) {
	std::size_t pathBeginPos = request.getUrl().find(basedir) + basedir.size();
	std::string file = path + request.getUrl().substr(pathBeginPos);
	readFile(file, request);
}

int main(int argc, char const *argv[])
{
	using namespace std::placeholders;

	Router router;
	//router.connect("/", std::bind(readFile, "www/index.html", _1));
	//router.connect("/*", std::bind(readDir, "www/", "/", _1));

	Log::write("Listening to port ", 8080);
	WebServer(8080, &router);

	return 0;
}
