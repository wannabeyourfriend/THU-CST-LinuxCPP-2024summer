#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include "random.h"

void Randomize()
{
    srand((int)time(NULL));
}

int GenerateRandomNumber(int low, int high)
{
    if (low > high)
    {
        std::swap(low, high);
    }
    // double _d ~ [0,1)
    double _d =  (double)rand() / ((double)RAND_MAX + 1.0);
    // int return ~ [low,high]
    return low + (int)(_d * (high - low + 1));
}

double GenerateRandomDouble(double low, double high)
{
    if (low > high)
    {
        std::swap(low, high);
    }
    // double _d ~ [0,1]
    double _d =  (double)rand() / (double)RAND_MAX;
    // double return ~ [low,high]
    return low + _d * (high - low);
    
}