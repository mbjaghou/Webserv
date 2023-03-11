/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:23:34 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/03/11 10:39:15 by mbjaghou         ###   ########.fr       */
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
    int bracket;
    int bracket1;
    
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

void pars::check_error(void)
{
	check_bracket(conf_file);
}

void pars::parsing_config(std::string line)
{
	int i = line.find_first_of("#");
	if (i >= 0)
		line.erase(i);
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

	int count = 0;
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

pars_server pars::parsing_servers(std::vector<std::string> conf, int *count)
{
	std::vector<std::string> tmp;
	pars_server server;
	
	tmp = ft_split(conf[0], " \t");
	if (tmp[1] != "{")
		throw std::runtime_error("must be add '{' or spase");
	std::vector<std::string>::iterator it = conf.begin() + (*count);
	if (it == conf.end())
		throw std::runtime_error("end of file");
	*it++;
	(*count)++;
	while (it != conf.end())
	{
		tmp = ft_split(*it, " ;");
		if (tmp[0] == "}")
		{
			std::cout << "end of server\n";
			break;
		}
		if (tmp[0] == "\tserver_name")
		{
			int i = 1;
			while (i < tmp.size())
			{
				server.server_name.push_back(tmp[i]);
				i++;
			}
		}
		else if (tmp[0] == "\tlisten")
		{
			if (tmp.size() != 2)
				throw std::runtime_error("listen must be add a port");
			std::vector<std::string> str = ft_split(tmp[1], ":");
			if (str.size() <= 2)
			{
				if (str.size() == 1)
				{
					server.address = "127.0.0.1";
					server.port = parssing_port(atol(str[0].c_str()));
				}
				else
				{
					server.address = str[0];
					server.port = parssing_port(atol(str[1].c_str()));;
				}
			}
				
		}
		else if (tmp[0] == "\troot")
		{
			if (tmp.size() == 2)
				server.root = tmp[1];
			else
				throw std::runtime_error("root must be add a path");
		}
		else if (tmp[0] == "\tindex")
		{
			int i = 1;
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
				throw std::runtime_error("error_page must be add a code between 100 and 599");
			if (tmp.size() == 3)
			{
				server.error_page.insert(std::make_pair(status, tmp[2]));
			}
			else
				throw std::runtime_error("error_page must be add a code and a path");
		}
		else if (tmp[0] == "\tmax_client_body_size")
		{
			if (tmp.size() == 2)
				server.max_client_body_size = atol(tmp[1].c_str());
			else
				throw std::runtime_error("Error in max_client_body_size");
		}
		else if (tmp[0] == "\tallowed_methods")
		{
			if (tmp.size() > 4)
				throw std::runtime_error("Error in allowed_methods");
			else
			{
				int i = 1;
				while (i < tmp.size())
				{
					server.allowed_methods.push_back(tmp[i]);
					i++;
				}
			}
		}
		else if (tmp[0] == "\tlocation")
		{
			std::cout << "location" << std::endl;
		}
		*it++;
		(*count)++;
		
	}
	return (server);
}


int pars::parssing_port(int port)
{
	if (port < 0 || port > 65535)
		throw std::invalid_argument("Error whit the port");
	return (port);
}
void pars::parsing(int ac, char **av)
{
	if (ac != 2)
        throw std::invalid_argument("Error whit the argment");
	open_file_read(av);
	check_error();
	stock_data();
	
}