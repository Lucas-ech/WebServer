#include "Template.h"

Template::Template(std::string templateName) :
m_template(FileOpener::readAll("templates/" + templateName + ".html"))
{

}

Template::~Template() {

}

void Template::bind(std::string variable, std::string value) {
	std::size_t pos(0);
	std::string templateVariable = '%' + variable + '%';
	while((pos = m_template.find(templateVariable, pos)) != std::string::npos) {
		m_template.replace(pos, templateVariable.length(), value);
	}
}

void Template::bind(const std::map<const std::string, const std::string> &values) {
	for(const auto &key : values) {
		bind(key.first, key.second);
	}
}


std::string Template::getContent() const {
	return m_template;
}
