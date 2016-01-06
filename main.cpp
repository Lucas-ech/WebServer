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
#include "OpenSSL.h"

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

int main()
{
	using namespace std::placeholders;

	Router router;
	//router.connect("/", std::bind(readFile, "www/index.html", _1));
	//router.connect("/*", std::bind(readDir, "www/", "/", _1));

	//OpenSSL ssl("cert.pem", "privkey.pem");

	Log::write("Listening to port ", 8080);
	WebServer webserver(8080, &router/*, &ssl*/);

	while(true) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	return 0;
}
