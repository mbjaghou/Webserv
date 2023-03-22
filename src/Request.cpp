/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachehbo <yachehbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:32:18 by ylabtaim          #+#    #+#             */
/*   Updated: 2023/03/22 18:03:08 by yachehbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../headers/http/Request.hpp"
#include "./../headers/http/Utils.hpp"



Request::Request(std::string &buffer, pars const &config) : _Status(OK), _Buffer(buffer) {
	if (findServer(config.parssing, _Buffer) == false) {
		_Status = BadRequest;
		return ;
	}
	RequestParsing();
}

Request::~Request() {}

void Request::RequestParsing() {
	std::vector<std::string> req = ft_split(_Buffer, "\r\n\r\n");

	if (req.size() >= 1) {
		std::vector<std::string> headers = ft_split(req[0], "\r\n");
		for (std::size_t i = 0; i < headers.size(); ++i)
			std::replace(headers[i].begin(), headers[i].end(), '\r', ' ');
		ParseStartLine(headers[0]);
		if (_Status != OK) return ;
		ParseHeaders(headers);
		if (_Status != OK) return ;
		if (req.size() >= 2) {
			std::string body;
			for (size_t i = 1; i < req.size(); ++i) {
				body.append(req[i]);
				if (i != req.size() - 1)
					body.append("\r\n\r\n");
			}
			if ((body.size() > _Server->max_client_body_size * 1000000)){
				_Status = PayloadTooLarge;
				return ;
			}
			if (_Headers["Transfer-Encoding"] == "chunked") {
				if (_Headers.find("Content-Length") != _Headers.end()) {
					_Status = BadRequest;
					return ;
				}
				ParseChunckedBody(body);
			}
			else
				ParseBody(body);
		}
	}
}

bool	Request::findServer(std::vector<pars_server> const & servers, std::string &buffer) {
	std::size_t begin = buffer.find("Host");
	if (begin == std::string::npos)
		return false;
	std::size_t end = buffer.find("\r\n", begin);
	if (end == std::string::npos)
        return false;
	_Host = ft_trim(buffer.substr(begin + 5 , end - begin - 5));
	if (_Host.empty())
		return false;

	for (std::size_t i = 0; i < servers.size(); ++i) {
		std::multimap<std::string, long> listeners = servers[i].listen;
		std::multimap<std::string, long>::iterator it;
		for (it = listeners.begin(); it!= listeners.end(); ++it) {
			std::stringstream str;
			str << it->second;
			std::string host = it->first + ":" + str.str();
			if ((host == _Host) || (it->first == _Host && it->second == 80)) {
				_Server = &servers[i];
				return true;
			}
			else {
				std::size_t pos = _Host.find(":");
				if (pos != std::string::npos) {
					std::string host = _Host.substr(0, pos);
					int port = atoi(_Host.substr(pos + 1, _Host.size() - pos).c_str());
					for (size_t j = 0; j < servers[i].server_name.size(); j++) {
						if (servers[i].server_name[j] == host) {
							for (std::multimap<std::string, long>::const_iterator it = servers[i].listen.begin(); it != servers[i].listen.end(); ++it) {
								if (port == it->second) {
									_Server = &servers[i];
									return true;
								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}

void Request::updatePath(const std::string & path) {
	std::vector<location> locations = _Server->location;

	_Path = path;
	std::size_t i;
	bool enter = false;
	for (i = 0; i < locations.size(); ++i){
		enter = true;
		if (!strncmp(locations[i].uploade_path.c_str(), path.c_str(), locations[i].uploade_path.size())) {
			if (locations[i].return_page.first != 0 && locations[i].uploade_path == path) {
				_Status = locations[i].return_page.first;
				_Headers["Location"] = locations[i].return_page.second;
			}
			else if (!locations[i].root.empty()) {
				if (strncmp(locations[i].root.c_str(), path.c_str(), locations[i].root.size()))
					_Path = locations[i].root + path;
			}
			if (!locations[i].index.empty()) {
				for (std::size_t j = 0; j < locations[i].index.size(); ++j) {
					std::string fullPath;
					if (!locations[i].return_page.second.empty())
						fullPath = locations[i].return_page.second + path + '/' + locations[i].index[j];
					else if (!locations[i].root.empty())
						fullPath = locations[i].root + path + '/' + locations[i].index[j];
					if (pathIsFile(fullPath) == 1) {
						_Index = fullPath;
						break ;
					}
				}
			}
			if (!locations[i].error_page.empty())
				_ErrorPage = locations[i].error_page;
			if (locations[i].autoindex && _Index == "")
				_AutoIndex = true;
			else
				_AutoIndex = false;
			_Location = &_Server->location[i];
		}
	}
	if(enter == false)
		_Location = NULL;
}

void Request::checkMethod(const std::string &path) {
	if (_Method != "GET" && _Method != "POST" && _Method != "DELETE")
		_Status = NotImplemented;

	bool methodIsAllowed = false;
	std::vector<location> locations = _Server->location;
	std::vector<std::string> methods;

	for (std::size_t i = 0; i < locations.size(); ++i) {
		if (path == locations[i].uploade_path) {
			methods = locations[i].allowed_methods;
			break ;
		}
	}
	if (methods.size() == 0) {
		methodIsAllowed = true;
	} else {
		for (std::size_t i = 0; i < methods.size(); ++i) {
			if (_Method == methods[i]) {
				methodIsAllowed = true;
				break ;
			}
		}
	}
	if (methodIsAllowed == false)
	    _Status = MethodNotAllowed;
}

void Request::ParseStartLine(std::string & str) {
	std::vector<std::string> StartLine = ft_split(str, " ");

	if (StartLine.size() == 3) {
		_Method = StartLine[0];
		checkMethod(StartLine[1]);
		if (_Status != OK) return ;
		if (StartLine[1].size() > 2000)
			_Status = URITooLong;
		std::vector<std::string> RequestTarget = ft_split(StartLine[1], "?");
		updatePath(RequestTarget[0]);
		if (_Status >= 300 && _Status < 400) return;
		if (pathIsFile(_Path) == 1) {
			std::fstream check(_Path);
			if (!check.good())
				_Status = Forbidden;
		}
		else if (pathIsFile(_Path) == 0) {
			DIR *dir = opendir(_Path.c_str());
			if (dir == NULL)
                _Status = Forbidden;
			else
				closedir(dir);
		}
		else
            _Status = NotFound;
		_Query = RequestTarget.size() == 2 ? RequestTarget[1] : "";
		if (_Query != "")
			ParseQuery(_Query);
		if (StartLine[2] != "HTTP/1.1")
			_Status = HTTPVersionNotSupported;
	}
	else
		_Status = BadRequest;
}

void Request::ParseQuery(std::string & query) {
	std::vector<std::string> QueryPairs = ft_split(query, "&");
	std::size_t pos;
	for (std::size_t i = 0; i < QueryPairs.size(); ++i) {
		pos = QueryPairs[i].find("=");
		if (pos != std::string::npos)
			_QueryMap[QueryPairs[i].substr(0, pos)] = QueryPairs[i].substr(pos + 1, QueryPairs[i].length());
		else
			_QueryMap[QueryPairs[i]] = "";
	}
}

void Request::ParseHeaders(std::vector<std::string> & headers) {
	for (std::size_t i = 1; i < headers.size() && !headers[i].empty(); ++i) {
		std::size_t pos = headers[i].find(":");
		if (pos == std::string::npos || (headers[i][pos - 1] && std::isspace(headers[i][pos - 1]))) {
			_Status = BadRequest;
			return ;
		}
		_Headers[headers[i].substr(0, pos)] = ft_trim(headers[i].substr(pos + 1, headers[i].length()));
	}
	if (_Headers.find("Host") == _Headers.end()) {
		_Status = BadRequest;
		return ;
	}
	if (_Headers["Transfer-Encoding"] == "chunked" && _Headers.find("Content-Length") != _Headers.end())
		_Status = BadRequest;
}

void Request::ParseChunckedBody(std::string &body) {
	std::vector<std::string> tmpBody = ft_split(body, "\r\n");
	std::size_t size;
	std::stringstream ss;

	for (std::size_t i = 0; i < tmpBody.size(); ++i) {
		if ((i % 2) == 0) {
			ss.clear();
			ss << std::hex << tmpBody[i];
			ss >> size;
		}
		else {
			if (size != tmpBody[i].size()) {
				_Status = BadRequest;
				return ;
			}
			else
				_Body.push_back(tmpBody[i]);
		}
	}
}

void Request::ParseBody(std::string &body) {
	std::size_t bodySize;
	std::stringstream ss;
	if (_Headers.find("Content-Length") != _Headers.end()) {
		ss << _Headers["Content-Length"];
		ss >> bodySize;
		if (bodySize != body.size()) {
			_Status = BadRequest;
			return ;
		}
	}
	if (body.size())
		_Body.push_back(body.substr(0, bodySize));
}

const std::map<std::string, std::string> &Request::getHeaders() const {
	return _Headers;
}

const int &Request::getStatus() const {
	return _Status;
}

const std::string &Request::getPath() const {
	return _Path;
}

const std::string &Request::getHost() const {
	return _Host;
}

const std::map<int, std::string> &Request::getErrorPage() const {
	return _ErrorPage;
}

const std::string &Request::getIndex() const {
	return _Index;
}

bool Request::getAutoIndex() const {
	return _AutoIndex;
}

const std::vector<std::string>& Request::GetBody() const {
	return _Body;
}

const std::string &Request::GetMethod() const {
	return _Method;
}
const std::string &Request::GetQuery() const {
	return _Query;
}
const std::vector<std::string> &Request::getBody() const {
	return _Body;
}

const location *Request::getLocation() const
{
	return _Location;
}
const std::string Request::getPort() const {
	return _Host.substr(_Host.find(":") + 1);
}

const std::string Request::getIp() const {
	return _Host.substr(0, _Host.find(":"));
}

const pars_server* Request::getServer() const
{
	return _Server;
}
