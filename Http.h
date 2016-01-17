#ifndef HTTP_H
#define HTTP_H

#include <map>
#include <string>
#include <iostream>

namespace Http {
	const std::map<unsigned int, std::string> Status = {
		{200, "200 OK"},
	    {201, "201 Created"},
	    {202, "202 Accepted"},
	    {204, "204 No Content"},
	    {206, "206 Partial Content"},
	    {301, "301 Moved Permanently"},
	    {302, "302 Moved Temporarily"},
	    {303, "303 See Other"},
	    {304, "304 Not Modified"},
	    {307, "307 Temporary Redirect"},
	    {400, "400 Bad Request"},
	    {401, "401 Unauthorized"},
	    {402, "402 Payment Required"},
	    {403, "403 Forbidden"},
	    {404, "404 Not Found"},
	    {405, "405 Not Allowed"},
	    {406, "406 Not Acceptable"},
	    {408, "408 Request Time-out"},
	    {409, "409 Conflict"},
	    {410, "410 Gone"},
	    {411, "411 Length Required"},
	    {412, "412 Precondition Failed"},
	    {413, "413 Request Entity Too Large"},
	    {414, "414 Request-URI Too Large"},
	    {415, "415 Unsupported Media Type"},
	    {416, "416 Requested Range Not Satisfiable"},
	    {500, "500 Internal Server Error"},
	    {501, "501 Not Implemented"},
	    {502, "502 Bad Gateway"},
	    {503, "503 Service Temporarily Unavailable"},
	    {504, "504 Gateway Time-out"},
	    {507, "507 Insufficient Storage"},
	};
}

namespace Mime {
	const std::map<std::string, const char*> Type = {
		{"html", "text/html; charset=UTF-8"},
		{"js", "text/javascript"},
		{"css", "text/css"},
		{"bin", "application/octet-stream"},
		{"exe", "application/octet-stream"},
		{"pdf", "application/pdf"},
		{"latex", "application/x-latex"},
		{"sh", "application/x-sh"},
		{"tex", "application/x-tex"},
		{"zip", "application/zip"},
		{"tar", "application/x-tar"},
		{"wav", "audio/x-wav"},
		{"gif", "image/gif"},
		{"jpeg", "image/jpeg"},
		{"jpg", "image/jpeg"},
		{"jpe", "image/jpeg"},
		{"tiff", "image/tiff"},
		{"tif", "image/tiff"},
		{"pnm", "image/x-portable-anymap"},
		{"pbm", "image/x-portable-bitmap"},
		{"pgm", "image/x-portable-graymap"},
		{"ppm", "image/x-portable-pixmap"},
		{"txt", "text/plain"},
		{"etx", "text/x-setext"},
		{"mpeg", "video/mpeg"},
		{"mpg", "video/mpeg"},
		{"mpe", "video/mpeg"},
		{"mp3", "audio/mp3"},
		{"mp4", "flac/mp4"},
		{"flac", "flac/flac"},
		{"qt", "video/quicktime"},
		{"mov", "video/quicktime"},
		{"avi", "video/x-msvideo"},
		{"cgi", "magnus-internal/cgi"},
	};
}

#endif