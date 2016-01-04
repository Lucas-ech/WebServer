#include "Network.h"

Network::Network(): m_socketId(0), m_bound(false) {

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
	if(::bind(m_socketId, reinterpret_cast<sockaddr*>(&m_srcInfo), sizeof(m_srcInfo)) < 0) {
		throw std::runtime_error("Unable to bind");
	}
	m_bound = true;

	if(::listen(m_socketId, 1) < 0) {
		throw std::runtime_error("Unable to listen");
	}
}

bool Network::listen(std::unique_ptr<Request> &request) {
	if(!m_bound) {
		throw std::logic_error("You need to bind first");
	}

	unsigned int srcSize = sizeof(m_srcInfo);
	int newSocket = ::accept(m_socketId, reinterpret_cast<sockaddr*>(&m_srcInfo), &srcSize);

	// There is no new connection
	if(errno == EAGAIN) {
		//Reset errno
		errno = 0;
		return false;
	} else if(newSocket < 0) {
		throw std::runtime_error("Unable to call accept()");
	}

	request = std::unique_ptr<Request>(new Request(static_cast<unsigned int>(newSocket), m_srcInfo));
	return true;
}

void Network::connect(const char *ipAddr, const int port) {
	createSocket();
	m_dstInfo.sin_family = AF_INET;
	m_dstInfo.sin_addr.s_addr = inet_addr(ipAddr);
	m_dstInfo.sin_port = htons(port);
	if(::connect(m_socketId, reinterpret_cast<sockaddr*>(&m_dstInfo), sizeof(m_dstInfo)) < 0) {
		throw std::runtime_error("Unable to connect");
	}
}

void Network::createSocket() {
	m_socketId = ::socket(AF_INET, SOCK_STREAM, 0);
	if(m_socketId < 0) {
		throw std::runtime_error("Socket creation failed");
	}

	//Setting listening in no-blocking mode
	int flags = fcntl(m_socketId, F_GETFL, 0);
    fcntl(m_socketId, F_SETFL, flags | O_NONBLOCK);

    flags = fcntl(m_socketId, F_GETFL, 0);
    if ((flags & O_NONBLOCK) != O_NONBLOCK) {
        throw std::runtime_error("Unable to set listening in no-blocking mode");
    }
}