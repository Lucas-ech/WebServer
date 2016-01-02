#include "Router.h"

Router::Router() {

}

Router::~Router() {

}

void Router::connect(std::string path, std::function<void(std::map<std::string, std::string>)> function) {
	m_connections[path] = function;
}

bool Router::route(std::string path) {
	auto connection = m_connections.find(path);
	if(connection == m_connections.end()) {
		std::size_t wildcardPos;
		for(auto&& route : m_connections) {
			wildcardPos = route.first.find("*");
			if(wildcardPos != std::string::npos) {
				std::string base = route.first.substr(0, wildcardPos);
				if(route.first.substr(0, wildcardPos) == path.substr(0, wildcardPos)) {
					route.second({});
					return true;
				}
			}
		}
		return false;
	}

	connection->second({});
}