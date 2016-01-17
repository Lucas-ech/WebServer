#include "WebServer.h"

WebServer::WebServer(unsigned short port, Router *router, OpenSSL *ssl) :
m_router(router),
m_done(false),
m_ssl(ssl) {
    m_network.bind(port);
    m_protocol = ssl == nullptr ? HTTP : HTTPS;
    m_catcher = std::unique_ptr<std::thread>(new std::thread(&WebServer::requestCatcher, this));
}

WebServer::~WebServer() {
    m_done = true;
    m_catcher->join();

    if (m_ssl != nullptr) {
         delete m_ssl;
    }
}

void WebServer::requestCatcher() {
    using std::get;

    char buffer[1000];
    RequestInfo reqInfo;

    while (m_done == false) {
        if (m_network.listen(reqInfo)) {
            std::unique_ptr<Request> request(new Request(get<0>(reqInfo), get<1>(reqInfo)));
            try {
                if (m_protocol == HTTPS) {
                    request->setHttps(m_ssl->getContext());
                }

                if (request->receive(buffer, sizeof(buffer))) {
                    std::string header(buffer);
                    std::unique_ptr<URI> uri = HttpHeader::parseURI(header);
                    request->setUri(std::move(uri));

                    if (m_router->route(*request)) {
                        if (request->isSentBack() == false) {
                            request->error(500);
                        }
                    } else {
                        request->error(404);
                    }
                }
            } catch (const NetworkException& e) {
                //Ignoring
            } catch (const RequestException& e) {
                //Ignoring
            } catch (const RenderException& e) {
                request->error(500);
            }
        }
        std::this_thread::sleep_for (std::chrono::milliseconds(2));
    }
}
