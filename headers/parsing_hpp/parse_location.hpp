/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_location.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:16:39 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/03/25 00:55:36 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_LOCATION_HPP
#define PARSE_LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>

class location
{
    public:
		std::string 					location_path;
        std::string 					root;
		std::vector<std::string> 		index;
		std::pair<int, std::string> 	return_page;
		std::vector<std::string> 		allowed_methods;
		bool							autoindex;
		std::map<int, std::string> 		error_page;
		std::string 					cgi_path;
		std::string 					cgi_script;
		std::string 					upload_store;
		int 							count_autoindex;

		void set_location_path(std::string location_path);
		void set_root(std::string root);
		void set_index(std::vector<std::string> index);
		std::string get_location_path(void);
        std::string get_root(void);
		std::vector<std::string> get_index(void);
		location();
		~location();
};

#endif