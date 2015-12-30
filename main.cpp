#include <iostream>
#include <chrono>
#include <thread>
#include "Network.h"
#include "HttpHeader.h"

int main(int argc, char const *argv[])
{
	Network net;
	unsigned int socketClientId;
	char tmp[1000];
	int nloop = 0;

	net.bind(8080);
	while(true) {
		tmp[0] = 0;
		socketClientId = net.listen();
		if(net.receive(tmp, sizeof(tmp))) {
			std::string header(tmp);
			URI uri = HttpHeader::parseURI(header);
			std::cout << "URI: " << uri.getUri() << std::endl;
			std::cout << "URL: " << uri.getUrl() << std::endl;
			net.send(socketClientId, "Answer to the client");
		}
		net.close(socketClientId);
		std::this_thread::sleep_for(std::chrono::milliseconds(2));
	}
	return 0;
}