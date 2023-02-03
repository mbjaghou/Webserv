/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:22:52 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/02/03 17:24:14 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

// struct socklen_t   addrlen;

//int bind(int socket, const struct sockaddr *address, socklen_t address_len);
/* htonl converts a long integer (e.g. address) to a network representation */ 
/* htons converts a short integer (e.g. port) to a network representation */ 

// struct sockaddr_in 
// { 
//     __uint8_t         sin_len; 
//     sa_family_t       sin_family; 
//     in_port_t         sin_port; 
//     struct in_addr    sin_addr; 
//     char              sin_zero[8]; 
// };

server::server()
{
    std::cout << "Welcome to my server \n";
}

server::~server()
{
    std::cout << "God bye \n";
}

int server::socket_server(void)
{
    this->server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        std::cout << std::strerror(errno);
        close();
        return 1;
    }
    int enable = 1;
    if (setsockopt(this->server_socket , SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) == -1)
    {
        std::cerr << " setsockopt : " << strerror(errno) << '\n';
        exit(1);
    }
    return (0);
}
int server::bind_server(void)
{
    server_bind = bind(server_socket, (struct sockaddr *)&addr, sizeof(addr));
    if (server_bind < 0)
    {
        std::cout << std::strerror(errno);
        close();
        return 1;
    }
    return (0);
}
int server::lesten_server(void)
{
    server_lesten = listen(server_socket, 10);
    if (server_lesten < 0)
    {
        std::cout << std::strerror(errno);
        close();
        return 1;
    }
    return (0);
}
int server::accept_server(void)
{
    int addrlen = sizeof(addr);
    server_accept = accept(server_socket, (struct sockaddr *)&addr, (socklen_t*)&addrlen);
    if (server_accept < 0)
    {
        std::cout << std::strerror(errno);
        close();
        return 1;
    }
    return (0);
}

void server::close(void)
{
    ::close(server_socket);
    ::close(server_accept);
}

int server::read_server(char buffer[80000])
{
    server_read = read(server_accept , buffer, 80000);
    if (server_read < 0)
    {
        std::cout << std::strerror(errno);
        close();
        return 1;
    }
    return (0);
}