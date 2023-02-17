/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:21:49 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/02/17 15:15:58 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#define PORT 8080
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

#include <vector>
class server
{
    private:
        //attrbuite
        struct sockaddr_in addr;
        std::vector<std::pair<int, sockaddr_in> > Serve;
        
        int server_socket;
        int server_bind;
        int server_lesten;
        int server_accept;
        int connection[FD_SETSIZE];
        int server_select;
        ssize_t server_send;
        ssize_t server_recv;
        char buffer[BUFFER];
        
    public:
        //membre fuction
        server();
        int socket_server_start(void);
        int select_socket(fd_set read_fd);
        int start_server();
};
#endif