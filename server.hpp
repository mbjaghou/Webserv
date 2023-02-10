/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:21:49 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/02/10 14:24:54 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#define PORT 8080
#define MAX_CONNECTION 50
#define BUFFER 1024

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
        
    public:
    server();
    ~server();
    struct sockaddr_in addr;
    int close(void);
    int socket_server_start(void);
    int read_server(char buffer[BUFFER]);
    int server_socket;
    int server_bind;
    int bind_server(void);
    int server_lesten;
    int lesten_server(void);
    int server_accept;
    int accept_server(void);
    long server_read;
    int connection[MAX_CONNECTION];
    int server_select;
    int select_socket(fd_set read_fd);
    ssize_t send_client(const char *str);
    ssize_t server_send;
    ssize_t server_recv;

};
#endif