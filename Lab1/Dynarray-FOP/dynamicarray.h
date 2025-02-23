#ifndef _DYNAMIC_ARRAY_H_
#define _DYNAMIC_ARRAY_H_
struct DynamicArray;
typedef struct DynamicArray DArray;
typedef struct DynamicArray* PDArray;
PDArray InitDArray(int count);
int  GetLength(PDArray &p);
int* GetAddress(PDArray &p);
void InitElement(PDArray &p);
void TraverseDArray(PDArray &p);
void SwapElement(PDArray &p, int i, int j);
void BubbleSort(PDArray &p);
int  BinarySearch(PDArray &p, int key);
void ResizeDArray(PDArray &p, int new_length);
void AppendElement(PDArray &p, int ele_count);
void AppendIdxElement(PDArray &p, int idx, int key);
void DeleteElement(PDArray &p, int ele_count);
void DeleteIdxElement(PDArray &p, int idx);
void WriteToArray(PDArray &p, int idx, int key);
#endif 
