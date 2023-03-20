/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_location.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:18:29 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/03/20 12:46:10 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing_hpp/parse_location.hpp"

location::location()
{
	root = "";
	autoindex = "";
	return_page = std::make_pair(0, "");
	max_client_body_size = 1;
}

location::~location()
{
}

void location::set_uploade_path(std::string uploade_path)
{
	this->uploade_path = uploade_path;
}

void location::set_root(std::string root)
{
	this->root = root;
}

void location::set_index(std::vector<std::string> index)
{
	this->index = index;
}

std::string location::get_uploade_path(void)
{
	return (uploade_path);
}

std::vector<std::string> location::get_index(void)
{
	return (index);
}

std::string location::get_root(void)
{
    return (root);
}

