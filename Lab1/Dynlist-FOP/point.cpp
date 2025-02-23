#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include "point.h"

using namespace std;

static char * DuplicateString(const char *s);
struct POINT{double x, y;};

PPOINT PtCreate(double x, double y)
{
    PPOINT t = new POINT;
    t->x = x;
    t->y = y;
    return t;
}

void PtDestroy(PPOINT point)
{
    if (point)
    {
        delete point;
    }
    //std::cout << "Point destroyed" << std::endl;
}

void PtGetValue(PPOINT point, double *x, double *y)
{
    if (point) 
    {
        if (x) *x = point->x;
        if (y) *y = point->y;
    }
}

void PtSetValue(PPOINT point, double x, double y)
{
    if (point) 
    {
        point->x = x;
        point->y = y;
    }
}

bool PtCompare(PPOINT point1, PPOINT point2)
{
    if (!point1 || !point2) 
    {
        exit(1);
    }
    return (point1->x == point2->x) && (point1->y == point2->y);
}

char * PtTransformIntoString(const char *format, PPOINT point)
{
    char buf[BUFSIZ];
    if (point) 
    {
        sprintf(buf, format, point->x, point->y);
        return DuplicateString(buf);
    }
    else
    {
        char* result = new char[20]; 
        strcpy(result, "NULL");
        return result;
    }
}

void PtPrint(PPOINT point)
{
    if (point)
        printf("(%lf, %lf)", point->x, point->y);
    else
        printf("NULL");
}

char* DuplicateString(const char *s)
{
    int n = strlen(s);
    char *t = new char[n+1];
    for (int i = 0; i < n; ++i)
        t[i] = s[i];
    t[n] = '\0';
    return t;
}