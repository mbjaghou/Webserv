/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   servers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:06:15 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/03/10 20:49:34 by mbjaghou         ###   ########.fr       */
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
        long 						port;
        std::string				 	root;
        std::vector<std::string> 	server_name;
        std::vector<std::string> 	index;
        std::map<int, std::string> 	error_page;
		std::string 				address; 
	
	pars_server();
	~pars_server();
    long							get_port(void);
    std::vector<std::string> 	get_server_name(void);
    std::vector<std::string> 	get_index(void);
    std::map<int, std::string>  	get_error_page(void);
    void        				set_port(long port);
    void        				set_server_name(std::vector<std::string> server_name);
    void        				set_index(std::vector<std::string> index);
    void        				set_error_page(std::map<int, std::string>  error_page);
	void  						set_root(std::string root);
	std::string  	get_root(void);
    
    
    
};


#endif