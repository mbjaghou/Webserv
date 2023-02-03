/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:21:49 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/02/03 17:26:17 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#define PORT 8080

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

class server
{
    private:
        
    public:
    server();
    ~server();
    struct sockaddr_in addr;
    void close(void);
    int socket_server(void);
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