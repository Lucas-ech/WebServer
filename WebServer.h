#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <iostream>
#include <thread>
#include <memory>
#include "Router.h"
#include "Network.h"
#include "URI.h"
#include "HttpHeader.h"
#include "Request.h"

class WebServer {

	public:
		WebServer(unsigned short port, Router *router);
		~WebServer();

	private:
		void requestCatcher();
		Network m_network;
		Router *m_router;
		std::unique_ptr<std::thread> m_catcher;
		bool m_done;

};

#endif
