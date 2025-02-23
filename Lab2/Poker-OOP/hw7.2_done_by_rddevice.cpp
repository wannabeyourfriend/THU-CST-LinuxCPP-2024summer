#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>
#include <random>
#include <cstring>
#include "random.h"

// 从 /dev/urandom 读取随机字节
std::vector<unsigned char> read_random_bytes(size_t num_bytes) {
    std::vector<unsigned char> buffer(num_bytes);
    std::ifstream urandom("/dev/urandom", std::ios::binary);
    urandom.read(reinterpret_cast<char*>(buffer.data()), num_bytes);
    return buffer;
}

// 随机数生成器
std::mt19937_64 rng;

void Randomize() {
    // 读取足够的随机字节来初始化种子
    auto random_bytes = read_random_bytes(sizeof(uint64_t));
    uint64_t seed = *reinterpret_cast<uint64_t*>(random_bytes.data());
    rng.seed(seed);
}

int GenerateRandomNumber(int low, int high) {
    if (low > high) {
        std::swap(low, high);
    }
    
    std::uniform_int_distribution<int> dist(low, high);
    return dist(rng);
}

double GenerateRandomDouble(double low, double high) {
    if (low > high) {
        std::swap(low, high);
    }
    
    std::uniform_real_distribution<double> dist(low, high);
    return dist(rng);
}
