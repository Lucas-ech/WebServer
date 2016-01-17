#ifndef OPENSSL_H
#define OPENSSL_H

#include <stdexcept>
#include <openssl/ssl.h>

class OpenSSL {

    public:
        OpenSSL(std::string cert, std::string privKey, std::string chain = "");
        ~OpenSSL();
        SSL_CTX* getContext();

    private:
        void createContext();
        void configureContext(std::string cert, std::string privKey, std::string chain);
        SSL_CTX* m_ctx;


};

#endif