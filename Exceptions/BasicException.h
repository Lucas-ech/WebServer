#ifndef BASICEXCEPTION_H
#define BASICEXCEPTION_H

#include <exception>
#include <string>

#include "ExceptionType.h"

template<ExceptionType Type>
class BasicException : public std::exception {

    public:
        explicit BasicException(std::string &message) : m_message(message) {}
        explicit BasicException(const char *message) : m_message(message) {}
        virtual ~BasicException() {}

        virtual const char* what() const noexcept {
            return m_message.c_str();
        }

    protected:
        std::string m_message;

};

#endif