#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "BasicException.h"
#include "ExceptionType.h"

using NetworkException = BasicException<ExceptionType::NetworkException>;
using RenderException = BasicException<ExceptionType::RenderException>;
using RequestException = BasicException<ExceptionType::RequestException>;

#endif