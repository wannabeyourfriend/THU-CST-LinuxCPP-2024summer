#ifndef DYNLIST_H
#define DYNLIST_H
#include <cstdlib>

template<typename T>
struct MyListNode   
{
    T data;                   
    MyListNode<T> * next;     

    MyListNode(const T & _data): data(_data), next(0) {}
};

template<typename T>
struct MyIterator   
{
    typedef MyListNode<T> * link_type;

    link_type ptr;    

    MyIterator<T>(link_type p = 0):ptr(p) {}

    T & operator*() {return (*ptr).data;} 
    MyIterator& operator++()
    {
        ptr = ptr->next;
        return *this;
    }
    MyIterator operator++(int)
    {
        MyIterator tmp = *this;
        ++*this;
        return tmp;
    }
    bool operator==(const MyIterator & x) const {return ptr == x.ptr;}
    bool operator!=(const MyIterator & x) const {return ptr != x.ptr;}
};

template<typename T>
class MyList    
{
private:
    int count; 
    MyListNode<T> * head;
    MyListNode<T> * tail;

public:
    MyList(): count(0), head(NULL), tail(NULL) {}
    ~MyList()
    {
        Clear();
        printf("Deletion completed\n");
    }

    MyIterator<T> begin() {return head;}
    MyIterator<T> end() {return tail->next;}
    void Append(const T & object);
    void Insert(const T & object, int pos);
    void Delete(int pos);
    void Clear();
    int GetCount() { return count; }
    bool IsEmpty() { return count == 0; }
};

template<typename T>
void MyList<T>::Append(const T & object)
{
    MyListNode<T> * p = new MyListNode<T>(object);
    p->next = NULL;
    if (!head) {
        head = p;
        tail = p;
    }
    else {
        tail->next = p;
        tail = p;
    }
    count++;
}

template<typename T>
void MyList<T>::Insert(const T & object, int pos)
{
    if (pos < count) {
        MyListNode<T> * p = new MyListNode<T>(object);
        p->next = NULL;
        if (pos == 0) {
            p->next = head;
            head = p;
        }
        else {
            MyListNode<T> * u = head;
            for (int i = 0; i < pos - 1; ++i)
                u = u->next;
            p->next = u->next;
            u->next = p;
        }
        count++;
    }
    else
        Append(object);
}

template<typename T>
void MyList<T>::Delete(int pos)
{
    if (count == 0)
        return;
    if (pos == 0) {
        MyListNode<T> * p = head;
        head = p->next;
        if (!p->next)
            tail = NULL;
        delete p;
        count--;
    }
    else if (pos < count) {
        MyListNode<T> * u = head;
        MyListNode<T> * p;
        for (int i = 0; i < pos - 1; ++i)
            u = u->next;
        p = u->next;
        u->next = p->next;
        if (!p->next)
            tail = u;
        delete p;
        count--;
    }
}

template<typename T>
void MyList<T>::Clear()
{
    while(head) {
        MyListNode<T> * p = head;
        head = p->next;
        delete p;
        count--;
    }
    tail = NULL;
}

#endif
