/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:23:34 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/02/17 19:57:42 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.hpp"


void pars::parsing_config()
{
    
}

void pars::open_file_read(char **av)
{
    std::string line;
    std::fstream file(av[1]);
    int count_server;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            if (!line.find("server" , 0, 6))
                count_server++;
            if (!line.find("    server_name", 0 , 14))
            {
                std::string tmp = line.substr(15);
                server_name.push_back(tmp);
                
            }
            if (!line.find("    listen", 0, 10))
            {
                std::string tmp = line.substr(11);
                listen.push_back(tmp);
            }
            if (!line.find("    root", 0, 8))
            {
                std::string tmp = line.substr(9);
                root.push_back(tmp);
            }
            if (!line.find("    error_page", 0, 14))
            {
                std::string tmp = line.substr(15);
                error_page.push_back(tmp);
            }
            if (!line.find("    index", 0, 9))
            {
                std::string tmp = line.substr(10);
                index.push_back(tmp);
            }
            config.push_back(line);
        }
        file.close();
    }
    else
        throw std::invalid_argument("bad Open File");
}