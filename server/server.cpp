/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:22:52 by mbjaghou          #+#    #+#             */
/*   Updated: 2023/03/16 16:22:58 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

server::server(){std::cout << "\033[32m" << "Welcome to my server" << "\033[0m" << std::endl;}

void server::stock_address_port(pars pars)
{
	size_t j = -1;
	while (++j < pars.parssing.size())
	{	
		for (std::multimap<std::string, long>::iterator it = pars.parssing[j].listen.begin(); it != pars.parssing[j].listen.end(); ++it)
		{
			std::cout << it->first << " => " << it->second << '\n';
			server_listen.insert(std::pair<std::string, int>(it->first, it->second));
		}
	}
}

int server::select_socket(fd_set read_fd , int max)
{
	int server_select;
    server_select = select(max + 1, &read_fd, NULL, NULL, NULL);
    if (server_select < 0)
    {
        throw std::invalid_argument(strerror(errno));
        return (1);
    }
    return (0);
}

int server::socket_server_start(void)
{
	for (std::multimap<std::string, long>::iterator it = server_listen.begin(); it != server_listen.end(); ++it)
	{
		if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
			throw std::invalid_argument(strerror(errno));
		int opt = 1;
		if ((setsockopt(server_socket , SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) < 0)
			throw std::invalid_argument("Error address socket is already used");
		fcntl(server_socket, F_SETFL, O_NONBLOCK);
		bzero(&this->addr, sizeof(this->addr));
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = inet_addr(it->first.c_str());
		addr.sin_port = htons(it->second);
		memset(addr.sin_zero, 0, sizeof addr.sin_zero);
		 int server_bind;
		if ((server_bind = bind(server_socket, (struct sockaddr *)&addr, sizeof(addr))) < 0)
		{
			throw std::invalid_argument(strerror(errno));
			::close(server_socket);
		}
		int server_lesten;
		if ((server_lesten = listen(server_socket, SOMAXCONN)) < 0)
		{ 
			throw std::invalid_argument(strerror(errno));
			::close(server_socket);
		}
		std::pair<int, sockaddr_in> pair = std::make_pair(server_socket, addr);
		Server.push_back(pair);
		server_socket = 0;
	}
    return (0);
}


int server::start_server(pars pars)
{
    fd_set read_fd;
    std::string response;
	int accepted[FD_SETSIZE];
	const char *hello = "HTTP/1.1 200 OK\r\nContent-Length: 12\r\n\r\nHello world\n";
    int i;

	stock_address_port(pars);
    if (socket_server_start())
        return (1);
	for(i = 0; i < FD_SETSIZE; i++)
         accepted[i] = -1;
	while (1)
	{
		FD_ZERO(&read_fd);
		int max;
		for (std::vector<std::pair<int, sockaddr_in> >::iterator it = Server.begin(); it != Server.end(); ++it)
		{
			FD_SET(it->first, &read_fd);
			max = it->first;
		}
		for (i = 0; i < FD_SETSIZE; ++i)
		{
			int sd = accepted[i];
			if (sd > 0)
				FD_SET(sd, &read_fd);
			if (sd > max)
				max = sd;
		}
        select_socket(read_fd, max);
		for (std::vector<std::pair<int, sockaddr_in> >::iterator it = Server.begin(); it != Server.end(); ++it)
		{
			if (FD_ISSET(it->first, &read_fd))
			{
				if((server_accept = accept(it->first, NULL, NULL)) >= 0)
				{
					int j;
					for (j = 0; j < FD_SETSIZE; j++)
					{
						if (accepted[j] < 0)
						{
							accepted[j] = server_accept;
							break ;
						}
					}
				}
			}
		}
    	for (i = 0; i < FD_SETSIZE; ++i)
    	{
			int sd = accepted[i];
			try {
				if (sd > 0 && FD_ISSET(sd, &read_fd))
				{
					server_recv = recv(sd, buffer, BUFFER, 0);
					if (server_recv == 0)
					{
						accepted[i] = -1;
						::close(sd);
						continue;
					}
					else if (server_recv < 0)
						throw std::invalid_argument(strerror(errno));
					else if (server_recv > 0)
					{
						std::string tmp = buffer;
						Request o(tmp, pars);
						Response res(o);
						if (o.getPath() == "/favicon.ico") {
							send(sd, hello, strlen(hello), 0);
							std::cout << "hello" << std::endl;
						}
						else {
							response = res.sendDir(o.getPath().c_str(), o.getHost());
							int send_res = send(sd, response.c_str(), response.size(), 0);
							if (send_res < 0)
								throw std::invalid_argument(strerror(errno));
							else if (send_res == 0)
								continue ;						
						}
					}
				}
    	    }
			catch (std::exception &e) {
				std::cout << e.what() << std::endl;
				::close(sd);
				accepted[i] = -1;
			}
    	}
	
	}
}
