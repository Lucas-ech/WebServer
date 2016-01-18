#include <chrono>
#include <thread>
#include <functional>

#include "Router.h"
#include "WebServer.h"
#include "Log.h"
#include "OpenSSL.h"
#include "RequestHandler.h"

int main()
{
    using namespace std::placeholders;

    Router router;
    //router.connect("/", std::bind(RequestHandler::file, "www/index.html", _1));
    //router.connect("/*", std::bind(RequestHandler::directory, "www/", "/", _1));

    //OpenSSL ssl("cert.pem", "privkey.pem", "fullchain.pem");

    Log::write("Listening to port ", 8080);
    WebServer webserver(8080, &router/*, &ssl*/);

    while (true) {
        std::this_thread::sleep_for (std::chrono::seconds(1));
    }

    return 0;
}
