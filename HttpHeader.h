#ifndef HTTPHEADER_H
#define HTTPHEADER_H

#include <string>

class HttpHeader {

	public:
		static std::string parseURI(const std::string &header);
		static std::string parseURL(const std::string &header);

	private:

};

#endif