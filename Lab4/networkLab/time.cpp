// time.cpp
#include <iostream>
#include <ctime>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

static const char* page_template = 
    "<html>\n"
    "<head>\n"
    "<meta http-equiv=\"refresh\" content=\"5\">\n"
    "</head>\n"
    "<body>\n"
    "<p>The current time is %s.</p>\n"
    "</body>\n"
    "</html>\n";

void module_generate(int client_socket) {
    // 获取当前时间
    time_t now = time(nullptr);
    struct tm *timeinfo = localtime(&now);

    // 格式化时间
    char time_str[100];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", timeinfo);

    // 构建 HTML 响应
    char response[1024];
    snprintf(response, sizeof(response),
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: %lu\r\n"
        "\r\n"
        "%s",
        strlen(page_template) + strlen(time_str) - 6, // Length of the final HTML response
        page_template);

    // 发送响应
    send(client_socket, response, strlen(response), 0);

    // 关闭客户端套接字
    close(client_socket);
}
