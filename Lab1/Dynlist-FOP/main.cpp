#include <iostream>
#include <cstdlib>
#include <cstring>
#include "dynlist.h"
#include "point.h"

using namespace std;

void DoPrintObject(ADT e, ADT tag)
{
    printf("%s", PtTransformIntoString((const char *)tag, (PPOINT)e));
    printf("->");
}

void DoDestroyObject(ADT e)
{
    PtDestroy((PPOINT)e);
}

int DoCompareObject(CADT e1, CADT e2)
{
    return PtCompare((PPOINT)e1, (PPOINT)e2);
}

int main(void)
{
    PLIST my_list = LICreate();

    if (LIIsEmpty(my_list))
    {
        printf("list is empty.\n");
    }

    PPOINT my_point = PtCreate(1.0, 2.0);
    LIAppend(my_list, (ADT)my_point);
    printf("show the point in format (a,b): ");
    LITraverse(my_list, DoPrintObject, (ADT)"(%lf, %lf)");
    printf("\n");

    if (!LIIsEmpty(my_list))
    {
        printf("list is not empty.\n");
    }

    printf("append another point (3.5,4) to the list:\n");
    LIAppend(my_list, (ADT)PtCreate(3.5,4));
    LITraverse(my_list, DoPrintObject, (ADT)"(%lf, %lf)");
    printf("\n");

    LIAppend(my_list, (ADT)PtCreate(3,6));
    LIAppend(my_list, (ADT)PtCreate(7.5,8)); 
    LITraverse(my_list, DoPrintObject, (ADT)"(%lf, %lf)");
    printf("\n");

    LIInsert(my_list, (ADT)PtCreate(4.0,8), 2);
    LITraverse(my_list, DoPrintObject, (ADT)"(%lf, %lf)");
    printf("\n");

    printf("now have %d nodes in the list.\n", LIGetCount(my_list));

    if (LISearch(my_list, (ADT)PtCreate(7.5, 8), DoCompareObject))
        printf("found!\n");
    else 
        printf("not found.\n");
    if (LISearch(my_list, (ADT)PtCreate(10, 11), DoCompareObject))
        printf("found!\n");
    else
        printf("not found.\n");
    LIDelete(my_list, 1, DoDestroyObject);   

    LITraverse(my_list, DoPrintObject, (ADT)"(%lf, %lf)");
    printf("\n");
    
    printf("now have %d nodes in the list.\n", LIGetCount(my_list));

    LIDestroy(my_list, DoDestroyObject);

    return 0;
}