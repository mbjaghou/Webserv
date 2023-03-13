/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   servers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:06:05 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/03/13 13:25:58 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing_hpp/servers.hpp"

pars_server::pars_server()
{
	root = "";
	max_client_body_size = 0;
	autoindex = "";
}
pars_server::~pars_server(){
}

std::vector<std::string> pars_server::get_server_name(void)
{
    return (server_name);
}
std::vector<std::string> pars_server::get_index(void)
{
    return (index);
}
std::map<int, std::string>  pars_server::get_error_page(void)
{
    return (error_page);
}

long pars_server::get_max_client_body_size(void)
{
	return (max_client_body_size);
}


std::vector<std::string> pars_server::get_allowed_methods(void)
{
	return (allowed_methods);
}

std::string pars_server::get_autoindex(void)
{
	return (autoindex);
}
std::string  pars_server::get_root(void)
{
    return (root);
}

void pars_server::set_root(std::string root)
{
   this->root = root;
}
void pars_server::set_server_name(std::vector<std::string> server_name)
{
    this->server_name = server_name;
}
void pars_server::set_index(std::vector<std::string> index)
{
    this->index = index;
}
void pars_server::set_error_page(std::map<int, std::string>  error_page)
{
    this->error_page = error_page;
}

void pars_server::set_max_client_body_size(long max_client_body_size)
{
	this->max_client_body_size = max_client_body_size;
}

void pars_server::set_allowed_methods(std::vector<std::string> allowed_methods)
{
	this->allowed_methods = allowed_methods;
}

void pars_server::set_autoindex(std::string autoindex)
{
	this->autoindex = autoindex;
}