#include <iostream>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>

#define PORT 8080
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

int main(int argc, char const *argv[]) {

    int server_socket, client_socket[MAX_CLIENTS], max_clients = MAX_CLIENTS;
    struct sockaddr_in server_addr, client_addr;
    fd_set readfds; // file descriptor set for select()
    char buffer[BUFFER_SIZE] = {0};
    int activity, valread, i, addrlen = sizeof(client_addr);

    // create server socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cerr << "Socket creation failed" << std::endl;
        return -1;
    }

    // set server socket options
    // int opt = 1;
    // if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
    //     std::cerr << "setsockopt failed" << std::endl;
    //     return -1;
    // }

    // set server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // bind server socket to address
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Bind failed" << std::endl;
        return -1;
    }

    // listen for client connections
    if (listen(server_socket, 3) < 0) {
        std::cerr << "Listen failed" << std::endl;
        return -1;
    }

    // initialize client sockets to 0
    for (i = 0; i < max_clients; i++) {
        client_socket[i] = 0;
    }

    while (true) {
        // clear the file descriptor set
        FD_ZERO(&readfds);

        // add server socket to file descriptor set
        FD_SET(server_socket, &readfds);
        int max_sd = server_socket;

        // add client sockets to file descriptor set
        for (i = 0; i < max_clients; i++) {
            int sd = client_socket[i];

            if (sd > 0) {
                FD_SET(sd, &readfds);
            }

            if (sd > max_sd) {
                max_sd = sd;
            }
        }

        // wait for activity on any of the sockets
        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

        if (activity < 0) {
            std::cerr << "Select error" << std::endl;
            return -1;
        }

        // handle new client connections
        if (FD_ISSET(server_socket, &readfds)) {
            int new_socket;

            if ((new_socket = accept(server_socket, (struct sockaddr *)&client_addr, (socklen_t*)&addrlen)) < 0) {
                std::cerr << "Accept error" << std::endl;
                return -1;
            }

            // add new socket to array of client sockets
            for (i = 0; i < max_clients; i++) {
                if (client_socket[i] == 0) {
                    client_socket[i] = new_socket;
                    std::cout << "New client connected";
					break;
                }
            }
        }

        // handle incoming data from clients
        for (i = 0; i < max_clients; i++) {
            int sd = client_socket[i];

            if (FD_ISSET(sd, &readfds)) {
                valread = read(sd, buffer, BUFFER_SIZE);

                if (valread == 0) {
                    // client disconnected
                    std::cout << "Client disconnected" << std::endl;
                    close(sd);
                    client_socket[i] = 0;
                } else {
                    // handle client message
                    std::cout << "Message received: " << buffer << std::endl;
                    // do something with the message
                    char response[] = "Server response";
            		send(sd, response, strlen(response), 0);

                }
            }
        }
    }

    return 0;
}