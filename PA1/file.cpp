#include <iostream>
#include <fstream>
#include <cstdio> // For std::remove

int main() {
    // 1. 创建临时文件
    std::ofstream tempFile("/tmp/tempfile.txt");
    if (!tempFile) {
        std::cerr << "无法创建临时文件" << std::endl;
        return 1;
    }

    // 2. 写入数据到临时文件
    tempFile << "Hello, World!" << std::endl;
    tempFile.close(); // 关闭文件以确保数据写入

    // 3. 读取数据
    std::ifstream readFile("/tmp/tempfile.txt");
    if (!readFile) {
        std::cerr << "无法打开临时文件" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(readFile, line)) {
        std::cout << line << std::endl;
    }
    readFile.close();

    // 4. 删除临时文件
    if (std::remove("/tmp/tempfile.txt") != 0) {
        std::cerr << "无法删除临时文件" << std::endl;
        return 1;
    }

    std::cout << "临时文件已删除" << std::endl;

    return 0;
}
