/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_server.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:06:05 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/02/18 19:28:18 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_server.hpp"


int pars_server::get_port(void)
{
    return (port);
}
std::string pars_server::get_server_name(void)
{
    return (server_name);
}
std::string pars_server::get_index(void)
{
    return (index);
}
std::string pars_server::get_error_page(void)
{
    return (error_page);
}

void pars_server::set_port(int port)
{
   this->port = port;
}
void pars_server::set_server_name(std::string server_name)
{
    this->server_name = server_name;
}
void pars_server::set_index(std::string index)
{
    this->index = index;
}
void pars_server::set_error_page(std::string error_page)
{
    this->error_page = error_page;
}