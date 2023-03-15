#include <iostream>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
#include <netdb.h>
#include <strings.h>

using namespace std;

std::vector<std::pair<short, std::string> > Server;
std::vector<std::pair<int, struct sockaddr_in>> Server_socket;


int main(int ac , char **av) {

	std::string server1 = "127.0.0.1";
	short s1 = 8080;
	Server.push_back(std::make_pair(s1, server1));
	std::string server2 = "127.0.0.1";
	short s2 = 9090;
	Server.push_back(std::make_pair(s2, server2));

	for (int i = 0 ; i < 2 ; i++) {
		int fd = socket(AF_INET, SOCK_STREAM, 0);
		if (fd < 0) {
			std::cout << "socket error" << std::endl;
			return 0;
		}
		struct sockaddr_in addr;
		bzero(&addr, sizeof(addr));
		addr.sin_family = AF_INET;
		struct addrinfo * res;
		if (0 < getaddrinfo(Server[i].second.c_str(), NULL ,NULL, &res)) {
			std::cout << "getaddrinfo error" << std::endl;
			return 0;
		}
		
		addr.sin_addr.s_addr = reinterpret_cast<struct sockaddr_in*>(res->ai_addr)->sin_addr.s_addr;
		addr.sin_port = htons(Server[i].first);
		if (0 > ::bind(fd, reinterpret_cast<const struct sockaddr*>(&addr), sizeof(addr))) {
			std::cout << "bind error" << std::endl;
			return 0;
		}
		if(0 > listen(fd, SOMAXCONN)) {
			std::cout << "listen error" << std::endl;
			return 0;
		}
		Server_socket.push_back(std::make_pair(fd, addr));
	}
	fd_set read_fd;
	fd_set write_fd;
	int max_fd = 0;
	int client_fds[1024] = {0};

	while(1) {
		FD_ZERO(&read_fd);
		FD_ZERO(&write_fd);
		
		for (int i = 0 ; i < 2 ; i++) {
			FD_SET(Server_socket[i].first, &read_fd);
			if (max_fd < Server_socket[i].first)
				max_fd = Server_socket[i].first;
		}
	}

}