/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:23:34 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/02/18 15:37:58 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.hpp"

void pars::open_file_read(char **av)
{
    std::string line;
    std::fstream file(av[1]);
    

    if (file.is_open())
    {
        while (getline(file, line))
        {
            parsing_config(line);
        }
        file.close();
        // std::cout << "===== " << count_server << " ======\n";
    }
    else
        throw std::invalid_argument("bad Open File");
}

void pars::parsing_config(std::string line)
{
    if (int i = (!line.find("#")))
    {
        line.erase(i - 1);
    }
    if (!line.find("server" , 0, 6))
        count_server++;
    else if (!line.find("    server_name", 0 , 14))
    {
        std::string tmp = line.substr(15);
        server_name.push_back(tmp);
        
    }
    else if (!line.find("    listen", 0, 10))
    {
        std::string tmp = line.substr(11);
        tmp.erase(tmp.end() - 1);
        listen.push_back(tmp);
    }
    else if (!line.find("    root", 0, 8))
    {
        std::string tmp = line.substr(9);
        tmp.erase(tmp.end() - 1);
        root.push_back(tmp);
    }
    else if (!line.find("    error_page", 0, 14))
    {
        std::string tmp = line.substr(15);
        tmp.erase(tmp.end() - 1);
        error_page.push_back(tmp);
    }
    else if (!line.find("    index", 0, 9))
    {
        std::string tmp = line.substr(10);
        tmp.erase(tmp.end() - 1);
        index.push_back(tmp);
    }
    if (line[0] && line[0] != '\n')
        config.push_back(line);
}