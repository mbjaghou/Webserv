/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:23:34 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/03/08 18:12:17 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.hpp"

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
        check_error();
		stock_data();
        file.close();
    }
    else
        throw std::invalid_argument("bad Open File");
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

void pars::stock_data(void)
{
	// stock the data from config file in the vector of class pars_server
	
	int i = -1;
	while (++i < count_server)
	{
		pars_server server;
		if (conf_file.find("server {", 0, 8) != std::string::npos)
		{
			std::string tmp;
			tmp = conf_file.substr(conf_file.find("listen", 0, 6), conf_file.find(";", 0, 1));
			int port = atoi(tmp.c_str());
			server.port.push_back(port);
			std::string server_name = conf_file.substr(conf_file.find("server_name", 0, 11), conf_file.find(";", 0, 1));
			server.server_name.push_back(server_name);
			std::string  root = conf_file.substr(conf_file.find("root", 0, 4), conf_file.find(";", 0, 1));
			server.root.push_back(root);
			std::string  index = conf_file.substr(conf_file.find("index", 0, 5), conf_file.find(";", 0, 1));
			server.index.push_back(index);
			std::string  error_page = conf_file.substr(conf_file.find("error_page", 0, 10), conf_file.find(";", 0, 1));
			server.error_page.push_back(error_page);
		}
		parssing.push_back(server);
	}
}