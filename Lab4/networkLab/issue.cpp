// issue.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <arpa/inet.h>

static const char* page_start = 
    "<html>\n"
    "<body>\n"
    "<pre>\n";

static const char* page_end = 
    "</pre>\n"
    "</body>\n"
    "</html>\n";

static const char* error_page = 
    "<html>\n"
    "<body>\n"
    "<p>Error: Could not open /proc/issue.</p>\n"
    "</body>\n"
    "</html>\n";

void module_generate(int client_socket) {
    std::ifstream issue_file("/proc/issue");
    std::ostringstream response_stream;

    if (issue_file.is_open()) {
        std::string issue_content((std::istreambuf_iterator<char>(issue_file)),
                                  std::istreambuf_iterator<char>());

        // 构建 HTML 响应
        response_stream << "HTTP/1.1 200 OK\r\n";
        response_stream << "Content-Type: text/html\r\n";
        response_stream << "Content-Length: " << (response_stream.str().size() + issue_content.size() + strlen(page_start) + strlen(page_end)) << "\r\n";
        response_stream << "\r\n";
        response_stream << page_start;
        response_stream << issue_content;
        response_stream << page_end;
    } else {
        // 构建错误页面
        response_stream << "HTTP/1.1 500 Internal Server Error\r\n";
        response_stream << "Content-Type: text/html\r\n";
        response_stream << "Content-Length: " << strlen(error_page) << "\r\n";
        response_stream << "\r\n";
        response_stream << error_page;
    }

    std::string response = response_stream.str();

    // 发送响应
    send(client_socket, response.c_str(), response.size(), 0);

    // 关闭客户端套接字
    close(client_socket);
}
