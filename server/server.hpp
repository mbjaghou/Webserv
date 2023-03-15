/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:21:49 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/03/15 18:07:26 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#define BUFFER 50000

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <fcntl.h>
#include <exception>
#include "./../headers/http/Request.hpp"
#include "./../headers/http/Response.hpp"
#include "../parsing_hpp/parsing.hpp"
#include <vector>
class server
{
    private:
        //attrbuite
        struct sockaddr_in addr;
        int server_socket;
        int server_accept;
        ssize_t server_send;
        ssize_t server_recv;
        char buffer[BUFFER];
        
    public:
        //membre fuction
        std::vector<std::pair<int, sockaddr_in> > Server;
        std::multimap<std::string, long> 		  server_listen;
        server();
        int socket_server_start(void);
        int select_socket(fd_set read_fd);
		void stock_address_port(pars pars);
        int start_server(pars pars);
};
#endif