#include "URI.h"

URI::URI(std::string uri) :
m_uri(uri),
m_url(findUrl()),
m_urn(findUrn()) {

}

URI::~URI() {

}

std::string URI::getUri() const {
	return m_uri;
}

std::string URI::getUrl() const {
	return m_url;
}

std::string URI::getUrn() const {
	return m_urn;
}

std::string URI::findUrl() {
	std::size_t posHash = m_uri.find_first_of("#");
	std::size_t posInterro = m_uri.find_first_of("?");

	if(posHash == std::string::npos && posInterro == std::string::npos) {
		return m_uri;
	}

	std::size_t firstPos = std::min(posHash, posInterro);
	if(firstPos == std::string::npos) {
		if(posHash == std::string::npos) {
			return m_uri.substr(0, posInterro);
		} else {
			return m_uri.substr(0, posHash);
		}
	} else {
		return m_uri.substr(0, firstPos);
	}
}

std::string URI::findUrn() {
	return m_uri.substr(m_url.size());
}
