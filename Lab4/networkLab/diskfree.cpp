// diskfree.cpp
#include <iostream>
#include <sstream>
#include <cstdio>
#include <unistd.h>
#include <sys/wait.h>
#include <arpa/inet.h>

static const char* page_start = 
    "<html>\n"
    "<body>\n"
    "<pre>\n";

static const char* page_end = 
    "</pre>\n"
    "</body>\n"
    "</html>\n";

void module_generate(int client_socket) {
    int pipefd[2];
    pipe(pipefd);

    pid_t pid = fork();

    if (pid == -1) {
        // Fork failed
        std::string error_page = "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/html\r\nContent-Length: 64\r\n\r\n<html><body><p>Error: Could not fork process.</p></body></html>\n";
        send(client_socket, error_page.c_str(), error_page.size(), 0);
        close(client_socket);
        return;
    }

    if (pid == 0) {
        // Child process
        close(pipefd[0]); // Close unused read end
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe
        execlp("df", "df", nullptr); // Execute df command
        _exit(127); // If exec fails
    } else {
        // Parent process
        close(pipefd[1]); // Close unused write end
        waitpid(pid, nullptr, 0); // Wait for child to finish

        std::ostringstream response_stream;
        response_stream << "HTTP/1.1 200 OK\r\n";
        response_stream << "Content-Type: text/html\r\n";

        // Calculate content length
        std::string output;
        char buffer[128];
        ssize_t bytes_read;
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            output += buffer;
        }
        close(pipefd[0]);

        response_stream << "Content-Length: " << (response_stream.str().size() + output.size() + strlen(page_start) + strlen(page_end)) << "\r\n";
        response_stream << "\r\n";
        response_stream << page_start;
        response_stream << output;
        response_stream << page_end;

        std::string response = response_stream.str();
        send(client_socket, response.c_str(), response.size(), 0);
        close(client_socket);
    }
}
