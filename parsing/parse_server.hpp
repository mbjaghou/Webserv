/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_server.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:06:15 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/03/08 18:12:54 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_SERVER_HPP
#define PARSE_SERVER_HPP

#include <iostream>
#include <vector>
#include <map>

class pars_server
{
    private:

    public:
        std::vector<int> port;
        std::vector<std::string> 				root;
        std::vector<std::string> 	server_name;
        std::vector<std::string> 	index;
        std::vector<std::string> 	error_page;

	
    std::vector<int>							get_port(void);
    std::vector<std::string> 	get_server_name(void);
    std::vector<std::string> 	get_index(void);
    std::vector<std::string>  	get_error_page(void);
    void        				set_port(std::vector<int> port);
    void        				set_server_name(std::vector<std::string> server_name);
    void        				set_index(std::vector<std::string> index);
    void        				set_error_page(std::vector<std::string>  error_page);
    
    
    
};


#endif