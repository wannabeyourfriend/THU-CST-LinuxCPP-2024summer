#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <dlfcn.h> // POSIX dynamic linking library
#include <cstring>

class server_module {
public:
    void* handle;
    void (*generate_function)(int);
    char* name;
};

server_module* module_open(const char* module_name);
void module_close(server_module* module);

#endif // COMMON_H