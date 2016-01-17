#ifndef ROUTER_H
#define ROUTER_H

#include <string>
#include <functional>
#include <map>
#include "URI.h"
#include "Request.h"

class Router {

    public:
        Router();
        ~Router();
        void connect(std::string path, std::function<void(Request&)> function);
        bool route(Request &request);

    private:
        std::map<std::string, std::function<void(Request&)>> m_connections;

};

#endif