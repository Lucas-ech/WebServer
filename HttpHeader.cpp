#include "HttpHeader.h"

HttpHeader::HttpHeader() {

}

HttpHeader::~HttpHeader() {

}

void HttpHeader::setHeader(std::string key, std::string value) {
    if (key.empty() || value.empty()) {
        throw RenderException("Empty field given to setHeader");
    }
    m_headers[key] = value;
}

void HttpHeader::setStatus(int status) {
    using namespace std::literals::string_literals;

    auto plainStatus = Http::Status.find(status);
    if (plainStatus == Http::Status.end()) {
        throw RenderException("Status does not exist");
    }
    m_status = "HTTP/1.1 "s + plainStatus->second;
}

void HttpHeader::setContentLength(std::size_t length) {
    setHeader("Content-Length", std::to_string(length));
}

void HttpHeader::setContentType(std::string mime, std::string encoding) {
    using namespace std::literals::string_literals;

    setHeader("Content-Type", mime + "; charset="s + encoding);
}


const std::string HttpHeader::getHeader() {
    std::stringstream header;
    if (m_status.empty() == false) {
        header << m_status << "\n";
    }

    if (m_headers.size() > 0) {
        for (const auto &item : m_headers) {
            header << item.first << ": " << item.second << "\n";
        }
    }

    // If there is some data, adds a newline at the end
    if (header.rdbuf()->in_avail()) {
        header << "\n";
    }

    return header.str();
}


std::unique_ptr<URI> HttpHeader::parseURI(const std::string &header) {
    std::regex methodUri("(GET|HEAD|POST|PUT|DELETE|TRACE|OPTIONS|CONNECT|PATCH) ([^ ]+)");
    std::smatch results;

    std::regex_search(header, results, methodUri);

    if (results.size() != 3) {
        throw RequestException("Unable to parse URI");
    }

    return std::unique_ptr<URI>(new URI(results[2]));
}
