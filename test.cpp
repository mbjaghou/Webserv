#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>

const int PORT = 8080;
const int MAX_CLIENTS = 10;

int main() {
    // Step 1: Create and bind the server socket.
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("socket");
        return 1;
    }
    sockaddr_in server_address = {};
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);
    if (bind(server_socket, (sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("bind");
        return 1;
    }

    // Step 2: Listen for incoming connections.
    if (listen(server_socket, MAX_CLIENTS) == -1) {
        perror("listen");
        return 1;
    }

    // Step 3: Create the set of monitored file descriptors.
    fd_set read_fds, write_fds;
    FD_ZERO(&read_fds);
    FD_ZERO(&write_fds);
    FD_SET(server_socket, &read_fds);

    // Step 4: Enter the main loop that waits for events.
    std::vector<int> clients;
    while (true) {
        fd_set read_fds_copy = read_fds;
        fd_set write_fds_copy = write_fds;
        if (select(FD_SETSIZE, &read_fds_copy, &write_fds_copy, nullptr, nullptr) == -1) {
            perror("select");
            return 1;
        }

        // Step 5: Handle the events.
        for (int fd = 0; fd < FD_SETSIZE; ++fd) {
            if (FD_ISSET(fd, &read_fds_copy)) {
                if (fd == server_socket) {
                    // Step 6: Accept a new incoming connection.
                    sockaddr_in client_address = {};
                    socklen_t client_address_size = sizeof(client_address);
                    int client_socket = accept(server_socket, (sockaddr*)&client_address, &client_address_size);
                    if (client_socket == -1) {
                        perror("accept");
                        continue;
                    }
                    std::cout << "New client connected: " << inet_ntoa(client_address.sin_addr) << std::endl;
                    FD_SET(client_socket, &read_fds);
                    clients.push_back(client_socket);
                } else {
                    // Step 7: Handle data from an existing client.
                    char buffer[1024];
                    int bytes_received = recv(fd, buffer, sizeof(buffer), 0);
                    if (bytes_received == -1) {
                        perror("recv");
                        close(fd);
                        FD_CLR(fd, &read_fds);
                        FD_CLR(fd, &write_fds);
                        clients.erase(std::remove(clients.begin(), clients.end(), fd), clients.end());
                        continue;
                    }
                    if (bytes_received == 0) {
                        std::cout << "Client disconnected" << std::endl;
                        close(fd);
                        FD_CLR(fd, &read_fds);
                        FD_CLR(fd, &write_fds);
                        clients.erase(std::remove(clients.begin(), clients.end(), fd), clients.end());
                        continue;
                    }
                    std::cout << "Received " << bytes_received << " bytes from client" << std::endl;

                    // Step 8: Send a response if necessary.
                    if (FD_ISSET(fd, &write_fds_copy)) {
                        const char* response = "Hello, client!";
                        int bytes_sent = send(fd, response, strlen(response), 0);
                        if (bytes_sent == -1) {
                            perror("send");
                            close(fd);
                            FD_CLR(fd, &read_fds);
                            FD_CLR(fd, &write_fds);
                            clients.erase(std::remove(clients.begin(), clients.end(), fd), clients.end());
                            continue;
                        }
                        std::cout << "Sent " << bytes_sent << " bytes to client" << std::endl;
                    }
                }
            }
        }

        // Step 9: Set the write file descriptors for clients that have data to send.
        for (int fd : clients) {
            if (FD_ISSET(fd, &read_fds) && !FD_ISSET(fd, &write_fds)) {
                FD_SET(fd, &write_fds);
            }
        }
    }

    return 0;
}
