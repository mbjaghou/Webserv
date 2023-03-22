/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:23:34 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/03/22 17:18:01 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing_hpp/parsing.hpp"

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
		throw std::runtime_error("Error: find another char after ';' Or ';' is missing");
    if (line[0] && line[0] != '\n')
    {
         conf_file += line + "\n";
    }
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
        throw std::invalid_argument("bad Open File");
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
		count++;	
	}
}

int pars::parssing_port(int port)
{
	if (port <= 0 || port > 65535)
		throw std::invalid_argument("Error whit the port");
	return (port);
}

location pars::parssing_location(std::vector<std::string> conf, size_t *count, pars_server server)
{
	std::vector<std::string> str = ft_split(conf[*count], " \t");
	location loc;

	if (str[2] != "{")
		throw std::runtime_error("Error must be add '{' or spase");
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
					throw std::runtime_error("Error root is duplicate location");
				else
					loc.root = tmp[1];
			}
			else
				throw std::runtime_error("Error in root location");
		}
		else if (tmp[0] == "index")
		{
			if (loc.index.size() != 0)
				throw std::runtime_error("Error index is duplicate location");
			if (tmp.size() == 1)
				throw std::runtime_error("Error in index location");
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
				throw std::runtime_error("Error in allowed_methods in location");
			else
			{
				if (loc.allowed_methods.size() != 0)
					throw std::runtime_error("Error in allowed_methods is duplicate location");
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
				throw std::runtime_error("Error return is duplicate location");
			int status = atol(tmp[1].c_str());
			if (status < 301 || status > 308)
				throw std::runtime_error("Error in satatus code");
			if (tmp.size() == 3)
			{
				loc.return_page = std::make_pair(status, tmp[2]);
			}
			else
				throw std::runtime_error("Error in return");
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
					throw std::runtime_error("Error in autoindex you must be add 'on' or 'off' in location");
			}
			else
				throw std::runtime_error("Error in autoindex in location");
		}
		else if (tmp[0] == "max_client_body_size")
		{
			if (atol(tmp[1].c_str()) < 0)
				throw std::runtime_error("Error in max_client_body_size location");
			if (tmp.size() == 2)
				loc.max_client_body_size = atol(tmp[1].c_str());
			else
				throw std::runtime_error("Error in max_client_body_size location");
		}
		else if (tmp[0] == "error_page")
		{
			int status = atol(tmp[1].c_str());
			if (status < 100 || status > 599)
				throw std::runtime_error("Error in satatus code location");
			if (tmp.size() == 3)
			{
				loc.error_page.insert(std::make_pair(status, tmp[2]));
			}
			else
				throw std::runtime_error("Error in error_page location");
		}
		else if (tmp[0] == "cgi_path")
		{
			if (loc.cgi_path.size() != 0)
				throw std::runtime_error("Error cgi_path is duplicate location");
			if (tmp.size() != 2)
				throw std::runtime_error("Error in cgi_path location");
			else
				loc.cgi_path = tmp[1];
			
		}
		else if (tmp[0] == "cgi_script")
		{
			if (loc.cgi_script.size() != 0)
				throw std::runtime_error("Error cgi_script is duplicate location");
			if (tmp.size() != 2)
				throw std::runtime_error("Error in cgi_script location");
			else
			{
				size_t pos = tmp[1].find('.');
				loc.cgi_extension = tmp[1].substr(pos);
				loc.cgi_script = tmp[1];
			}
			
		}
		else
			throw std::runtime_error("Error: bad location");
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
		throw std::runtime_error("Error must add cgi_path or cgi_script");
	return (loc);
}

pars_server pars::parsing_servers(std::vector<std::string> conf, size_t *count)
{
	std::vector<std::string> tmp;
	pars_server server;
	
	tmp = ft_split(conf[0], " \t");
	if (tmp[1] != "{")
		throw std::runtime_error("Error must be add '{' or spase");
	(*count)++;
	std::vector<std::string>::iterator it = conf.begin() + (*count);
	if (it == conf.end())
		throw std::runtime_error("end of file");
	while (it != conf.end())
	{
		tmp = ft_split(*it, " ;");
		if (tmp[0] == "}")
			break;
		if (tmp[0] == "\tserver_name")
		{
			if (server.server_name.size() != 0)
				throw std::runtime_error("Error server_name is duplicate");
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
				throw std::runtime_error("Error in listen");
			std::vector<std::string> str = ft_split(tmp[1], ":");
			if (str.size() <= 2)
			{
				if (str.size() == 1)
				{
					if (str[0].find(".") != std::string::npos)
						throw std::runtime_error("Error in listen");
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
					throw std::runtime_error("Error root is duplicate");
				else
					server.root = tmp[1];
			}
			else
				throw std::runtime_error("Error in root");
		}
		else if (tmp[0] == "\tindex")
		{
			if (server.index.size() != 0)
				throw std::runtime_error("Error index is duplicate");
			if (tmp.size() == 1)
				throw std::runtime_error("Error in index");
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
				throw std::runtime_error("Error in satatus code");
			if (tmp.size() == 3)
			{
				server.error_page.insert(std::make_pair(status, tmp[2]));
			}
			else
				throw std::runtime_error("Error in error_page");
		}
		else if (tmp[0] == "\tmax_client_body_size")
		{
			if (atol(tmp[1].c_str()) < 0)
				throw std::runtime_error("Error in max_client_body_size");
			if (tmp.size() == 2)
				server.max_client_body_size = atol(tmp[1].c_str());
			else
				throw std::runtime_error("Error in max_client_body_size");
		}
		else if (tmp[0] == "\tallowed_methods")
		{
			if (tmp.size() > 4 || tmp.size() == 1)
				throw std::runtime_error("Error in allowed_methods");
			else
			{
				if (server.allowed_methods.size() != 0)
					throw std::runtime_error("Error in allowed_methods is duplicate");
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
					throw std::runtime_error("Error in autoindex you must be add 'on' or 'off'");
			}
			else
				throw std::runtime_error("Error in autoindex");
		}
		else if (tmp[0] == "\tlocation")
		{
			int move_step = *count;
			server.location.push_back(parssing_location(conf, count, server));
			it += *count - move_step;
		}
		else
			throw std::runtime_error("Error in server");
		*it++;
		(*count)++;
		
	}
	check_content_if_empty(server);
	return (server);
}

void pars::check_content_if_empty(pars_server server)
{
	if (server.listen.size() == 0)
		throw std::runtime_error("must be add listen");	
}

void pars::parsing(int ac, char **av)
{
	if (ac == 1)
	{
		std::cout << "config file not found, use default config file" << std::endl;
		av[1] = (char *)"./config_files/config.conf"; 
		ac++;
	}
	if (ac != 2)
        throw std::invalid_argument("Error whit the argment");
	open_file_read(av);
	check_bracket(conf_file);
	stock_data();
}