/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:21:49 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/02/08 19:06:29 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#define PORT 8080
#define MAX_CONNECTION 50
#define BUFFER 80000

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
    void close(void);
    int socket_server_start(void);
    int read_server(char buffer[80000]);
    int server_socket;
    int server_bind;
    int bind_server(void);
    int server_lesten;
    int lesten_server(void);
    int server_accept;
    int accept_server(void);
    long server_read;

};
#endif