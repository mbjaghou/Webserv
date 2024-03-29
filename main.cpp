/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:32:23 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/03/27 22:37:00 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/http/server.hpp"
#include "exception"


int main(int ac, char **av)
{
    try
    {
		pars   pars;
		
		pars.parsing(ac, av);
        server serv;
        serv.start_server(pars);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return (0);
}