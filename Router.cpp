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
		return false;
	}

	connection->second({});
}