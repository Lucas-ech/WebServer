#ifndef HTTPHEADER_H
#define HTTPHEADER_H

#include <stdexcept>
#include <regex>
#include <string>
#include <sstream>
#include <map>
#include <memory>

#include "URI.h"
#include "Http.h"
#include "Exceptions/Exception.h"

class HttpHeader {

    public:
        HttpHeader();
        ~HttpHeader();
        void setHeader(std::string key, std::string value);
        void setStatus(int status);
        void setContentLength(std::size_t length);
        void setContentType(std::string mime, std::string encoding = "UTF-8");
        const std::string getHeader();
        static std::unique_ptr<URI> parseURI(const std::string &header);

    private:
        std::map<std::string, std::string> m_headers;
        std::string m_status;

};

#endif