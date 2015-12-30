#ifndef NETWORK_H
#define NETWORK_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdexcept>
#include <deque>
#include <string>
#include <cassert>

class Network {

	public:
		Network();
		~Network();
		void bind(const int port);
		unsigned int listen();
		bool receive(char *buffer, unsigned int buffsize);
		void connect(const char *ipAddr, const int port);
		void send(unsigned int socketId, std::string data);
		void close(unsigned int socketId);

	private:
		void createSocket();
		int m_socketId;
		bool m_bound;
		std::deque<int> m_inputSockets;
		sockaddr_in m_srcInfo;
		sockaddr_in m_dstInfo;

};

#endif //NETWORK_H