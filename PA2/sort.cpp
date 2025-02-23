// This program sorts an array of integers using different algorithms.
#include <iostream>
#include <algorithm>
#include <vector>

int bubbleSort(std::vector<int>& array)
{
    if (array.empty()) {
        std::cout << "Array is empty" << std::endl;
        return -1;
    }
    int n = array.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                std::swap(array[j], array[j + 1]);
            }   
        }
    }
    return 0;
}

int selectionSort(std::vector<int>& array)
{
    if (array.empty()) {
        std::cout << "Array is empty" << std::endl;
        return -1;
    }
    int n = array.size();
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < n ; j++)
        {
            if (array[j] < array[min])
            {
                min = j;
            }
        }
        if (min!= i)
        {
            std::swap(array[i], array[min]);
        }
    } 
    return 0;
}

int insertionSort(std::vector<int>& array)
{
    if (array.empty()) {
        std::cout << "Array is empty" << std::endl;
        return -1;
    }
    int n = array.size();
    int i,j,key;
    for (i = 1; i< n; i++)
    {
        int key = array[i];
        for (j = i; j > 0 && array[j - 1] > key; j--)
        {
            array[j] = array[j - 1];
        }
        array[j] = key;
    }
    return 0;

}

void mergeSort(std::vector<int>& array, int start, int end)
{
    if (start >= end)
    {
        return ;
    }
    std::vector<int>* temp = new std::vector<int>();
    int len = end - start ;
    int mid  = start + len/2 ;
    int start_1 = start ;
    int end_1 = mid ;
    int start_2 = mid + 1 ;
    int end_2 = end ;
    mergeSort( array, start_1, end_1);
    mergeSort( array, start_2, end_2);
    int index = start;
    while(start_1 <= end_1 && start_2 <= end_2)
    {
        if(array[start_1] < array[start_2])
        {
            temp->push_back(array[start_1]);
            start_1++;
        }
        else
        {
            temp->push_back(array[start_2]);
            start_2++;
        }
    }
    while(start_1 <= end_1)
    {
        temp->push_back(array[start_1]);
        start_1++;
    }
    while(start_2 <= end_2)
    {
        temp->push_back(array[start_2]);
        start_2++;
    }
    for(int i = 0; i < len; i++)
    {
        array[start + i] = temp->at(i);
    }
    delete temp;
    return ;
}

int mergeSort(std::vector<int>& array)
{
    if (array.empty()) 
    {
        std::cout << "Array is empty" << std::endl;
        return -1;
    }
    int len = array.size();
    mergeSort(array, 0, len - 1);    
    return 0;
}

int shellSort(std::vector<int>& array)
{
    if (array.empty())
    {
        std::cout << "Array is empty" << std::endl;
        return -1;
    }
    int gap,i,j;
    int temp;
    for (gap = array.size() / 2; gap > 0; gap /= 2)
    {
        for (i = gap; i < array.size(); i++)
        {
            temp = array[i];
            for (j = i - gap; j>=0 && array[j] > temp; j = j -gap)
            {
                array[j+gap] = array[j];
            }
            array[j+gap] = temp;    
        }
    }
    return 0;
}

int quickSort(std::vector<int>& array, int start, int end)
{
    if (start > end)
    {
        return -1;
    }
    int pivot = array[start];
    int left = start;
    int right = end;
    while(left < right)
    {
        while (left < right && array[left] < pivot)
        {
            left++;
        }
        while ( left < right && array[right] > pivot)
        {
            right--;
        }
        if (left < right)
        {
            std::swap(array[left], array[right]);
        }
    }
    quickSort(array, start, left - 1);

    quickSort(array, right + 1, end);
    
    return 0;

}

int quickSort(std::vector<int>& array)
{
    if (array.empty())
    {
        std::cout << "Array is empty" << std::endl;
        return -1;
    }
    quickSort(array, 0, array.size() - 1);
    return 0;
}

int main(){
    std::vector<int> arr_0 = {17, 12, 5, 2, 8, 3, 1, 11, 20, 15, 18, 13, 16, 19, 14, 9, 4, 7, 6, 10};
    std::cout << "Original array: ";
    for (int i = 0; i < arr_0.size(); i++) 
    {
        std::cout << arr_0[i] << " ";
    }
    std::cout << std::endl;
    std::vector<int> arr_1 = arr_0;
    bubbleSort(arr_1);
    std::cout << "Bubble sort: ";
    for (int i = 0; i < arr_1.size(); i++) 
    {
        std::cout << arr_1[i] << " ";
    }
    std::cout << std::endl;
    std::vector<int> arr_2 = arr_0;
    selectionSort(arr_2);
    std::cout << "Selection sort: ";
    for (int i = 0; i < arr_2.size(); i++) 
    {
        std::cout << arr_2[i] << " ";
    }
    std::cout << std::endl;
    std::vector<int> arr_3 = arr_0;
    insertionSort(arr_3);
    std::cout << "Insertion sort: ";
    for (int i = 0; i < arr_3.size(); i++) 
    {
        std::cout << arr_3[i] << " ";   
    }
    std::cout << std::endl;
    std::vector<int> arr_4 = arr_0;
    mergeSort(arr_4);
    std::cout << "Merge sort: ";
    for (int i = 0; i < arr_4.size(); i++) 
    {
        std::cout << arr_4[i] << " ";
    }
    std::cout << std::endl;
    std::vector<int> arr_5 = arr_0;
    shellSort(arr_5);
    std::cout << "Shell sort: ";
    for (int i = 0; i < arr_5.size(); i++) 
    {
        std::cout << arr_5[i] << " ";
    }
    std::cout << std::endl;
    std::vector<int> arr_6 = arr_0;
    quickSort(arr_6);
    std::cout << "Quick sort: ";
    for (int i = 0; i < arr_6.size(); i++) 
    {
        std::cout << arr_6[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}