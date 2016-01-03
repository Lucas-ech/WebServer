#ifndef URI_H
#define URI_H

#include <string>
#include <map>

class URI {

	public:
		URI(std::string uri);
		~URI();
		std::string getHostname();
		const std::map<std::string, std::string>& getArguments();
		std::string getUri() const;
		std::string getUrl() const;
		std::string getUrn() const;

	private:
		std::string findUrl();
		std::string findUrn();
		const std::map<std::string, std::string>& findArguments();
		std::string m_uri;
		std::string m_url;
		std::string m_urn;
		std::string m_hostname;
		std::map<std::string, std::string> m_arguments;

};

#endif