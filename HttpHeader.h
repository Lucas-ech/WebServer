#ifndef HTTPHEADER_H
#define HTTPHEADER_H

#include <stdexcept>
#include <regex>
#include <string>
#include <memory>
#include "URI.h"

class HttpHeader {

	public:
		static std::unique_ptr<URI> parseURI(const std::string &header);

	private:

};

#endif