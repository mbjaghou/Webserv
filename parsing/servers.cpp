/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   servers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:06:05 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/03/11 11:07:58 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing_hpp/servers.hpp"



pars_server::pars_server()
{
	port = 0;
	root = "";
	address = "";
	max_client_body_size = 0;
}
pars_server::~pars_server(){}

long pars_server::get_port(void)
{
    return (port);
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

std::string  pars_server::get_root(void)
{
    return (root);
}
void pars_server::set_port(long port)
{
   this->port = port;
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