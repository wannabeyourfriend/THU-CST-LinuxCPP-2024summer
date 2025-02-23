#include <iostream>
#include "dynlist.h"

typedef struct NODE *PNODE;

struct NODE
{
    ADT data;
    PNODE next;
};

struct LIST
{
    int count;
    PNODE head, tail;
};

PLIST LICreate()
{
    PLIST pList = new LIST;
    pList->count = 0;
    pList->head = NULL;
    pList->tail = NULL;
    return pList;
}

void LIDestroy(PLIST list, DESTROY_OBJECT destroy)
{
    if (list)
    {
        LIClear(list, destroy);
        delete list;
    }
}

void LIAppend(PLIST list, ADT object)
{
    PNODE newNode = new NODE;
    if (!list || !object)
    {
        exit(1);
    }
    newNode->data = object;
    newNode->next = NULL;
    if (list->count == 0)
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->count++;
}

void LIInsert(PLIST list, ADT object, int pos)
{
    if (!list || !object)
    {
        exit(1);
    }
    if (pos < list->count)
    {
        PNODE newNode = new NODE;
        newNode->data = object;
        newNode->next = NULL;
        if (pos == 0)
        {
            newNode->next = list->head;
            list->head = newNode;
        }
        else
        {
            PNODE ptr = list->head;
            for(int i = 1;i < pos ; i++)
            {
                ptr = ptr->next;
            }
            newNode->next = ptr->next;
            ptr->next = newNode;
        }
        list->count++;
    }
    else
    {
        LIAppend(list, object);
    }
}

void LIDelete(PLIST list, int pos, DESTROY_OBJECT destroy)
{
    if (!list)
    {
        exit(1);
    }
    if (list->count == 0)
    {
        return;
    }
    if (pos < list->count)
    {
        PNODE ptr = list->head;
        if (pos == 0)
        {
            list->head = ptr->next;
            if (list->head == NULL)
            {
                list->tail = NULL;
            }
            if (destroy)
            {
                (*destroy)(ptr->data);
            }
            delete ptr;
            list->count--;
        }
        else
        {
            for(int i = 0; i < pos - 1; i++)
            {
                ptr = ptr->next;
            }
            //std::cout<<"here is operated"<<std::endl;
            PNODE t = ptr->next;
            ptr->next = t->next;
            if (t->next == NULL)
            {
                list->tail = ptr;
            }
            if (destroy)
            {
                (*destroy)(t->data);
                //std::cout<<"here is operated"<<std::endl;
            }

            delete t;
            //std::cout<<"here is operated"<<std::endl;

            list->count--;
        }
    }
}

/*
void LIDelete(PLIST list, int pos, DESTROY_OBJECT destroy)
{
    if (!list) 
    {
        exit(1);
    }
    if (list->count == 0)
        return;
    if (pos == 0) 
    {
        PNODE t = list->head;
        list->head = t->next;
        if (!t->next)
            list->tail = NULL;
        if (destroy)
            (*destroy)(t->data);
        delete t;
        list->count--;
    }
    else if (pos < list->count) 
    {
        PNODE u = list->head, t;
        for (int i = 0; i < pos - 1; ++i)
        {
            u = u->next;
        }
        t = u->next;
        u->next = t->next;
        if (!t->next)
            list->tail = u;
        if (destroy)
            (*destroy)(t->data);
        delete t;
        list->count--;
    }
}
*/
void LIClear(PLIST list, DESTROY_OBJECT destroy)
{
    if (!list)
    {
        exit(1);
    }
    while(list->head)
    {
        PNODE ptr = list->head;
        list->head = ptr->next;
        if (destroy)
        {
            (*destroy)(ptr->data);
        }
        delete ptr;
        list->count--;
    }
    list->tail = NULL;
}

void LITraverse(PLIST list, MANIPULATE_OBJECT manipulate, ADT tag)
{
    PNODE t = list->head;
    if (!list) 
    {
        exit(1);
    }
    while(t) {
        if (manipulate)
            (*manipulate)(t->data, tag);
        t = t->next;
    }
}

bool LISearch(PLIST list, ADT object, COMPARE_OBJECT compare)
{
    PNODE t = list->head;
    if (!list || !object) 
    {
        exit(1);
    }
    while(t) 
    {
        if ((*compare)(t->data, object))
        {
            return true;
        }
        t = t->next;
    }
    return false;
}

int LIGetCount(PLIST list)
{
    return list->count;
}

bool LIIsEmpty(PLIST list)
{
    return list->count == 0;
}
