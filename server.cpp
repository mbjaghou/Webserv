/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:22:52 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/02/10 14:37:11 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

server::server()
{
    std::cout << "Welcome to my server \n";
}

server::~server()
{
    std::cout << "God bye \n";
    close();
}

int server::socket_server_start(void)
{
    this->server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        std::cout << std::strerror(errno);
        close();
    }
    int i = 1;
    setsockopt(server_socket , SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i));
    // fcntl(server_socket, F_SETFL, O_NONBLOCK);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(PORT);
    memset(addr.sin_zero, '\0', sizeof addr.sin_zero);
    bind_server();
    lesten_server();
    return (0);
}
int server::bind_server(void)
{
    server_bind = bind(server_socket, (struct sockaddr *)&addr, sizeof(addr));
    if (server_bind < 0)
    {
        std::cout << std::strerror(errno);
        close();
    }
    return (0);
}
int server::lesten_server(void)
{
    server_lesten = listen(server_socket, 3);
    if (server_lesten < 0)
    {
        std::cout << std::strerror(errno);
        close();
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

int server::close(void)
{
    ::close(server_socket);
    ::close(server_accept);
    return (1);
}

int server::read_server(char buffer[BUFFER])
{
    server_read = read(server_accept , buffer, BUFFER);
    if (server_read < 0)
    {
        std::cout << std::strerror(errno);
        close();
    }
    return (0);
}
int server::select_socket(fd_set read_fd)
{
    server_select = select(FD_SETSIZE, &read_fd, NULL, NULL, NULL);
    if (server_select < 0)
    {
        std::cout << std::strerror(errno);
        close();
    }
    return (0);
}
ssize_t server::send_client(const char *str)
{
    server_send = send(server_accept, str, strlen(str), 0);
    if (server_send < 0)
    {
        std::cout << std::strerror(errno);
        close();
    }
    return (0);

}