// main.cpp

#include <iostream>
#include <getopt.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <cstdlib>
#include "server.h"
#incldue "common.h"
#include "process.h"
#include "diskfree.h"
#include "issue.h"
#include "time.h"

static void print_usage(const char* program_name) {
    std::cout << "Usage: " << program_name << " [OPTIONS]\n"
              << "Options:\n"
              << "  -a, --address ADDRESS   Server address (default: localhost)\n"
              << "  -h, --help              Display this help message\n"
              << "  -m, --modir DIR         Service module directory\n"
              << "  -p, --port PORT         Server port (default: 8008)\n"
              << "  -v, --verbose           Verbose mode\n";
}

static void start_server(const std::string& address, int port, const std::string& modir, bool verbose) {
    int server_fd, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char buffer[1024] = {0};

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set up server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(address.c_str());
    server_addr.sin_port = htons(port);

    // Bind the socket
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (verbose) {
        std::cout << "Server listening on " << address << ":" << port << std::endl;
    }

    while (true) {
        // Accept incoming connection
        client_socket = accept(server_fd, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_socket < 0) {
            perror("accept failed");
            continue;
        }

        // Handle client request
        module_generate(client_socket);
    }

    close(server_fd);
}

int main(int argc, char* argv[]) {
    std::string address = "localhost";
    int port = 8008;
    std::string modir;
    bool verbose = false;

    static struct option long_options[] = {
        {"address", required_argument, nullptr, 'a'},
        {"help", no_argument, nullptr, 'h'},
        {"modir", required_argument, nullptr, 'm'},
        {"port", required_argument, nullptr, 'p'},
        {"verbose", no_argument, nullptr, 'v'},
        {nullptr, 0, nullptr, 0}
    };

    int opt;
    int option_index = 0;

    while ((opt = getopt_long(argc, argv, "a:hm:p:v", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'a':
                address = optarg;
                break;
            case 'h':
                print_usage(argv[0]);
                return 0;
            case 'm':
                modir = optarg;
                break;
            case 'p':
                port = std::stoi(optarg);
                break;
            case 'v':
                verbose = true;
                break;
            default:
                print_usage(argv[0]);
                return 1;
        }
    }

    if (verbose) {
        std::cout << "Starting server with the following configuration:\n"
                  << "Address: " << address << "\n"
                  << "Port: " << port << "\n"
                  << "Module Directory: " << modir << "\n";
    }

    start_server(address, port, modir, verbose);
    return 0;
}
