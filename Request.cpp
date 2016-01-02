#include "Request.h"

Request::Request(unsigned int socketId, const sockaddr_in &socketInfo) :
m_socketId(socketId),
m_sentBack(false) {
	m_ipAddr = inet_ntoa(socketInfo.sin_addr);
}

Request::~Request() {
	::close(m_socketId);
}

bool Request::receive(char *buffer, unsigned int buffsize) {
	int charNumber;
	charNumber = ::recv(getSocketId(), buffer, buffsize, 0);
		if(charNumber > 0) {
			buffer[charNumber] = 0;
			return true;
		}
	return false;
}

void Request::send(std::string data, int httpStatus) {
	//TODO: Simplify
	std::stringstream headers;
	headers << "HTTP/1.1 " << httpStatus << " OK\n";
	headers << m_headers.str() << "\n";
	data.insert(0, headers.str());
	if(::send(m_socketId, data.c_str(), data.size(), 0) < 0) {
		throw std::runtime_error("An error occured during sending");
	}
	m_sentBack = true;
}

void Request::setHeader(std::string key, std::string value) {
	m_headers << key << ": " << value << "\n";
}

bool Request::isSentBack() const {
	return m_sentBack;
}

unsigned int Request::getSocketId() const {
	return m_socketId;
}

std::string Request::getIpAddress() const {
	return m_ipAddr;
}