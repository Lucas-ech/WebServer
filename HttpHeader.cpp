#include "HttpHeader.h"

std::unique_ptr<URI> HttpHeader::parseURI(const std::string &header) {
	std::regex methodUri("(GET|HEAD|POST|PUT|DELETE|TRACE|OPTIONS|CONNECT|PATCH) ([^ ]+)");
	std::smatch results;

	std::regex_search(header, results, methodUri);

	if(results.size() != 3) {
		throw RequestException("Unable to parse URI");
	}

	return std::unique_ptr<URI>(new URI(results[2]));
}
