#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "dynamicarray_oop.h"

DynamicArray::DynamicArray(const DynamicArray& other): capacity(other.capacity), size(other.size) 
{
    if (other.pointer)
    {
        pointer = new int[size];
        
        if (other.pointer == NULL)
        {
            printf("Memory allocation failed.\n");
            exit(1);
        }

        memccpy(pointer, other.pointer, sizeof(int) * size, sizeof(int) * other.size );

    }
    else 
        pointer = NULL;

}

DynamicArray::DynamicArray(int _cap, int * other, int n): capacity(_cap), size(n) 
{
    if (capacity < n)
    {
        printf("Capacity is less than size.\n");
        exit(2);
    }

    pointer = new int[capacity];

    if (pointer == NULL)
    {
        printf("Failed to new pinter");
        exit(1);
    }

    memccpy(pointer, other, sizeof(int) * size, sizeof(int) * size);

    
}
DynamicArray& DynamicArray::operator =(const DynamicArray &other)
{
    if (pointer == other.pointer)
    {
        return *this;
    }

    if (other.pointer == NULL)
    {
        if (pointer)
        {
            delete [] pointer;
        }
        size = 0;
        pointer = NULL;
        return *this;
    }

    if (other.size > size)
    {
        printf("The size that copily initialize the array is too large.");
        exit(2);
    }

    if (other.size < size)
    {
        if (pointer)
        {
            delete [] pointer;
        }
        pointer = new int[other.size];

        if (pointer == NULL)
        {
            printf("Fail to initiate pointer");
            exit(1);
        }
    }

    memccpy(pointer, other.pointer,sizeof(int) * size, sizeof(int) * other.size);

    size = other.size;

    return *this;
}

void DynamicArray::push_back(int value)
{
    if ( size + 1 > capacity)
    {
        printf("The size is larger than capacity!");
        exit(2);
    }

    if (pointer)
    {
        int *temp = new int [size +1];
        if (temp == NULL)
        {
            printf("Failed to new memory!");
            exit(1);
        }

        memccpy(temp,pointer,sizeof(int) * (size +1),sizeof(int) * (size));

        delete [] pointer;

        pointer = temp;
    }
    else
    {
        pointer = new int[1];
        if (pointer == NULL)
        {
            printf("Failed to new memory");
            exit(1);
        }
    }

    pointer[size++] = value;

}

int DynamicArray::length()
{
    return size;
}

// int DynamicArray::operator [](int idx)
// {
//     return pointer[idx];
// }

void DynamicArray::travel_by(void(*func)(int * data))
{
    for (int i = 0; i < size; ++i)
    {
        func(pointer + i);
    }
    printf("\n");
}

void  DynamicArray::insert(int idx,int value)
{
    if (idx > size || idx < 0)
    {
        printf("The insert index is out of range");
        exit(2);
    }

    if (pointer)
    {
        int *temp = new int [size +1];
        if (temp == NULL)
        {
            printf("Failed to new memory!");
            exit(1);
        }
        for (int i = 0 ; i < idx ; ++i )
        {
            temp[i] = pointer[i];
        }
        for (int i = idx; i < size ; ++i)
        {
            temp[i+1] = pointer[i];  
        }
        temp[idx] = value;

        delete [] pointer;

        pointer = temp;

        size++;
    }
    else
    {
        pointer = new int[1];
        if (pointer == NULL)
        {
            printf("Failed to new memory");
            exit(1);
        }
        pointer[1] = value;
    }
    return;

}

void DynamicArray::extract(int idx)
{
    if (pointer)
    {
        int *temp = new int [size - 1];
        if (temp == NULL)
        {
            printf("Failed to new memory!");
            exit(1);
        }
        for (int i = 0; i < idx ; ++i )
        {
            temp[i] = pointer[i];
        }
        for (int i = idx; i < size-1; ++i)
        {
            temp[i] = pointer[i+1];  
        }

        delete [] pointer;

        pointer = temp;

        size--;
    }
    else
    {
        printf("Array is empty!");
        exit(2);
    }
}