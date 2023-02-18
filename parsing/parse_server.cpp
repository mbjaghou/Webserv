/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_server.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:06:05 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/02/18 17:14:37 by mbjaghou         ###   ########.fr       */
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