/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:21:49 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/02/11 14:38:59 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#define PORT 8080
#define MAX_CONNECTION 50
#define BUFFER 999999

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <fcntl.h>

class server
{
    private:
        //attrbuite
        struct sockaddr_in addr;
        int server_socket;
        int server_bind;
        int server_lesten;
        int server_accept;
        int connection[MAX_CONNECTION];
        int server_select;
        ssize_t server_send;
        ssize_t server_recv;
        char buffer[BUFFER];
        
    public:
        //membre fuction
        server();
        ~server();
        int close(void);
        int socket_server_start(void);
        int bind_server(void);
        int lesten_server(void);
        int accept_server(void);
        int select_socket(fd_set read_fd);
        ssize_t send_client(const char *str);
        void start_server();
};
#endif