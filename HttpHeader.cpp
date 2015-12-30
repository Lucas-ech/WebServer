#include "HttpHeader.h"

URI HttpHeader::parseURI(const std::string &header) {
	std::size_t pos = header.find("GET ");

	if(pos == std::string::npos) {
		throw std::runtime_error("Unable to parse URI");
	}

	pos += 4; // Ignore "GET "

	std::size_t length = header.find_first_of(" ", pos) - pos;

	return URI(header.substr(pos, length));
}
