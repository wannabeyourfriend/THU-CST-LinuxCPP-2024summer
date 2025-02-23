#include <iostream>
#include <cstdlib>
#include "dynamicarray.h"

int main()
{
    auto  p = InitDArray(10);
    int len = GetLength(p);
    std::cout << "Length of the dynamic array is " << len << std::endl;
    int* addr = GetAddress(p);
    std::cout << "Address of the dynamic array is " << addr << std::endl;
    InitElement(p);
    TraverseDArray(p);
    
    std::cout<<"Swapping elements at index 2 and 5:"<<std::endl;
    SwapElement(p, 2, 5);
    TraverseDArray(p);
    std::cout<< "Bubble sort the dynamic array:"<<std::endl;
    
    BubbleSort(p);
    TraverseDArray(p);

    std::cout<<"Binary search for element 5:"<<std::endl;
    std::cout <<BinarySearch(p, 5) << std::endl;
    TraverseDArray(p);

    std::cout<<"Binary search for element 100:"<<std::endl;
    std::cout <<BinarySearch(p, 100) << std::endl;
    std::cout<<"Resize the dynamic array to 11:"<<std::endl;
    ResizeDArray(p, 11);
    TraverseDArray(p);

    std::cout<<"Write element 100 to index 10:"<<std::endl;
    WriteToArray(p, 10, 100);
    TraverseDArray(p);

    std::cout<<"Insert element 200 at index 11:"<<std::endl;
    AppendElement(p,1);
    WriteToArray(p, 11, 200);
    TraverseDArray(p);

    std::cout<<"Insert element 300 at index 5:"<<std::endl;
    AppendIdxElement(p, 5, 300);
    TraverseDArray(p);
    std::cout<<"Delete  2 elements at tail:"<<std::endl;
    DeleteElement(p, 2);
    TraverseDArray(p);

    std::cout<<"Delete element at index 3:"<<std::endl;
    DeleteIdxElement(p, 3);
    TraverseDArray(p);

    return 0;
}
