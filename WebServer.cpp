#include "WebServer.h"

WebServer::WebServer(unsigned short port, Router *router, OpenSSL *ssl) :
m_router(router),
m_done(false),
m_ssl(ssl) {
	m_network.bind(port);
	m_protocol = ssl == nullptr ? HTTP : HTTPS;
	m_catcher = std::unique_ptr<std::thread>(new std::thread(&WebServer::requestCatcher, this));
}

WebServer::~WebServer() {
	m_done = true;
	m_catcher->join();

	if(m_ssl != nullptr) {
		 delete m_ssl;
	}
}

void WebServer::requestCatcher() {
	char buffer[1000];
	RequestInfo requestInfo;

	while(!m_done) {
		if(m_network.listen(requestInfo)) {
			std::unique_ptr<Request> request(new Request(std::get<0>(requestInfo), std::get<1>(requestInfo)));
			if(m_protocol == HTTPS) {
				request->setHttps(m_ssl->getContext());
			}

			if(request->receive(buffer, sizeof(buffer))) {
				std::string header(buffer);
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
