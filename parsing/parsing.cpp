/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:23:34 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/03/23 15:56:50 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing_hpp/parsing.hpp"

pars::~pars(){}
pars::pars(){}
std::vector<std::string> ft_split(const std::string &str, const char *del) {
	std::vector<std::string> res;
	std::size_t pos = 0;
	std::size_t prev = 0;
	while ((pos = str.find_first_of(del, prev))!= std::string::npos) {
		if (str.substr(prev, pos - prev) != "")
			res.push_back(str.substr(prev, pos - prev));
		prev = pos + 1;
	}
	if (str.substr(prev) != "")
		res.push_back(str.substr(prev));
	return res;
}

void pars::check_bracket(std::string str)
{
    int bracket = 0;
    int bracket1 = 0;
    
    int i = -1;
    while (str[++i] != '\0')
    {
        if (str[i] == '{')
            bracket++;
        else if (str[i] == '}')
            bracket1++;            
    }
    if (bracket1 == bracket)
        return ;
    else
        throw std::runtime_error("bracket is missing");
}

void pars::parsing_config(std::string line)
{
	int i = line.find_first_of("#");
	if (i >= 0)
		line.erase(i);
	i = 0;
	for(; line[i] == ' ' || line[i] == '\t'; i++);
	if(line[i] == '\0' || line[i] == '\n')
		line.erase(0);
	
	i = line.size() - 1;
	for(; line[i] == ' ' || line[i] == '\t'; i--);
	line.erase(i + 1);
	
	size_t j = line.find_last_of(";{}");
	if (j != line.size() - 1)
		throw std::runtime_error("end of line must be either ';' or '}' or '{'");
    if (line[0] && line[0] != '\n')
         conf_file += line + "\n";
}

void pars::open_file_read(char **av)
{
    std::string line;
    std::fstream file(av[1]);

    if (file && file.is_open())
    {
        while (getline(file, line))
        {
            parsing_config(line);
        }
        file.close();
    }
    else
        throw std::invalid_argument("Could not open file");
}

void pars::stock_data(void)
{
	std::vector<std::string> config;
	config = ft_split(conf_file, "\n");

	if (config.end() == config.begin())
		throw std::runtime_error("Error: config file is empty");
	size_t count = 0;
	while (count < config.size())
	{
		std::vector<std::string> tmp = ft_split(config[count], " \t");
		if (tmp[0] == "server")
		{
			pars_server server = parsing_servers(config, &count);
			parssing.push_back(server);
		}
		else
			throw std::runtime_error("Server block must start with \"server\"");
		count++;	
	}
}

int pars::parssing_port(int port)
{
	if (port <= 0 || port > 65535)
		throw std::invalid_argument("invalid port");
	return (port);
}

