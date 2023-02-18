/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:23:34 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/02/18 19:54:40 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.hpp"

void pars::open_file_read(char **av)
{
    std::string line;
    std::fstream file(av[1]);
    int i = 0;

    count_server = 0;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            parsing_config(line);
        }
        while(tmp1[i])
        {
            if (tmp1[i] == 's' && tmp1[i + 1] == 'e' && tmp1[i + 2] == 'r' && tmp1[i + 3] == 'v' \
                && tmp1[i + 4] == 'e' && tmp1[i + 5] == 'r' && tmp1[i + 6] == ' ' && tmp1[i + 7] == '{')
            {
                ++count_server;
            }
            i++;
        }
        check_bracket(tmp1);
        check_error();
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
    if (!line.find("    server_name", 0 , 14))
    {
        std::string tmp = line.substr(15);
        tmp.erase(tmp.end() - 1);
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
    {
         tmp1 += line + "\n";
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
        throw std::runtime_error("duplicate");
}

void pars::check_error(void)
{
    int i = 0;
    while (i < count_server)
    {
        if (server_name[i].empty())
            throw std::runtime_error("Add server_name");
        else if (index[i].empty())
            throw std::runtime_error("Add index");
        else if (root[i].empty())
            throw std::runtime_error("Add root");
        else if (listen[i].empty())
            throw std::runtime_error("Add listen");
        else if (error_page[i].empty())
            throw std::runtime_error("Add error_page");
        i++;
        
    }
}