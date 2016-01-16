#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "FileOpener.h"

class Template {

	public:
		explicit Template(std::string templateName);
		~Template();
		void bind(std::string variable, std::string value);
		void bind(const std::map<const std::string, const std::string> &values);
		std::string getContent() const;

	private:
		std::string m_template;

};

#endif