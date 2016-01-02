#include "Router.h"

Router::Router() {

}

Router::~Router() {

}

void Router::connect(std::string path, std::function<void(URI&, Request&)> function) {
	m_connections[path] = function;
}

bool Router::route(URI &uri, Request &request) {
	auto connection = m_connections.find(uri.getUrl());
	if(connection == m_connections.end()) {
		std::size_t wildcardPos;
		for(auto&& route : m_connections) {
			wildcardPos = route.first.find("*");
			if(wildcardPos != std::string::npos) {
				std::string base = route.first.substr(0, wildcardPos);
				if(route.first.substr(0, wildcardPos) == uri.getUrl().substr(0, wildcardPos)) {
					route.second(uri, request);
					return true;
				}
			}
		}
		return false;
	}

	connection->second(uri, request);
	return true;
}