/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_location.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:18:29 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/03/25 00:19:09 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing_hpp/parse_location.hpp"

location::location()
{
	root = "";
	autoindex = false;
	return_page = std::make_pair(0, "");
	count_autoindex = 0;
}

location::~location()
{
}

void location::set_location_path(std::string location_path)
{
	this->location_path = location_path;
}

void location::set_root(std::string root)
{
	this->root = root;
}

void location::set_index(std::vector<std::string> index)
{
	this->index = index;
}

std::string location::get_location_path(void)
{
	return (location_path);
}

std::vector<std::string> location::get_index(void)
{
	return (index);
}

std::string location::get_root(void)
{
    return (root);
}

