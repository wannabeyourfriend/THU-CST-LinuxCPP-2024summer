#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <cstdio>

using namespace std;

class Point
{
private:
    int x, y;
public:
    Point(int _x, int _y): x(_x), y(_y) {}
    ~Point()
    {
        printf("(%d, %d)析构\n", x, y);//用来观察析构情况
    }
    void GetValue(int *a, int *b) { *a = x, *b = y; }
    void SetValue(int _x, int _y) { x = _x, y = _y; }
    friend bool operator ==(const Point &a, const Point &b);//判断相等
    friend ostream & operator <<(ostream & os, const Point &a);
    char * TransformIntoString(const char *format) const;//转换成字符串
    static char * DuplicateString(const char *s);
};
#endif
