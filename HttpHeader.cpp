#include "HttpHeader.h"

std::string HttpHeader::parseURI(const std::string &header) {
	std::size_t pos = header.find("GET ");

	if(pos == std::string::npos) {
		return "";
	}

	pos += 4; // Ignore "GET "

	std::size_t length = header.find_first_of(" ", pos) - pos;
	return header.substr(pos, length);
}

std::string HttpHeader::parseURL(const std::string &header) {
	std::string uri = parseURI(header);
	std::size_t posHash = uri.find_first_of("#");
	std::size_t posInterro = uri.find_first_of("?");

	if(posHash == std::string::npos && posInterro == std::string::npos) {
		return uri;
	}

	std::size_t firstPos = std::min(posHash, posInterro);
	if(firstPos == std::string::npos) {
		if(posHash == std::string::npos) {
			return uri.substr(0, posInterro);
		} else {
			return uri.substr(0, posHash);
		}
	} else {
		return uri.substr(0, firstPos);
	}
}