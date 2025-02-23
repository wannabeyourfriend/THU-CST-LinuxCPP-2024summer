#ifndef SERVER_H
#define SERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

typedef void (*module_generate_function)(int);

void handle_client(int client_socket);
void server_run(const char* local_address, uint16_t port);

#endif // SERVER_H