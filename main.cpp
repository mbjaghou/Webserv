/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:32:23 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/02/03 17:25:21 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

int main(int ac, char **av)
{
    server serv;
    
    if (serv.socket_server())
        exit (1);

    serv.addr.sin_family = AF_INET;
    serv.addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv.addr.sin_port = htons(PORT);
    memset(serv.addr.sin_zero, '\0', sizeof serv.addr.sin_zero);

    if (serv.bind_server())
        exit (1);
    if (serv.lesten_server())
        exit (1);
    while (1)
    {
        char buffer[80000];
        if (serv.accept_server())
            exit(1);
        if (serv.read_server(buffer))
            exit (1);

        printf("%s\n ", buffer);
        //response
        char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nLife is Life";
        write(serv.server_accept , hello , strlen(hello));
        close(serv.server_accept);
    }
    return (0);
}