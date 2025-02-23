#include <iostream>
#include <cstdlib>
#include "dynamicarray.h"

struct DynamicArray
{
    int count;
    int* ptrArray;
};

PDArray InitDArray(int count)
{
    auto p = new DynamicArray;
    p->count = count;
    p->ptrArray = new int[count];
    return p;
}

int GetLength(PDArray &p)
{
    return p->count;
}

int *GetAddress(PDArray &p)
{
    return p->ptrArray;
}

void InitElement(PDArray &p)
{
    int len = GetLength(p);
    int* addr = GetAddress(p);
    std::cout<<"Enter "<<len<<" elements: ";
    for(int i=0; i<len; i++)
    {
        std::cin>>addr[i];
    }
}

void TraverseDArray(PDArray &p)
{
    int* addr = GetAddress(p);
    int len = GetLength(p);
    for(int i=0; i<len; i++)
    {
        std::cout<<addr[i]<<" ";
    }
    std::cout<<std::endl;
}

void SwapElement(PDArray &p, int i, int j)
{
    int len = GetLength(p);
    if (i<0 || i>=len || j<0 || j>=len)
    {
        exit(1);
    } else 
    {
        int* addr = GetAddress(p);
        int temp = addr[i];
        addr[i] = addr[j];
        addr[j] = temp;
    }
}

void BubbleSort(PDArray &p)
{
    int len = GetLength(p);
    int* addr = GetAddress(p);
    for(int i=0; i<len-1; i++)
    {
        for(int j=0; j<len-i-1; j++)
        {
            if(addr[j] > addr[j+1])
            {
                SwapElement(p, j, j+1);
            }
        }
    }
}

int BinarySearch(PDArray &p, int key)
{
    int len = GetLength(p);
    int* addr = GetAddress(p);
    int low = 0;
    int high = len-1;
    int index = -1;
    while (low <= high)
    {
        int mid = (low + high)/2;
        if (addr[mid] == key)
        {
            index = mid;
            break;
        } else if (addr[mid] < key)
        {
            low = mid + 1;
        } else 
        {
            high = mid - 1;
        }
    }
    return index;
}

void ResizeDArray(PDArray &p, int new_length)
{
    int len = GetLength(p);
    int* temp = new int[new_length];
    int minlen = (len < new_length)? len : new_length;
    int* addr = GetAddress(p);
    for (int i=0; i<minlen; i++)
    {
        temp[i] = addr[i];
    }
    if (len < new_length)
    {
        //std::cout<<"Enter "<<new_length-len<<" new elements: ";
        for(int i=len; i<new_length; i++)
        {
            temp[i] = 0;
        }
    }
    delete[] p -> ptrArray;
    p->ptrArray = temp;
    p->count = new_length;
}

void AppendElement(PDArray &p, int ele_count)
{
    ResizeDArray(p, GetLength(p)+ele_count);
}

void AppendIdxElement(PDArray &p, int idx, int key)
{

    int len = GetLength(p);
    //std::cout<< GetAddress(p)<<std::endl;
    if (idx < 0 || idx > len)
    {
        exit(1);
    } else 
    {
        ResizeDArray(p, len+1);
        //std::cout<< GetAddress(p)<<std::endl;
        int* addr = p->ptrArray;
        for (int i=len-1; i>=idx; i--)
        {
            addr[i+1] = addr[i];
        }
        //std::cout<< "here is operated" << std::endl;
        addr[idx] = key;
        //for (int i = 0; i < len; i++)
        //{
        //    std::cout<<addr[i]<<" ";
        //}

        //std::cout<<std::endl;
        //std::cout<< "here is operated" << std::endl;
        //TraverseDArray(p);
    }
}

void DeleteElement(PDArray &p, int ele_count)
{
    int len = GetLength(p);
    if (ele_count > len)
    {
        exit(1);
    }
    ResizeDArray(p, len-ele_count);
}

void DeleteIdxElement(PDArray &p, int idx)
{
    int len = GetLength(p);
    if (idx < 0 || idx >= len)
    { 
        exit(1);
    }
    int* addr = p->ptrArray;
    for (int i=idx; i<len-1; i++)
    {
        addr[i] = addr[i+1];
    }
    ResizeDArray(p, len-1);

}

void WriteToArray(PDArray &p, int idx, int key)
{
    int len = GetLength(p);
    if (idx < 0 || idx >= len)
    {
        exit(1);
    }
    int* addr = p->ptrArray;
    addr[idx] = key;
}