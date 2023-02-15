/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:22:52 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/02/15 20:28:23 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

server::server()
{
    std::cout << "Welcome to my server \n";
}

int server::bind_server(void)
{
    server_bind = bind(server_socket, (struct sockaddr *)&addr, sizeof(addr));
    if (server_bind < 0)
    {
        std::cout << "\033[32m" <<  std::strerror(errno) << "\033[0m" << std::endl;
        ::close(server_socket);
        return (1);
    }
    return (0);
}

int server::lesten_server(void)
{
    server_lesten = listen(server_socket, SOMAXCONN);
    if (server_lesten < 0)
    {
        std::cout << "\033[32m" <<  std::strerror(errno) << "\033[0m" << std::endl;
        ::close(server_socket);
        return (1);
    }
    return (0);
}

int server::select_socket(fd_set read_fd)
{
    server_select = select(FD_SETSIZE, &read_fd, NULL, NULL, NULL);
    if (server_select < 0)
    {
        std::cout << "\033[32m" <<  std::strerror(errno)  << " select" << "\033[0m" << std::endl;
        return (1);
    }
    return (0);
}

int server::socket_server_start(void)
{
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        std::cout << "\033[32m" <<  std::strerror(errno) << "\033[0m" << std::endl;
        return (1);
    }
    int i = 1;
    if ((setsockopt(server_socket , SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i))) < 0)
        return (1);
    fcntl(server_socket, F_SETFL, O_NONBLOCK);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(PORT);
    memset(addr.sin_zero, '\0', sizeof addr.sin_zero);
    if (bind_server())
        return (1);
    if (lesten_server())
        return (1);
    return (0);
}

int server::start_server()
{
    fd_set read_fd;
    int i;
    int addrlen = sizeof(addr);
    const char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 14\n\nLife word Life";
    
    if (socket_server_start())
        return (1);
    for(i = 0; i < FD_SETSIZE; i++)
         connection[i] = -1;
    connection[0] = server_socket;
    while (1)
    {
        FD_ZERO(&read_fd);
        for (i = 0; i < FD_SETSIZE;++i)
        {
            if (connection[i] >= 0)
                FD_SET(connection[i], &read_fd);
        }
        if (!select_socket(read_fd))
        {
            if (FD_ISSET(server_socket, &read_fd))
            {
                if((server_accept = accept(server_socket, (struct sockaddr *)&addr, (socklen_t*)&addrlen)) >= 0)
                {
                    setsockopt(server_accept , SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i));
                    for (i = 0; i < FD_SETSIZE; ++i)
                    {
                        if (connection[i] < 0)
                        {
                            connection[i] = server_accept;
                            break ;
                        }
                    }
                }
            }
            for (i = 1; i < FD_SETSIZE; ++i)
            {   
                if (connection[i] > 0 && FD_ISSET(connection[i], &read_fd))
                {
                    server_recv = recv(connection[i], buffer, BUFFER, 0);
                    if (server_recv == 0)
                    {
                        ::close(connection[i]);
                        connection[i] = -1;
                    }
                    if (server_recv > 0)
                    {
                        write(1,buffer,strlen(buffer));
                    }
                }
            }
        }
        server_send = send(server_accept, hello, strlen(hello), 0);
    }
    for (i = 0; i < FD_SETSIZE; i++)
    {
        if (connection[i] > 0)
        {
            FD_CLR(connection[i], &read_fd);
            ::close(connection[i]);
        }
    }
}