#include <cstdio>
#include "dynamicarray_oop.h"

void print_array(int *data)
{
    printf("%d ", *data);
}

int main()
{
    int DYNAMICARRAY[6] = {376,425,328,556,668,710};

    DynamicArray array_a(10);

    array_a.push_back(600);

    array_a.travel_by(print_array);

    array_a.push_back(500);

    array_a.push_back(400);


    array_a.travel_by(print_array);

    DynamicArray array_b (20, DYNAMICARRAY, 6);

    array_b.travel_by(print_array);

    DynamicArray array_c(array_b);

    array_c.travel_by(print_array);

    array_a.travel_by(print_array);

    array_c = array_a;

    array_c.travel_by(print_array);
    
    printf("%d ",array_c[1]);

    printf("\n");

    array_c.insert(1,133);

    array_c.travel_by(print_array);

    array_c.extract(2);

    array_c.travel_by(print_array);

    return 0;

}