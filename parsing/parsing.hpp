/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:23:56 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/02/18 15:37:51 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_HPP
#define PARSING_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <exception>

class pars
{
    public:
        std::vector<std::string> listen;
        std::vector<std::string> server_name;
        std::vector<std::string> config;
        std::vector<std::string> root;
        std::vector<std::string> index;
        std::vector<std::string> error_page;
        int count_server;

        void open_file_read(char **av);
        void parsing_config(std::string line);
    
};


#endif