/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdou <aabdou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:03:29 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/12/13 20:44:57 by aabdou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../headers/http/Utils.hpp"

std::string ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string ft_trim(const std::string &s) {
    return rtrim(ltrim(s));
}

std::vector<std::string> ft_split(const std::string &str, const std::string &del) {
	std::vector<std::string> res;

	std::size_t pos = 0;
	std::size_t prev = 0;
	while ((pos = str.find(del, prev))!= std::string::npos) {
		if (str.substr(prev, pos - prev) != "")
			res.push_back(str.substr(prev, pos - prev));
		prev = pos + del.size();
	}
	if (str.substr(prev) != "")
		res.push_back(str.substr(prev));
	return res;
}

std::string getDate() {
	time_t		t_time;
	struct tm*	s_time;
	char		date[80];

	std::time(&t_time);
	if ((s_time = std::gmtime(&t_time)) == 0)
		throw std::runtime_error("getDate function failed");
	if (!std::strftime(date, 80, "%a, %d %b %Y %T GMT", s_time))
		throw std::runtime_error("getDate function failed");
	return date;
}

int	getFileLength(const std::string & filename) {
	try {
		std::ifstream	file(filename, std::ios::binary);
		file.seekg(0, std::ios::end);
		int len = file.tellg();
		return len == -1 ? 0 : len;
	}
	catch(...) {
		return 0;
	}
}

int		pathIsFile(const std::string& path) {
	struct stat s;
	if (stat(path.c_str(), &s) == 0 )
	{
		if (s.st_mode & S_IFDIR)
			return 0;
		else if (s.st_mode & S_IFREG)
			return 1;
		else
			return -1;
	}
	else
		return -1;
}

std::string	getMediaType(const std::string &subtype) {
	if (subtype == "aac") return "audio/aac";
	else if (subtype == "abw") return "application/x-abiword";
	else if (subtype == "arc") return "application/x-freearc";
	else if (subtype == "avif") return "image/avif";
	else if (subtype == "avi") return "video/x-msvideo";
	else if (subtype == "azw") return "application/vnd.amazon.ebook";
	else if (subtype == "bin") return "application/octet-stream";
	else if (subtype == "bmp") return "image/bmp";
	else if (subtype == "bz") return "application/x-bzip";
	else if (subtype == "bz2") return "application/x-bzip2";
	else if (subtype == "cda") return "application/x-cdf";
	else if (subtype == "csh") return "application/x-csh";
	else if (subtype == "css") return "text/css";
	else if (subtype == "csv") return "text/csv";
	else if (subtype == "doc") return "application/msword";
	else if (subtype == "docx") return "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
	else if (subtype == "eot") return "application/vnd.ms-fontobject";
	else if (subtype == "epub") return "application/epub+zip";
	else if (subtype == "gz") return "application/gzip";
	else if (subtype == "gif") return "image/gif";
	else if (subtype == "html") return "text/html";
	else if (subtype == "htm") return "text/html";
	else if (subtype == "ico") return "image/vnd.microsoft.icon";
	else if (subtype == "ics") return "text/calendar";
	else if (subtype == "jar") return "application/java-archive";
	else if (subtype == "jpeg") return "image/jpeg";
	else if (subtype == "jpg") return "image/jpeg";
	else if (subtype == "js") return "text/javascript";
	else if (subtype == "mjs") return "text/javascript";
	else if (subtype == "json") return "application/json";
	else if (subtype == "jsonld") return "application/ld+json";
	else if (subtype == "mid") return "audio/midi";
	else if (subtype == "midi") return "audio/midi";
	else if (subtype == "mp3") return "audio/mpeg";
	else if (subtype == "mp4") return "video/mp4";
	else if (subtype == "mpeg") return "video/mpeg";
	else if (subtype == "mpkg") return "application/vnd.apple.installer+xml";
	else if (subtype == "odp") return "application/vnd.oasis.opendocument.presentation";
	else if (subtype == "ods") return "application/vnd.oasis.opendocument.spreadsheet";
	else if (subtype == "odt") return "application/vnd.oasis.opendocument.text";
	else if (subtype == "oga") return "audio/ogg";
	else if (subtype == "ogv") return "video/ogg";
	else if (subtype == "ogx") return "application/ogg";
	else if (subtype == "opus") return "audio/opus";
	else if (subtype == "otf") return "font/otf";
	else if (subtype == "png") return "image/png";
	else if (subtype == "pdf") return "application/pdf";
	else if (subtype == "php") return "application/x-httpd-php";
	else if (subtype == "ppt") return "application/vnd.ms-powerpoint";
	else if (subtype == "pptx") return "application/vnd.openxmlformats-officedocument.presentationml.presentation";
	else if (subtype == "rar") return "application/vnd.rar";
	else if (subtype == "rtf") return "application/rtf";
	else if (subtype == "sh") return "application/x-sh";
	else if (subtype == "svg") return "image/svg+xml";
	else if (subtype == "tar") return "application/x-tar";
	else if (subtype == "tif") return "image/tiff";
	else if (subtype == "tiff") return "image/tiff";
	else if (subtype == "ts") return "video/mp2t";
	else if (subtype == "ttf") return "font/ttf";
	else if (subtype == "txt") return "text/plain";
	else if (subtype == "vsd") return "application/vnd.visio";
	else if (subtype == "wav") return "audio/wav";
	else if (subtype == "weba") return "audio/webm";
	else if (subtype == "webm") return "video/webm";
	else if (subtype == "webp") return "image/webp";
	else if (subtype == "woff") return "font/woff";
	else if (subtype == "woff2") return "font/woff2";
	else if (subtype == "xhtml") return "application/xhtml+xml";
	else if (subtype == "xls") return "application/vnd.ms-excel";
	else if (subtype == "xlsx") return "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
	else if (subtype == "xml") return "application/xml";
	else if (subtype == "xul") return "application/vnd.mozilla.xul+xml";
	else if (subtype == "zip") return "application/zip";
	else if (subtype == "3gp") return "video/3gpp";
	else if (subtype == "3g2") return "video/3gpp2";
	else if (subtype == "7z") return "application/x-7z-compressed";
	else return "";
}

