#include "WebServer.h"

WebServer::WebServer(unsigned short port, Router *router) :
m_router(router) {
	m_network.bind(port);

	m_catcher = std::unique_ptr<std::thread>(new std::thread(&WebServer::requestCatcher, this));
}

WebServer::~WebServer() {
	//TODO: Use a non-blocking accept & recv
	m_catcher->join();
}

void WebServer::requestCatcher() {
	unsigned int socketClientId;
	char tmp[1000];

	while(true) {
		tmp[0] = 0;
		socketClientId = m_network.listen();
		if(m_network.receive(tmp, sizeof(tmp))) {
			std::string header(tmp);
			URI uri = HttpHeader::parseURI(header);
			std::cout << "URI: " << uri.getUri() << std::endl;
			std::cout << "URL: " << uri.getUrl() << std::endl;
			m_router->route(uri.getUrl());
			m_network.send(socketClientId, "Answer to the client");
		}
		m_network.close(socketClientId);
		std::this_thread::sleep_for(std::chrono::milliseconds(2));
	}
}