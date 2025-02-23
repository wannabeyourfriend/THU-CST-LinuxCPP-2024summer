// process.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstring>
#include <arpa/inet.h>

static const char* page_start =
    "<html>\n"
    "<body>\n"
    "<table cellpadding=\"4\" cellspacing=\"0\" border=\"1\">\n"
    "<thead>\n"
    "<tr>\n"
    "<th>PID</th>\n"
    "<th>Program</th>\n"
    "<th>User</th>\n"
    "<th>Group</th>\n"
    "<th>RSS&nbsp;(KB)</th>\n"
    "</tr>\n"
    "</thead>\n"
    "<tbody>\n";

static const char* page_end =
    "</tbody>\n"
    "</table>\n"
    "</body>\n"
    "</html>\n";

std::string get_process_info(int pid) {
    std::ostringstream info;
    std::ifstream stat_file("/proc/" + std::to_string(pid) + "/stat");
    std::string line;
    if (stat_file.is_open()) {
        std::getline(stat_file, line);
        size_t start = line.find('(') + 1;
        size_t end = line.find(')');
        std::string comm = line.substr(start, end - start);

        std::ifstream status_file("/proc/" + std::to_string(pid) + "/status");
        std::string status_line;
        std::string rss;
        if (status_file.is_open()) {
            while (std::getline(status_file, status_line)) {
                if (status_line.find("VmRSS:") == 0) {
                    rss = status_line.substr(status_line.find_last_of('\t') + 1);
                    break;
                }
            }
        }

        struct stat buf;
        std::string exe_path = "/proc/" + std::to_string(pid) + "/exe";
        if (lstat(exe_path.c_str(), &buf) == 0) {
            passwd* pw = getpwuid(buf.st_uid);
            group* gr = getgrgid(buf.st_gid);
            info << "<tr>\n"
                 << "<td>" << pid << "</td>\n"
                 << "<td>" << comm << "</td>\n"
                 << "<td>" << (pw ? pw->pw_name : "Unknown") << "</td>\n"
                 << "<td>" << (gr ? gr->gr_name : "Unknown") << "</td>\n"
                 << "<td>" << rss << "</td>\n"
                 << "</tr>\n";
        }
    }
    return info.str();
}

void module_generate(int client_socket) {
    std::ostringstream response_stream;
    DIR* proc_dir = opendir("/proc");
    if (proc_dir) {
        struct dirent* entry;
        response_stream << "HTTP/1.1 200 OK\r\n";
        response_stream << "Content-Type: text/html\r\n";

        response_stream << "Content-Length: " << (response_stream.str().size() + strlen(page_start) + strlen(page_end)) << "\r\n";
        response_stream << "\r\n";
        response_stream << page_start;

        while ((entry = readdir(proc_dir)) != nullptr) {
            if (entry->d_type == DT_DIR) {
                int pid = std::atoi(entry->d_name);
                if (pid > 0) {
                    response_stream << get_process_info(pid);
                }
            }
        }

        closedir(proc_dir);
        response_stream << page_end;
    } else {
        response_stream << "HTTP/1.1 500 Internal Server Error\r\n";
        response_stream << "Content-Type: text/html\r\n";
        response_stream << "Content-Length: " << strlen("Error: Could not open /proc directory.") << "\r\n";
        response_stream << "\r\n";
        response_stream << "<html><body><p>Error: Could not open /proc directory.</p></body></html>";
    }

    std::string response = response_stream.str();
    send(client_socket, response.c_str(), response.size(), 0);
    close(client_socket);
}
