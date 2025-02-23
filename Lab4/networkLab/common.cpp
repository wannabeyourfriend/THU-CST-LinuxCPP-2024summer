#include "server.h"
#include <iostream>
#include <dlfcn.h> // POSIX dynamic linking library
#include <cstring>

// 载入模块
server_module* module_open(const char* module_name) {
    server_module* mod = new server_module();
    mod->handle = dlopen(module_name, RTLD_LAZY); // 动态加载模块

    if (!mod->handle) {
        std::cerr << "Failed to load module: " << dlerror() << std::endl;
        delete mod;
        return nullptr;
    }

    // 获取模块的生成函数
    mod->generate_function = reinterpret_cast<void (*)(int)>(dlsym(mod->handle, "generate_function"));
    if (!mod->generate_function) {
        std::cerr << "Failed to find generate_function: " << dlerror() << std::endl;
        dlclose(mod->handle);
        delete mod;
        return nullptr;
    }

    const char* name = reinterpret_cast<const char*>(dlsym(mod->handle, "module_name"));
    if (name) {
        mod->name = strdup(name); // 复制模块名称
    } else {
        mod->name = "Unnamed Module";
    }

    return mod;
}

// 卸载模块
void module_close(server_module* module) {
    if (module) {
        if (module->handle) {
            dlclose(module->handle);
        }
        if (module->name) {
            free(const_cast<char*>(module->name)); // 释放名称内存
        }
        delete module;
    }
}

void server_run(const char* local_address, uint16_t port) {
   
}
