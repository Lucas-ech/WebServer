#ifndef HTTPHEADER_H
#define HTTPHEADER_H

#include <stdexcept>
#include <regex>
#include <string>
#include "URI.h"

class HttpHeader {

	public:
		static URI parseURI(const std::string &header);

	private:

};

#endif