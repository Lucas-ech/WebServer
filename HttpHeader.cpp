#include "HttpHeader.h"

URI HttpHeader::parseURI(const std::string &header) {
	std::regex methodUri("(GET|HEAD|POST|PUT|DELETE|TRACE|OPTIONS|CONNECT|PATCH) ([^ ]+)");
	std::smatch results;

	std::regex_search(header, results, methodUri);

	if(results.size() != 3) {
		throw std::runtime_error("Unable to parse URI");
	}

	return URI(results[2]);
}
