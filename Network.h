#ifndef NETWORK_H
#define NETWORK_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <memory>
#include <stdexcept>
#include <deque>
#include <string>
#include <cassert>
#include "Request.h"

class Network {

	public:
		Network();
		~Network();
		void bind(const int port);
		std::unique_ptr<Request> listen();
		void connect(const char *ipAddr, const int port);

	private:
		void createSocket();
		int m_socketId;
		bool m_bound;
		sockaddr_in m_srcInfo;
		sockaddr_in m_dstInfo;

};

#endif //NETWORK_H