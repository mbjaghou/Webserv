/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:23:34 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/03/10 12:29:03 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.hpp"

std::vector<std::string> ft_split(std::string str , const char *c)
{
	std::vector<std::string> res;
	std::string tmp;
	int i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == c[0] || str[i] == c[1] || str[i] == c[2])
		{
			if (tmp != "")
				res.push_back(tmp);
			tmp = "";
		}
		else
			tmp += str[i];
	}
	if (tmp != "")
		res.push_back(tmp);
	return (res);
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
    while (int i = (line.find("#")) != std::string::npos)
    {
        line.erase(i - 1);
    }
	if (!line.find("server {", 0, 8))
			count_server++;
    if (line[0] && line[0] != '\n')
    {
         conf_file += line + "\n";
    }
}

void pars::open_file_read(char **av)
{
    std::string line;
    std::fstream file(av[1]);
    count_server = 0;

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
		throw std::runtime_error("Error in server");
	std::vector<std::string>::iterator it = conf.begin() + *count;
	// if (it == conf.end())
	// 	return (NULL);
	*it++;
	count++;
	while (it != conf.end())
	{
		tmp = ft_split(*it, " \t;");
		if (tmp[0] == "}")
		{
			std::cout << "test\n";
			break;
		}
		if (tmp[0] == "server_name")
		{
			std::cout << "server_name" << std::endl;
		}
		else if (tmp[0] == "listen")
		{
			std::cout << "listen" << std::endl;
		}
		else if (tmp[0] == "root")
		{
			std::cout << "root" << std::endl;
		}
		else if (tmp[0] == "error_page")
		{
			std::cout << "error_page" << std::endl;
		}
		else if (tmp[0] == "index")
		{
			std::cout << "index" << std::endl;
		}
		else if (tmp[0] == "location")
		{
			std::cout << "location" << std::endl;
		}
		else if (tmp[0] == "max_client_body_size")
		{
			std::cout << "max_client_body_size" << std::endl;
		}
		else if (tmp[0] == "allow_methods")
		{
			std::cout << "allow_methods" << std::endl;
		}
		*it++;
		count++;
		
	}
	return (server);
}


void pars::parsing(int ac, char **av)
{
	if (ac != 2)
        throw std::invalid_argument("Error whit the argment");
	open_file_read(av);
	check_error();
	stock_data();
}