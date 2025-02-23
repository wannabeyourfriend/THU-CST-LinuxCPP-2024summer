#pragma once

typedef void * ADT;
typedef const void * CADT;


class Node
{
public:
    ADT data;
    Node * next;
    void printNode(void(*func)(ADT data));


};

