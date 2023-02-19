/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:23:34 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/02/19 17:05:35 by mbjaghou         ###   ########.fr       */
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
	int i = 0;
	
	int start_pos;
	int last_pos;
	
	while (conf_file[i])
	{
		pars_server config;
		start_pos = conf_file.find_first_not_of(" \t\n");
		if (start_pos == std::string::npos)
			std::cout << "Error\n";
		last_pos = conf_file.find_first_of(" \t\n");
		if (last_pos == std::string::npos)
			std::cout << "Error1\n";
		i++;
	}
	std::cout << start_pos << "    " << last_pos << std::endl;
}