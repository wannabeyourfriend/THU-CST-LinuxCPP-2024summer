#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <sys/sysinfo.h>
#include <dirent.h>
#include <cstring>

// 获取 CPU 信息
void printCPUInfo() {
    std::ifstream cpuinfo("/proc/cpuinfo");
    if (!cpuinfo.is_open()) {
        std::cerr << "无法打开 /proc/cpuinfo 文件" << std::endl;
        return;
    }

    std::string line;
    std::cout << "CPU 信息:" << std::endl;
    while (std::getline(cpuinfo, line)) {
        if (line.find("processor") != std::string::npos ||
            line.find("model name") != std::string::npos ||
            line.find("cpu MHz") != std::string::npos ||
            line.find("cache size") != std::string::npos) {
            std::cout << line << std::endl;
        }
    }
    std::cout << std::endl;
}

// 获取内存信息
void printMemoryInfo() {
    struct sysinfo info;
    if (sysinfo(&info) != 0) {
        std::cerr << "无法获取内存信息" << std::endl;
        return;
    }

    std::cout << "内存信息:" << std::endl;
    std::cout << "总内存: " << info.totalram / (1024 * 1024) << " MB" << std::endl;
    std::cout << "可用内存: " << info.freeram / (1024 * 1024) << " MB" << std::endl;
    std::cout << "总交换区: " << info.totalswap / (1024 * 1024) << " MB" << std::endl;
    std::cout << "可用交换区: " << info.freeswap / (1024 * 1024) << " MB" << std::endl;
    std::cout << std::endl;
}

// 获取进程信息
void printProcessInfo() {
    std::cout << "进程信息:" << std::endl;

    DIR *procDir = opendir("/proc");
    if (!procDir) {
        std::cerr << "无法打开 /proc 目录" << std::endl;
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(procDir)) != nullptr) {
        if (entry->d_type == DT_DIR && std::isdigit(entry->d_name[0])) {
            std::string pid = entry->d_name;
            std::ifstream statusFile("/proc/" + pid + "/status");
            if (statusFile.is_open()) {
                std::string line;
                std::cout << "PID " << pid << ":" << std::endl;
                while (std::getline(statusFile, line)) {
                    if (line.find("Name:") != std::string::npos ||
                        line.find("State:") != std::string::npos ||
                        line.find("VmSize:") != std::string::npos) {
                        std::cout << "  " << line << std::endl;
                    }
                }
                statusFile.close();
                std::cout << std::endl;
            }
        }
    }
    closedir(procDir);
}

int main() {
    printCPUInfo();
    printMemoryInfo();
    printProcessInfo();

    return 0;
}
