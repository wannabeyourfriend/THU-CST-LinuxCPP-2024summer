#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class ProcessInfo {
public:
    static std::string get_process_info(int pid);
};

#endif // PROCESS_H