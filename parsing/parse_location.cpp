/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_location.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:18:29 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/03/12 12:13:19 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing_hpp/parse_location.hpp"

location::location()
{
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

void location::set_return_page(std::map<int, std::string> return_page)
{
	this->return_page = return_page;
}

void location::set_autoindex(std::string autoindex)
{
	this->autoindex = autoindex;
}

std::string location::get_uploade_path(void)
{
	return (uploade_path);
}

std::vector<std::string> location::get_index(void)
{
	return (index);
}

std::map<int, std::string> location::get_return_page(void)
{
	return (return_page);
}

std::string location::get_autoindex(void)
{
	return (autoindex);
}

std::string location::get_root(void)
{
    return (root);
}