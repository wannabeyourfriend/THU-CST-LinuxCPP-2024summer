#include <iostream>
#include <fstream>
#include <string>

void print_cpu_info() {
    std::ifstream cpuinfo("/proc/cpuinfo");
    if (cpuinfo) {
        std::string line;
        while (std::getline(cpuinfo, line)) {
            std::cout << line << std::endl;
        }
    } else {
        std::cerr << "Failed to open /proc/cpuinfo" << std::endl;
    }
}

void print_mem_info() {
    std::ifstream meminfo("/proc/meminfo");
    if (meminfo) {
        std::string line;
        while (std::getline(meminfo, line)) {
            std::cout << line << std::endl;
        }
    } else {
        std::cerr << "Failed to open /proc/meminfo" << std::endl;
    }
}

void print_process_info(int pid) {
    std::string path = "/proc/" + std::to_string(pid) + "/status";
    std::ifstream status(path);
    if (status) {
        std::string line;
        while (std::getline(status, line)) {
            std::cout << line << std::endl;
        }
    } else {
        std::cerr << "Failed to open " << path << std::endl;
    }
}

int main() {
    std::cout << "CPU Info:" << std::endl;
    print_cpu_info();
    std::cout << "\nMemory Info:" << std::endl;
    print_mem_info();
    std::cout << "\nProcess Info (PID 1):" << std::endl;
    print_process_info(1);
    return 0;
}