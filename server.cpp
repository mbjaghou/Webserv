/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:22:52 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/02/11 16:39:26 by mbjaghou         ###   ########.fr       */
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
    server_lesten = listen(server_socket, 10);
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
    //fcntl(server_socket, F_SETFL, O_NONBLOCK);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(PORT);
    memset(addr.sin_zero, '\0', sizeof addr.sin_zero);
    bind_server();
    lesten_server();
    return (0);
}

void server::start_server()
{
    fd_set read_fd;

    const char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 14\n\nLife word Life";
    int i;

    socket_server_start();
    for(int i = 0; i < MAX_CONNECTION; i++)
        connection[i] = -1;
    
    connection[0] = server_socket;
    while (1)
    {
        FD_ZERO(&read_fd);
        for (i = 0; i < MAX_CONNECTION;++i)
        {
            if (connection[i] >= 0)
                FD_SET(connection[i], &read_fd);
        }
        if (!select_socket(read_fd))
        {
            if (FD_ISSET(server_socket, &read_fd))
            {
                if(!accept_server())
                {
                    for (i = 0; i < MAX_CONNECTION; ++i)
                    {
                        if (connection[i] < 0)
                        {
                            connection[i] = server_accept;
                            break ;
                        }
                    }
                }
               
            }
            for (i = 1; i < MAX_CONNECTION; ++i)
            {   
                if (connection[i] > 0 && FD_ISSET(connection[i], &read_fd))
                {
                    server_recv = recv(connection[i], buffer, BUFFER, 0);
                    if (server_recv == 0)
                    {
                        ::close(connection[i]);
                        std::cout << "\n=======================shutdown====================\n";
                        connection[i] = -1;
                    }
                    if (server_recv > 0)
                    {
                        write(1,buffer,strlen(buffer));
                    }
                    if (server_recv == -1)
                    {
                        std::cout << std::strerror(errno);
                        break;
                    }
                }
            }
        }
        send_client(hello);
    }
    for (int i = 0; i < MAX_CONNECTION; i++)
    {
        if (connection[i] > 0)
            ::close(connection[i]);
    }
}