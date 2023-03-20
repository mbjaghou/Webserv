/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   servers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:06:15 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/03/20 10:46:38 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERS_HPP
#define SERVERS_HPP

#include <iostream>
#include <vector>
#include <map>
#include "parse_location.hpp"

class pars_server
{
    public:
        std::string				 					root;
        std::vector<std::string> 					server_name;
        std::vector<std::string> 					index;
        std::map<int, std::string> 					error_page;
		int 										max_client_body_size;
		std::vector<std::string> 					allowed_methods;
		std::vector<location> 	 					location;
		bool 										autoindex;
		std::multimap<std::string, long>			listen;


		std::vector<std::string> 		get_server_name(void);
		std::vector<std::string> 		get_index(void);
		std::map<int, std::string>  	get_error_page(void);
		void        					set_server_name(std::vector<std::string> server_name);
		void        					set_index(std::vector<std::string> index);
		void        					set_error_page(std::map<int, std::string>  error_page);
		void  							set_root(std::string root);
		void  							set_max_client_body_size(long max_client_body_size);
		void  							set_allowed_methods(std::vector<std::string> allowed_methods);
		void  							set_autoindex(bool autoindex);
		bool 							get_autoindex(void);
		std::string  					get_root(void);
		long 							get_max_client_body_size(void);
		std::vector<std::string> 		get_allowed_methods(void);
		pars_server();
		~pars_server();
};


#endif