/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:23:56 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/02/19 15:45:52 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_HPP
#define PARSING_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <exception>

#include "parse_server.hpp"

class pars
{
    public:
        std::vector<std::string> listen;
        std::vector<std::string> server_name;
        std::vector<std::string> root;
        std::vector<std::string> index;
        std::vector<std::string> error_page;
        int count_server;

        std::vector<pars_server> parssing;
        std::string				conf_file;

        void open_file_read(char **av);
        void parsing_config(std::string line);
        void check_bracket(std::string str);
        void check_error(void);
		void stock_data(void);
    
};


#endif