#include "OpenSSL.h"

OpenSSL::OpenSSL(std::string cert, std::string privKey) : m_ctx(nullptr) {
	SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();

    createContext();
    configureContext(cert, privKey);
}

OpenSSL::~OpenSSL() {
    EVP_cleanup();
    SSL_CTX_free(m_ctx);
}

SSL_CTX* OpenSSL::getContext() {
    return m_ctx;
}

void OpenSSL::createContext() {
    const SSL_METHOD *method;
    method = SSLv23_server_method();

    m_ctx = SSL_CTX_new(method);
    if (!m_ctx) {
    	throw std::runtime_error("Unable to create SSL context");
    }
}

void OpenSSL::configureContext(std::string cert, std::string privKey)
{
    SSL_CTX_set_ecdh_auto(m_ctx, 1);

    // Set the key and cert
    if (SSL_CTX_use_certificate_file(m_ctx, cert.c_str(), SSL_FILETYPE_PEM) != 1) {
    	throw std::runtime_error("Unable to load certificate");
    }

    if (SSL_CTX_use_PrivateKey_file(m_ctx, privKey.c_str(), SSL_FILETYPE_PEM) != 1) {
    	throw std::runtime_error("Unable to load private key");
    }
}