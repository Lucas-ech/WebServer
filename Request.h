#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <stdexcept>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sstream>

class Request {

	public:
		Request(unsigned int socketId, const sockaddr_in &socketInfo);
		~Request();
		bool receive(char *buffer, unsigned int buffsize);
		void send(std::string data, int httpStatus = 200);
		void setHeader(std::string key, std::string value);
		bool isSentBack() const;
		unsigned int getSocketId() const;
		std::string getIpAddress() const;

	private:
		unsigned int m_socketId;
		bool m_sentBack;
		std::string m_ipAddr;
		std::stringstream m_headers;

};

#endif