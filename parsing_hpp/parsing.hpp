/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:23:56 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/03/12 17:22:58 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_HPP
#define PARSING_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <exception>

#include "servers.hpp"
#include "parse_location.hpp"

class pars
{
    public:
        std::vector<pars_server> parssing;
        std::string				 conf_file;
		pars();
		~pars();
		void pars_root();
        void open_file_read(char **av);
        void parsing_config(std::string line);
        void check_bracket(std::string str);
		void stock_data(void);
		void parsing(int ac, char **av);
		int parssing_port(int port);
		void check_content_if_empty(pars_server server);
		pars_server parsing_servers(std::vector<std::string> conf, int *count);
		location parssing_location(std::vector<std::string> conf, int *count);
    
};


#endif