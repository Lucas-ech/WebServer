#include <iostream>
#include <chrono>
#include <thread>
#include "Network.h"
#include "Router.h"
#include "HttpHeader.h"
#include "WebServer.h"

void a(std::map<std::string, std::string> truc) {
	std::cout << "Coucou" << std::endl;
}

int main(int argc, char const *argv[])
{
	Router router;
	router.connect("/", a);

	WebServer(8080, &router);



	return 0;
}