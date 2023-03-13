/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:32:03 by ylabtaim          #+#    #+#             */
/*   Updated: 2023/03/13 19:59:04 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "codes.hpp"
#include <iostream>
#include <map>
#include <vector>
#include "../parsing_hpp/parsing.hpp"
class Request {
private:
	int									_Status;
	std::string 						_Buffer;
	std::string							_Method;
	std::string							_Path;
	std::string							_Query;
	std::map<std::string, std::string>	_Headers;
	std::map<std::string, std::string>	_QueryMap;
	std::vector<std::string>			_Body;
	std::string							_Host;
	const pars_server*					_Server;
	std::map<int, std::string>			_ErrorPage;
	std::string							_Index;
	bool								_AutoIndex;
	const location*				_Location;

public:
	Request(std::string & buffer, pars const &config);
	~Request();
    Request() {};

	void RequestParsing();
	void ParseStartLine(std::string & str);
	void ParseHeaders(std::vector<std::string> & headers);
	void ParseChunckedBody(std::string &body);
	void ParseBody(std::string &body);
	void ParseQuery(std::string & query);

	const std::map<std::string, std::string> &getHeaders() const;
	const int &getStatus() const;
	const std::string &getPath() const;
	const std::string &getHost() const;
	const std::string &getIndex() const;
	const std::map<int, std::string> &getErrorPage() const;
	bool getAutoIndex() const;

	void updatePath(const std::string & path);
	void checkMethod(const std::string & path);
	bool findServer(std::vector<pars_server> const & servers, std::string &buffer);
	// const ServerContext& GetServerBlock() const;
	const std::vector<std::string>& GetBody() const;
	// const LocationContext &GetLocation() const;
	const std::string &GetMethod() const;
	const std::string &GetQuery() const;
	const std::vector<std::string> &getBody() const;
};
