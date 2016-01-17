#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <thread>
#include <memory>
#include <tuple>

#include "Router.h"
#include "Network.h"
#include "URI.h"
#include "HttpHeader.h"
#include "Request.h"
#include "OpenSSL.h"
#include "Log.h"
#include "Exceptions/Exception.h"

class WebServer {

	public:
		WebServer(unsigned short port, Router *router, OpenSSL *ssl = nullptr);
		~WebServer();

	private:
		void requestCatcher();
		enum Protocol {HTTP, HTTPS};
		Network m_network;
		Router *m_router;
		std::unique_ptr<std::thread> m_catcher;
		bool m_done;
		OpenSSL *m_ssl;
		Protocol m_protocol;

};

#endif
