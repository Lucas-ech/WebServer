#include "PageRender.h"

PageRender::PageRender() {

}

PageRender::~PageRender() {

}

void PageRender::setTemplate(const Template &t) {
    m_content = t.getContent();
}

void PageRender::setStaticPage(const std::string &page) {
    m_content = FileOpener::readAll(page);
}

std::string PageRender::getContent() const {
    return m_content;
}
