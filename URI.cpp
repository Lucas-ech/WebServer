#include "URI.h"

URI::URI(std::string uri) :
m_uri(uri),
m_url(findUrl()),
m_urn(findUrn()) {

}

URI::~URI() {

}

std::string URI::getUri() const {
    return m_uri;
}

std::string URI::getUrl() const {
    return m_url;
}

std::string URI::getUrn() const {
    return m_urn;
}

std::string URI::findUrl() {
    std::regex url("([^?#]+)");
    std::smatch results;

    std::regex_search(m_uri, results, url);

    if (results.size() == 2) {
        return results[1];
    }
    return m_uri;
}

std::string URI::findUrn() {
    return m_uri.substr(m_url.size());
}
