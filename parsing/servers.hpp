/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   servers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:06:15 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/03/10 13:17:56 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERS_HPP
#define SERVERS_HPP

#include <iostream>
#include <vector>
#include <map>

class pars_server
{
    public:
        std::vector<int> 			port;
        std::vector<std::string> 	root;
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
	void  						set_root(std::vector<std::string> root);
	std::vector<std::string>  	get_root(void);
    
    
    
};


#endif