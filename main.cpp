/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:32:23 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/02/10 14:39:38 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

#include <sys/select.h>
 #include <fcntl.h>
int main()
{
    server serv;
    fd_set read_fd;
    char buffer[BUFFER];
    const char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 14\n\nLife word Life";
    int i;

    serv.socket_server_start();
    for(int i = 0; i < MAX_CONNECTION; i++)
        serv.connection[i] = -1;
    
    serv.connection[0] = serv.server_socket;
    while (1)
    {
        FD_ZERO(&read_fd);
        for (i = 0; i < MAX_CONNECTION;++i)
        {
            if (serv.connection[i] >= 0)
                FD_SET(serv.connection[i], &read_fd);
        }
        if (!serv.select_socket(read_fd))
        {
            if (FD_ISSET(serv.server_socket, &read_fd))
            {
                if(!serv.accept_server())
                {
                    serv.send_client(hello);
                    for (i = 0; i < MAX_CONNECTION; ++i)
                    {
                        if (serv.connection[i] < 0)
                        {
                            serv.connection[i] = serv.server_accept;
                            break ;
                        }
                    }
                }
               
            }
            for (i = 1; i < MAX_CONNECTION; ++i)
            {
                
                if (serv.connection[i] > 0 && FD_ISSET(serv.connection[i], &read_fd))
                {
                    serv.server_recv = recv(serv.connection[i], buffer, BUFFER, 0);
                    if (serv.server_recv == 0)
                    {
                        std::cout << "shutdown\n";
                        close(serv.connection[i]);
                        serv.connection[i] = -1;
                    }
                    if (serv.server_recv > 0)
                    {
                        printf("%s", buffer);
                    }
                    if (serv.server_recv == -1)
                    {
                        std::cout << std::strerror(errno);
                        break;
                    }
                }
            }
        }
        
    }
    for (int i = 0; i < MAX_CONNECTION; i++)
    {
        if (serv.connection[i] > 0)
            close(serv.connection[i]);
    }
    return (0);
}