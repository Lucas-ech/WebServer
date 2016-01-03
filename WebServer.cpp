#include "WebServer.h"

WebServer::WebServer(unsigned short port, Router *router) :
m_router(router),
m_done(false) {
	m_network.bind(port);

	m_catcher = std::unique_ptr<std::thread>(new std::thread(&WebServer::requestCatcher, this));
}

WebServer::~WebServer() {
	m_done = true;
	m_catcher->join();
}

void WebServer::requestCatcher() {
	char tmp[1000];

	while(!m_done) {
		tmp[0] = 0;
		std::unique_ptr<Request> request;
		if(m_network.listen(request)) {
			if(request->receive(tmp, sizeof(tmp))) {
				std::string header(tmp);
				std::unique_ptr<URI> uri = HttpHeader::parseURI(header);
				request->setUri(std::move(uri));

				if(m_router->route(*request)) {
					if(!request->isSentBack()) {
						request->send("");
					}
				} else {
					request->send("<h1>Error 404</h1>");
				}
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(2));
	}
}
