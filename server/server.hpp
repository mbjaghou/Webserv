/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:21:49 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/03/20 18:56:42 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#define BUFFER 65000

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
        int server_accept;
        int server_recv;
        char buffer[BUFFER];
        
    public:
        //membre fuction
        std::vector<std::pair<int, sockaddr_in> > Server;
        std::multimap<std::string, long> 		  server_listen;
        server();
        int socket_server_start(void);
        int select_socket(fd_set read_fd, int max);
		void stock_address_port(pars pars);
        int start_server(pars pars);
		std::string recv_data(int socket, int &check);
};
#endif