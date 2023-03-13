/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:22:52 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/03/13 20:00:51 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

server::server()
{
    std::cout << "\033[32m" << "Welcome to my server" << "\033[0m" << std::endl;
}

int server::select_socket(fd_set read_fd)
{
    server_select = select(FD_SETSIZE, &read_fd, NULL, NULL, NULL);
    if (server_select < 0)
    {
        throw std::invalid_argument(strerror(errno));
        return (1);
    }
    return (0);
}

int server::socket_server_start(void)
{
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        throw std::invalid_argument(strerror(errno));
    int opt = 1;
    if ((setsockopt(server_socket , SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) < 0)
       throw std::invalid_argument("Error address socket is already used");
    fcntl(server_socket, F_SETFL, O_NONBLOCK);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(PORT);
    memset(addr.sin_zero, '\0', sizeof addr.sin_zero);
    if (( server_bind = bind(server_socket, (struct sockaddr *)&addr, sizeof(addr))) < 0)
    {
        throw std::invalid_argument(strerror(errno));
        ::close(server_socket);
    }
    if (( server_lesten = listen(server_socket, SOMAXCONN)) < 0)
    { 
        throw std::invalid_argument(strerror(errno));
        ::close(server_socket);
    }
    return (0);
}

int server::start_server()
{
    fd_set read_fd;
    int i;
    int addrlen = sizeof(addr);
    const char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 14\n\nLife word Life";

    std::string response;
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
						// write(1, buffer, strlen(buffer));
                        std::string tmp = buffer;
                        Request o(tmp);
                        std::cout << o.getStatus() << '\n';
                        Response res(o);
                        response = res.sendFile("/Users/mbjaghou/Desktop/Webserv/server/main.cpp");
                    }
                    if (server_recv == -1)
                    {
                        continue;   
                    }
                }
            }
        }
        server_send = send(server_accept, response.c_str(), response.size(), 0);
        // server_send = send(server_accept, hello, strlen(hello), 0);

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