location pars::parssing_location(std::vector<std::string> conf, size_t *count, pars_server server)
{
	std::vector<std::string> str = ft_split(conf[*count], " \t");
	location loc;

	if (str[2] != "{")
		throw std::runtime_error("location's line must end with '{'");
	loc.uploade_path = str[1];
	(*count)++;
	std::vector<std::string>::iterator it = conf.begin() + (*count);
	if (it == conf.end())
		throw std::runtime_error("end of file");
	while (it != conf.end())
	{
		std::vector<std::string> tmp = ft_split(*it, " ;\t");
		if (tmp[0] == "}")
			break;
		else if (tmp[0] == "root")
		{
			if (tmp.size() == 2)
			{
				if (loc.root.size() != 0)
					throw std::runtime_error("root is duplicated in location " + str[1]);
				else
					loc.root = tmp[1];
			}
			else
				throw std::runtime_error("root in " + str[1] + " should take only one argument");
		}
		else if (tmp[0] == "index")
		{
			if (loc.index.size() != 0)
				throw std::runtime_error("index is duplicated in location" + str[1]);
			if (tmp.size() == 1)
				throw std::runtime_error("the index directive in location " + str[1] + " needs arguments");
			size_t i = 1;
			while (i < tmp.size())
			{
				loc.index.push_back(tmp[i]);
				i++;
			}
		}
		else if (tmp[0] == "allowed_methods")
		{
			if (tmp.size() > 4 || tmp.size() == 1)
				throw std::runtime_error("invalid number of arguments in allowed_methods in location " + str[1]);
			else
			{
				if (loc.allowed_methods.size() != 0)
					throw std::runtime_error("allowed_methods is duplicated in location " + str[1]);
				size_t i = 1;
				while (i < tmp.size())
				{
					loc.allowed_methods.push_back(tmp[i]);
					i++;
				}
			}
		}
		else if (tmp[0] == "return")
		{
			if (loc.return_page.first != 0 && loc.return_page.second.size() != 0)
				throw std::runtime_error("return is duplicated in location " + str[1]);
			int status = atol(tmp[1].c_str());
			if (status < 301 || status > 308)
				throw std::runtime_error("invalid status code of return directive in location " + str[1]);
			if (tmp.size() == 3)
				loc.return_page = std::make_pair(status, tmp[2]);
			else
				throw std::runtime_error("invalid number of arguments for return in location " + str[1]);
		}
		else if (tmp[0] == "autoindex")
		{
			if (tmp.size() == 2)
			{
				if (tmp[1] == "on")
					loc.autoindex = true;
				else if (tmp[1] == "off")
					loc.autoindex = false;
				else
					throw std::runtime_error("invalid argument for autoindex in location " + str[1]);
			}
			else
				throw std::runtime_error("invalid number of arguments for autoindex in location " + str[1]);
		}
		else if (tmp[0] == "max_client_body_size")
		{
			if (atol(tmp[1].c_str()) < 0)
				throw std::runtime_error("max_client_body_size is negative in location " + str[1]);
			if (tmp.size() == 2)
				loc.max_client_body_size = atol(tmp[1].c_str());
			else
				throw std::runtime_error("invalid number of arguments for max_client_body_size in location " + str[1]);
		}
		else if (tmp[0] == "error_page")
		{
			int status = atol(tmp[1].c_str());
			if (status < 100 || status > 599)
				throw std::runtime_error("invalid status code for error_page in location " + str[1]);
			if (tmp.size() == 3)
				loc.error_page.insert(std::make_pair(status, tmp[2]));
			else
				throw std::runtime_error("invalid number of arguments for error_page in location " + str[1]);
		}
		else if (tmp[0] == "cgi_path")
		{
			if (loc.cgi_path.size() != 0)
				throw std::runtime_error("cgi_path is duplicated in location " + str[1]);
			if (tmp.size() != 2)
				throw std::runtime_error("invalid number of arguments for cgi_path in location " + str[1]);
			else
				loc.cgi_path = tmp[1];			
		}
		else if (tmp[0] == "cgi_script")
		{
			if (loc.cgi_script.size() != 0)
				throw std::runtime_error("cgi_script is duplicated in location " + str[1]);
			if (tmp.size() != 2)
				throw std::runtime_error("invalid number of arguments for cgi_script in location " + str[1]);
			else
			{
				size_t pos = tmp[1].find('.');
				loc.cgi_extension = tmp[1].substr(pos);
				loc.cgi_script = tmp[1];
			}			
		}
		else
			throw std::runtime_error("invalid directive in location " + str[1]);
		*it++;
		(*count)++;
	}
	loc = check_content_of_location(loc, server);
	return (loc);
}

location pars::check_content_of_location(location loc, pars_server server)
{
	if (loc.root.size() == 0 && server.root.size() != 0)
			loc.root = server.root;
	if (loc.index.size() == 0 && server.index.size() != 0)
		loc.index = server.index;
	if (loc.allowed_methods.size() == 0 && server.allowed_methods.size() != 0)
		loc.allowed_methods = server.allowed_methods;
	if (loc.max_client_body_size == 1 && server.max_client_body_size != 1)
		loc.max_client_body_size = server.max_client_body_size;
	if (loc.error_page.size() == 0 && server.error_page.size() != 0)
		loc.error_page = server.error_page;
	if ((loc.cgi_path.size() == 0 && loc.cgi_script.size() != 0) || (loc.cgi_path.size() != 0  &&loc.cgi_script.size() == 0))
		throw std::runtime_error("missing cgi_path or cgi_script");
	return (loc);
}

