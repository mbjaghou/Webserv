/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_server.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:06:15 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/02/18 19:28:07 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_SERVER_HPP
#define PARSE_SERVER_HPP

#include <iostream>


class pars_server
{
    private:
        int port;
        std::string root;
        std::string server_name;
        std::string index;
        std::string error_page;
    public:

    int get_port(void);
    std::string get_server_name(void);
    std::string get_index(void);
    std::string get_error_page(void);
    void set_port(int port);
    void set_server_name(std::string server_name);
    void set_index(std::string index);
    void set_error_page(std::string error_page);
    
    
    
};


#endif