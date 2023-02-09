/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:32:23 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/02/09 15:22:04 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

#include <sys/select.h>
 #include <fcntl.h>
int main()
{
    server serv;
    serv.socket_server_start();

    int connection[MAX_CONNECTION];
    fd_set read_fd;
    for(int i = 0; i < MAX_CONNECTION; i++)
        connection[i] = -1;
    connection[0] = serv.server_socket;
    while (1)
    {
        int i;
        char buffer[BUFFER];
        FD_ZERO(&read_fd);
        for (i = 0; i < MAX_CONNECTION; i++ )
        {
            if (connection[i] >= 0)
                FD_SET(connection[i], &read_fd);
        }
        int select_fd = select(FD_SETSIZE, &read_fd, NULL, NULL, NULL);
        if (select_fd >= 0)
        {
            if (FD_ISSET(serv.server_socket, &read_fd))
            {
                if (!serv.accept_server())
                {
                    for (i = 0; i < MAX_CONNECTION; i++)
                    {
                        if (connection[i] < 0)
                        {
                            connection[i] = serv.server_accept;
                            i = MAX_CONNECTION;
                        }
                            
                    }
                }
            select_fd--;
            if (!select_fd)
                continue;
            }
            // std::cout << "test\n";
            for (i=1;i < MAX_CONNECTION;i++) {
                 if ((connection[i] > 0) &&
                     (FD_ISSET(connection[i], &read_fd))) {
                     /* read incoming data */   
                    //  printf("Returned fd is %d [index, i: %d]\n", connection[i], i);
                     select_fd = recv(connection[i], buffer, BUFFER, 0);
                     if (select_fd == 0) {
                         printf("Closing connection for fd:%d\n", connection[i]);
                         close(connection[i]);
                         connection[i] = -1; /* Connection is now closed */
                     } 
                     if (select_fd > 0) { 
                        std::cout << "test\n"; 
                         printf("Received data (len %d bytes, fd: %d): \n%s\n", 
                             select_fd, connection[i], buffer);
                     } 
                     if (select_fd == -1) {
                         printf("recv() failed for fd: %d [%s]\n", 
                             connection[i], strerror(errno));
                         break;
                     }
                 }
                 select_fd--;
                 if (!select_fd) continue;
             }
        }
        else 
        {
            std::cout << "hello\n";
        }
        printf("%s\n ", buffer);
        serv.read_server(buffer);
        const char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 13\n\nLife 888 Life";
        write(serv.server_accept , hello , strlen(hello));
    }
        for (int i = 0; i < MAX_CONNECTION; i++)
        {
            if (connection[i] > 0)
                close(connection[i]);
        }
    return (0);
}