pars_server pars::parsing_servers(std::vector<std::string> conf, size_t *count)
{
	std::vector<std::string> tmp;
	pars_server server;

	(*count)++;
	std::vector<std::string>::iterator it = conf.begin() + (*count);
	while (it != conf.end())
	{
		tmp = ft_split(*it, " ;");
		if (tmp[0] == "}")
			break;
		if (tmp[0] == "\tserver_name")
		{
			if (server.server_name.size() != 0)
				throw std::runtime_error("server_name is duplicated");
			size_t i = 1;
			while (i < tmp.size())
			{
				server.server_name.push_back(tmp[i]);
				i++;
			}
		}
		else if (tmp[0] == "\tlisten")
		{
			if (tmp.size() != 2)
				throw std::runtime_error("listen takes only one argument");
			std::vector<std::string> str = ft_split(tmp[1], ":");
			if (str.size() <= 2)
			{
				if (str.size() == 1)
				{
					if (str[0].find(".") != std::string::npos)
						throw std::runtime_error("in listen");
					server.listen.insert(std::make_pair("127.0.0.1",  parssing_port(atol(str[0].c_str()))));
				}
				else
				{
					if (str[0] == "localhost")
						server.listen.insert(std::make_pair("127.0.0.1", parssing_port(atol(str[1].c_str()))));
					else
						server.listen.insert(std::make_pair(str[0], parssing_port(atol(str[1].c_str()))));
				}
			}
				
		}
		else if (tmp[0] == "\troot")
		{
			if (tmp.size() == 2)
			{
				if (server.root.size() != 0)
					throw std::runtime_error("Error: root is duplicated");
				else
					server.root = tmp[1];
			}
			else
				throw std::runtime_error("root takes only one argument");
		}
		else if (tmp[0] == "\tindex")
		{
			if (server.index.size() != 0)
				throw std::runtime_error("index is duplicated");
			if (tmp.size() == 1)
				throw std::runtime_error("the index directive needs arguments");
			size_t i = 1;
			while (i < tmp.size())
			{
				server.index.push_back(tmp[i]);
				i++;
			}
		}
		else if (tmp[0] == "\terror_page")
		{
			int status = atol(tmp[1].c_str());
			if (status < 100 || status > 599)
				throw std::runtime_error("invalid satatus code");
			if (tmp.size() == 3)
				server.error_page.insert(std::make_pair(status, tmp[2]));
			else
				throw std::runtime_error("error_page takes only one argument");
		}
		else if (tmp[0] == "\tmax_client_body_size")
		{
			if (atol(tmp[1].c_str()) < 0)
				throw std::runtime_error("max_client_body_size must be a positive value");
			if (tmp.size() == 2)
				server.max_client_body_size = atol(tmp[1].c_str());
			else
				throw std::runtime_error("max_client_body_size takes only one argument");
		}
		else if (tmp[0] == "\tallowed_methods")
		{
			if (tmp.size() > 4 || tmp.size() == 1)
				throw std::runtime_error("allowed_methods accepts up to 3 arguments");
			else
			{
				if (server.allowed_methods.size() != 0)
					throw std::runtime_error("allowed_methods is duplicated");
				size_t i = 1;
				while (i < tmp.size())
				{
					server.allowed_methods.push_back(tmp[i]);
					i++;
				}
			}
		}
		else if (tmp[0] == "\tautoindex")
		{
			if (tmp.size() == 2)
			{
				if (tmp[1] == "on")
					server.autoindex = true;
				else if (tmp[1] == "off")
					server.autoindex = false;
				else
					throw std::runtime_error("autoindex accepts only 'on' or 'off' as argument");
			}
			else
				throw std::runtime_error("autoindex takes only one argument");
		}
		else if (tmp[0] == "\tlocation")
		{
			int move_step = *count;
			server.location.push_back(parssing_location(conf, count, server));
			it += *count - move_step;
		}
		else
			throw std::runtime_error("invalid directive in the server block");
		*it++;
		(*count)++;
		
	}
	check_content_if_empty(server);
	return (server);
}

void pars::check_content_if_empty(pars_server server)
{
	if (server.listen.size() == 0)
		throw std::runtime_error("listen directive is missing");
}

void pars::parsing(int ac, char **av)
{
	if (ac == 1)
	{
		std::cout << "config file not found, default config file used" << std::endl;
		av[1] = (char *)"./config_files/config.conf"; 
		ac++;
	}
	if (ac != 2)
        throw std::invalid_argument("You should provide one argument");
	open_file_read(av);
	check_bracket(conf_file);
	stock_data();
}