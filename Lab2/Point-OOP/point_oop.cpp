#include <iostream>
#include <cstdio>
#include <cstring>
#include "point_oop.h"

using namespace std;

bool operator ==(const Point &a, const Point &b)
{
    return (a.x == b.x) && (a.y == b.y);
}

ostream & operator <<(ostream & os, const Point &a)
{
    os << "(" << a.x << " , " << a.y << ")";
    return os;
}

char * Point::TransformIntoString(const char *format) const
{
    char buf[BUFSIZ];
    sprintf(buf, format, x, y);
    return DuplicateString(buf);
}

char* Point::DuplicateString(const char *s)
{
    int n = strlen(s);
    char *t = new char[n+1];
    for (int i = 0; i < n; ++i)
        t[i] = s[i];
    t[n] = '\0';
    return t;
}