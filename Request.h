#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <stdexcept>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <unistd.h>
#include <tuple>
#include <deque>
#include <sstream>
#include <memory>

#include "URI.h"
#include "Http.h"
#include "HttpHeader.h"
#include "PageRender.h"
#include "Template.h"
#include "Exceptions/Exception.h"

using RequestInfo = std::tuple<int, sockaddr_in>;

class Request {

    public:
        Request(int socketId, const sockaddr_in socketInfo);
        ~Request();
        bool receive(char *buffer, unsigned int buffsize);
        void send(const std::string &data, int httpStatus = 200);
        void send(const PageRender &page, int httpStatus = 200);
        void error(int httpStatus);
        void close();
        void setHeader(std::string key, std::string value);
        bool isSentBack() const;
        unsigned int getSocketId() const;
        std::string getIpAddress() const;
        void setUri(std::unique_ptr<URI> uri);
        const URI& getUri() const;
        std::string getUrl() const;
        void setSocketId(unsigned int socketId);
        void setSocketInfo(const sockaddr_in socketInfo);
        void setHttps(SSL_CTX *ctx);
        bool isHttps() const;

    private:
        int m_socketId;
        bool m_sentBack;
        std::string m_ipAddr;
        std::unique_ptr<URI> m_uri;
        bool m_isHttps;
        SSL *m_ssl;
        HttpHeader m_headers;

};

#endif
