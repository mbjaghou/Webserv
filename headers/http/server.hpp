/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:21:49 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/03/26 18:10:40 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#define BUFFER 1048576

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <fcntl.h>
#include <exception>
#include "./Request.hpp"
#include "./Response.hpp"
#include "../parsing_hpp/parsing.hpp"
#include <vector>
class server
{
    private:
        int server_accept;
        int server_recv;
    public:
        std::vector<std::pair<int, sockaddr_in> > Server;
        std::map<long, std::string> 		  server_listen;
        server();
        int socket_server_start(void);
        int select_socket(fd_set read_fd, int max);
		void stock_address_port(pars pars);
        int start_server(pars pars);
		std::string recv_data(int socket, int &check);
};
#endif