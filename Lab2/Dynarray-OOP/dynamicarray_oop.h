#ifndef _DYNARRAY_H_
#define _DYNARRAY_H_

class DynamicArray {
private:
    const int capacity;
    int size;
    int *pointer;

public:
    DynamicArray(int _cap): capacity(_cap),size(0),pointer(NULL) {}

    DynamicArray(const DynamicArray &other);

    DynamicArray(int _cap, int *other ,int num);

    DynamicArray & operator =(const DynamicArray &other);

    ~DynamicArray()
    {
        printf("Destructor called\n");
        if (pointer)
        {
            delete [] pointer;
        }
    }

    void push_back(int value);
    
    int length();

    int & operator[](int idx){return pointer[idx];} 

    void travel_by(void (*func)(int* data));

    void insert(int,int);

    void extract(int idx);

};

#endif