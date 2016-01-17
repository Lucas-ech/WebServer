#ifndef URI_H
#define URI_H

#include <string>
#include <regex>

class URI {

    public:
        explicit URI(std::string uri);
        ~URI();
        std::string getUri() const;
        std::string getUrl() const;
        std::string getUrn() const;

    private:
        std::string findUrl();
        std::string findUrn();
        std::string m_uri;
        std::string m_url;
        std::string m_urn;

};

#endif