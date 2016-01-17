#include "Router.h"

Router::Router() {

}

Router::~Router() {

}

void Router::connect(std::string path, std::function<void(Request&)> function) {
    m_connections[path] = function;
}

bool Router::route(Request &request) {
    auto connection = m_connections.find(request.getUrl());
    if (connection == m_connections.end()) {
        for (auto&& route : m_connections) {
            std::size_t wildcardPos;
            wildcardPos = route.first.find("*");
            if (wildcardPos != std::string::npos) {
                if (route.first.substr(0, wildcardPos) == request.getUrl().substr(0, wildcardPos)) {
                    route.second(request);
                    return true;
                }
            }
        }
        return false;
    }

    connection->second(request);
    return true;
}