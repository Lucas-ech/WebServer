#ifndef PAGERENDER_H
#define PAGERENDER_H

#include <string>

#include "Template.h"
#include "FileOpener.h"

class PageRender {

	public:
		PageRender();
		~PageRender();
		void setTemplate(const Template &t);
		void setStaticPage(const std::string page);
		std::string getContent() const;

	private:
		std::string m_content;

};

#endif