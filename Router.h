#ifndef ROUTER_H
#define ROUTER_H

#include <string>
#include <functional>
#include <map>

class Router {

	public:
		Router();
		~Router();
		void connect(std::string path, std::function<void(std::map<std::string, std::string>)> function);
		bool route(std::string path);

	private:
		std::map<std::string, std::function<void(std::map<std::string, std::string>)>> m_connections;

};

#endif