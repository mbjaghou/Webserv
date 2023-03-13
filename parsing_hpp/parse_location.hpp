/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_location.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:16:39 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/03/13 19:47:37 by mbjaghou         ###   ########.fr       */
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
		std::string 					uploade_path;
        std::string 					root;
		std::vector<std::string> 		index;
		std::pair<int, std::string> 		return_page;
		std::vector<std::string> 		allowed_methods;
		bool							autoindex;
		long 							max_client_body_size;
		std::map<int, std::string> 		error_page;


		void set_uploade_path(std::string uploade_path);
		void set_root(std::string root);
		void set_index(std::vector<std::string> index);
		//void set_return_page(std::map<int, std::string> return_page);
		std::string get_uploade_path(void);
        std::string get_root(void);
		std::vector<std::string> get_index(void);
		//std::map<int, std::string> get_return_page(void);
		location();
		~location();
};

#endif