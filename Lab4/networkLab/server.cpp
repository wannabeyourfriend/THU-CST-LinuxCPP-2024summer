#include "server.h"
#include <iostream>
#include <cstring>
#include <unistd.h> // POSIX API for fork(), exec(), etc.
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        std::string request(buffer);

        // 简单处理GET请求
        if (request.find("GET") == 0) {
            const char* response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 13\r\n\r\nHello, World!";
            send(client_socket, response, strlen(response), 0);
        } else {
            const char* response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nContent-Length: 15\r\n\r\nBad Request";
            send(client_socket, response, strlen(response), 0);
        }
    }
    close(client_socket);
}

void server_run(const char* local_address, uint16_t port) {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        std::cerr << "Socket creation failed" << std::endl;
        return;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(local_address);
    server_addr.sin_port = htons(port);

    if (bind(server_socket, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Bind failed" << std::endl;
        close(server_socket);
        return;
    }

    if (listen(server_socket, 5) < 0) {
        std::cerr << "Listen failed" << std::endl;
        close(server_socket);
        return;
    }

    std::cout << "Server running on " << local_address << ":" << port << std::endl;

    while (true) {
        sockaddr_in client_addr{};
        socklen_t client_len = sizeof(client_addr);
        int client_socket = accept(server_socket, (sockaddr*)&client_addr, &client_len);
        if (client_socket < 0) {
            std::cerr << "Accept failed" << std::endl;
            continue;
        }

        pid_t pid = fork();
        if (pid == 0) {
        
            close(server_socket); 
            handle_client(client_socket);
            exit(0);
        } else if (pid > 0) {
            close(client_socket); 
            waitpid(-1, nullptr, WNOHANG);
        } else {
            std::cerr << "Fork failed" << std::endl;
        }
    }
}
