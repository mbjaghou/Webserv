/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:23:34 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/02/17 18:28:48 by mbjaghou         ###   ########.fr       */
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
                server_name.push_back(line);
            if (!line.find("    listen", 0, 10))
                listen.push_back(line);
            if (!line.find("    root", 0, 8))
                root.push_back(line);
            if (!line.find("    root", 0, 8))
                root.push_back(line);
            if (!line.find("    error_page", 0, 14))
                error_page.push_back(line);
            if (!line.find("    index", 0, 9))
                index.push_back(line);
            config.push_back(line);
        }
    }
    else
        throw std::invalid_argument("bad Open File");
}