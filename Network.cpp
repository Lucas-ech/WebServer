#include "Network.h"

Network::Network(): m_bound(false) {

}

Network::~Network() {
	if(m_bound) {
		::close(m_socketId);
	}
}

void Network::bind(const int port) {
	createSocket();
	m_srcInfo.sin_family = AF_INET;
	m_srcInfo.sin_addr.s_addr = INADDR_ANY;
	m_srcInfo.sin_port = htons(port);
	if(::bind(m_socketId, (sockaddr*)&m_srcInfo, sizeof(m_srcInfo)) < 0) {
		throw std::runtime_error("Unable to bind");
	}
	m_bound = true;
	::listen(m_socketId, 1);
}

unsigned int Network::listen() {
	if(!m_bound) {
		throw std::logic_error("You need to bind first");
	}

	unsigned int srcSize = sizeof(m_srcInfo);
	int newSocket = ::accept(m_socketId, (sockaddr*)&m_srcInfo, &srcSize);
	if(newSocket < 0) {
		throw std::runtime_error("Unable to call accept()");
	} else {
		m_inputSockets.push_back(newSocket);
	}

	return m_inputSockets.size() - 1;
}

bool Network::receive(char *buffer, unsigned int buffsize) {
	int charNumber;
	charNumber = ::recv(m_inputSockets[0], buffer, buffsize, 0);
		if(charNumber > 0) {
			buffer[charNumber] = 0;
			return true;
		}
	return false;
}

void Network::connect(const char *ipAddr, const int port) {
	createSocket();
	m_dstInfo.sin_family = AF_INET;
	m_dstInfo.sin_addr.s_addr = inet_addr(ipAddr);
	m_dstInfo.sin_port = htons(port);
	if(::connect(m_socketId, (sockaddr*)&m_dstInfo, sizeof(m_dstInfo)) < 0) {
		throw std::runtime_error("Unable to connect");
	}
}

void Network::send(unsigned int socketId, std::string data) {
	assert(m_inputSockets.size() > socketId);
	int err = ::send(m_inputSockets[socketId], data.c_str(), data.size(), 0);
	if(err < 0) {
		throw std::runtime_error("An error occured during sending");
	}
}

void Network::close(unsigned int socketId) {
	assert(m_inputSockets.size() > socketId);
	::close(m_inputSockets[socketId]);
}


void Network::createSocket() {
	m_socketId = ::socket(AF_INET, SOCK_STREAM, 0);
	if(m_socketId < 0) {
		throw std::runtime_error("Socket creation failed");
	}
}