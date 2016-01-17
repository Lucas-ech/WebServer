#include "Network.h"

Network::Network(): m_socketId(-1), m_bound(false) {

}

Network::~Network() {
    if (m_bound && m_socketId > 0) {
        ::close(m_socketId);
    }
}

void Network::bind(const int port) {
    createSocket();
    m_srcInfo.sin_family = AF_INET;
    m_srcInfo.sin_addr.s_addr = INADDR_ANY;
    m_srcInfo.sin_port = htons(port);
    if (::bind(m_socketId, reinterpret_cast<sockaddr*>(&m_srcInfo), sizeof(m_srcInfo)) < 0) {
        throw NetworkException("Unable to bind");
    }
    m_bound = true;

    if (::listen(m_socketId, 1) < 0) {
        throw NetworkException("Unable to listen");
    }
}

bool Network::listen(RequestInfo &requestInfo) {
    if (m_bound == false) {
        throw std::logic_error("You need to bind first");
    }

    unsigned int srcSize = sizeof(m_srcInfo);
    int newSocket = ::accept(m_socketId, reinterpret_cast<sockaddr*>(&m_srcInfo), &srcSize);

    // There is no new connection
    if (errno == EAGAIN) {
        //Reset errno
        errno = 0;
        return false;
    } else if (newSocket < 0) {
        throw NetworkException("Unable to call accept()");
    }

    requestInfo = std::make_tuple(newSocket, m_srcInfo);

    return true;
}

void Network::connect(const char *ipAddr, const int port) {
    createSocket();
    m_dstInfo.sin_family = AF_INET;
    m_dstInfo.sin_addr.s_addr = inet_addr(ipAddr);
    m_dstInfo.sin_port = htons(port);
    if (::connect(m_socketId, reinterpret_cast<sockaddr*>(&m_dstInfo), sizeof(m_dstInfo)) < 0) {
        throw NetworkException("Unable to connect");
    }
}

void Network::createSocket() {
    m_socketId = ::socket(AF_INET, SOCK_STREAM, 0);
    if (m_socketId < 0) {
        throw NetworkException("Socket creation failed");
    }

    //Setting listening in no-blocking mode
    int flags = fcntl(m_socketId, F_GETFL, 0);
    fcntl(m_socketId, F_SETFL, flags | O_NONBLOCK);

    flags = fcntl(m_socketId, F_GETFL, 0);
    if ((flags & O_NONBLOCK) != O_NONBLOCK) {
        throw NetworkException("Unable to set listening in no-blocking mode");
    }
}