std::string ReasonPhrase(int code) {
	switch (code) {
	case 100: return "Continue";
	case 101: return "Switching Protocols";
	case 102: return "Processing";
	case 103: return "Early Hints";

	case 200: return "OK";
	case 201: return "Created";
	case 202: return "Accepted";
	case 203: return "Non-Authoritative Information";
	case 204: return "No Content";
	case 205: return "Reset Content";
	case 206: return "Partial Content";
	case 207: return "Multi-Status";
	case 208: return "Already Reported";
	case 226: return "IM Used";

	case 300: return "Multiple Choices";
	case 301: return "Moved Permanently";
	case 302: return "Found";
	case 303: return "See Other";
	case 304: return "Not Modified";
	case 305: return "Use Proxy";
	case 307: return "Temporary Redirect";
	case 308: return "Permanent Redirect";

	case 400: return "Bad Request";
	case 401: return "Unauthorized";
	case 402: return "Payment Required";
	case 403: return "Forbidden";
	case 404: return "Not Found";
	case 405: return "Method Not Allowed";
	case 406: return "Not Acceptable";
	case 407: return "Proxy Authentication Required";
	case 408: return "Request Timeout";
	case 409: return "Conflict";
	case 410: return "Gone";
	case 411: return "Length Required";
	case 412: return "Precondition Failed";
	case 413: return "Payload Too Large";
	case 414: return "URI Too Long";
	case 415: return "Unsupported Media Type";
	case 416: return "Range Not Satisfiable";
	case 417: return "Expectation Failed";
	case 418: return "I'm a teapot";
	case 422: return "Unprocessable Entity";
	case 423: return "Locked";
	case 424: return "Failed Dependency";
	case 426: return "Upgrade Required";
	case 428: return "Precondition Required";
	case 429: return "Too Many Requests";
	case 431: return "Request Header Fields Too Large";
	case 451: return "Unavailable For Legal Reasons";

	case 500: return "Internal Server Error";
	case 501: return "Not Implemented";
	case 502: return "Bad Gateway";
	case 503: return "Service Unavailable";
	case 504: return "Gateway Time-out";
	case 505: return "HTTP Version Not Supported";
	case 506: return "Variant Also Negotiates";
	case 507: return "Insufficient Storage";
	case 508: return "Loop Detected";
	case 510: return "Not Extended";
	case 511: return "Network Authentication Required";

	default: return "";
	}
}
