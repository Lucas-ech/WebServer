#include "Request.h"

Request::Request(int socketId, const sockaddr_in socketInfo) :
m_socketId(socketId),
m_sentBack(false),
m_ipAddr(inet_ntoa(socketInfo.sin_addr)),
m_isHttps(false),
m_ssl(nullptr)
{
    // Setting HTML content as default
    m_headers.setContentType("text/html");
}

Request::~Request() {
    close();
}

bool Request::receive(char *buffer, unsigned int buffsize) {
    int charNumber;
    if (isHttps()) {
        charNumber = SSL_read(m_ssl, buffer, buffsize);
    } else {
        charNumber = ::recv(getSocketId(), buffer, buffsize, 0);
    }
    if (charNumber > 0) {
        buffer[charNumber] = 0;
        return true;
    }
    return false;
}

void Request::send(const std::string &data, int httpStatus) {
    using namespace std::literals::string_literals;

    m_headers.setStatus(httpStatus);
    m_headers.setContentLength(data.length());

    std::string request = m_headers.getHeader() + data;

    if (isHttps()) {
        if (SSL_write(m_ssl, request.c_str(), request.size()) <= 0) {
            throw NetworkException("An error occured during sending");
        }
    } else {
        if (::send(m_socketId, request.c_str(), request.size(), 0) < 0) {
            throw NetworkException("An error occured during sending");
        }
    }
    m_sentBack = true;
}

void Request::send(const PageRender &page, int httpStatus) {
    send(page.getContent(), httpStatus);
}


void Request::error(int httpStatus) {
    Template t("error");
    t.bind(
        {
            {"errno", std::to_string(httpStatus)}
        }
    );
    setHeader("Content-Type", "text/html; charset=UTF-8");
    send(t.getContent(), httpStatus);
}

void Request::close() {
    if (m_socketId >= 0) {
        ::close(m_socketId);
    }
    if (isHttps()) {
        SSL_free(m_ssl);
    }
}

void Request::setHeader(std::string key, std::string value) {
    m_headers.setHeader(key, value);
}

bool Request::isSentBack() const {
    return m_sentBack;
}

unsigned int Request::getSocketId() const {
    return m_socketId;
}

std::string Request::getIpAddress() const {
    return m_ipAddr;
}

void Request::setUri(std::unique_ptr<URI> uri) {
    m_uri = std::move(uri);
}

const URI& Request::getUri() const {
    return *m_uri;
}

std::string Request::getUrl() const {
    return m_uri->getUrl();
}

void Request::setHttps(SSL_CTX *ctx) {
    m_ssl = SSL_new(ctx);
    SSL_set_fd(m_ssl, m_socketId);

    if (SSL_accept(m_ssl) <= 0) {
        throw NetworkException("Unable to set request as SSL");
    }
    m_isHttps = true;
}

bool Request::isHttps() const {
    return m_isHttps;
}
