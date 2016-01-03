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
	using namespace std::literals::string_literals;

	m_headers.push_front("Content-Length: "s + std::to_string(data.size()));
	m_headers.push_front("HTTP/1.1 "s + std::to_string(httpStatus) + " OK"s);

	std::stringstream headers;
	for(auto&& header : m_headers) {
		headers << header << "\n";
	}

	data.insert(0, headers.str());
	if(::send(m_socketId, data.c_str(), data.size(), 0) < 0) {
		throw std::runtime_error("An error occured during sending");
	}
	m_sentBack = true;
}

void Request::setHeader(std::string key, std::string value) {
	using namespace std::literals::string_literals;
	m_headers.push_back(key + ": "s + value + "\n"s);
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