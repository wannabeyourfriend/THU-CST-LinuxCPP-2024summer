#include <iostream>
#include "dynlist_template.h"
#include "point_oop.h"
#include <cstdio>
#include <cstdlib>
using namespace std;

template<class Iterator, class Function>
void for_each(Iterator first, Iterator last, Function f)
{
    for(; first != last; ++first)
        f(*first);
}

template<class Iterator, class T>
bool find(Iterator first, Iterator last, const T& value)
{
    while (first != last){
        if (*first == value)
            return true;
        ++first;
    }
    return false;
}//实现自己的find算法

class PrintPoint //在for_each中要调用的函数对象
{
private:
    const char * tag;
public:
    PrintPoint(const char * x): tag(x) {}
    void operator()(const Point & obj)
    {
        printf("%s",obj.TransformIntoString(tag));
        printf("->");
    }
};

int main(void)
{
    MyList<Point> my_list;

    if (my_list.IsEmpty())
        printf("抽象链表目前是空的。\n");

    Point my_point(1,2);
    my_list.Append(my_point);
    printf("插入一个点（1,2），现在显示目前链表状况：存储的点元素用（a，b）形式显示：");
    for_each(my_list.begin(), my_list.end(), PrintPoint("(%d, %d)"));
    printf("\n");

    if (!my_list.IsEmpty())
        printf("经判断，抽象链表已经不是空的了。\n");

    printf("再续上一个元素（5,4）：\n");
    my_list.Append(*(new Point(5,4)));
    printf("显示目前链表状况：存储的点元素用<a,b>形式显示：");
    for_each(my_list.begin(), my_list.end(), PrintPoint("<%d, %d>"));
    printf("\n");

    printf("再续上俩元素（3,6）和（7,8）：\n");
    my_list.Append(*(new Point(3,6)));
    my_list.Append(*(new Point(7,8)));
    printf("显示目前链表状况：存储的点元素以[a,b]形式显示：");
    for_each(my_list.begin(), my_list.end(), PrintPoint("[%d, %d]"));
    printf("\n");

    printf("在第2个位置（从第0开始）插入一个元素（4,8）：\n");
    my_list.Insert(*(new Point(4,8)), 2);
    printf("显示目前链表状况：存储的点元素用{a，b}形式显示：");
    for_each(my_list.begin(), my_list.end(), PrintPoint("{%d, %d}"));
    printf("\n");

    printf("现在抽象链表一共有%d个节点（元素）。\n", my_list.GetCount());

    printf("现在搜索这个链表里有没有(7,8)这个元素：");
    if (find(my_list.begin(), my_list.end(), Point(7,8)))
        printf("找到了！\n");

    printf("现在搜索这个链表里有没有(10, 11)这个元素：");
    if (find(my_list.begin(), my_list.end(), Point(10,11)))
        printf("找到了！\n");
    else
        printf("没找到！\n");

    printf("现在把第1个节点删除：\n");
    my_list.Delete(1);
    printf("显示目前链表状况：存储的点元素用{a，b}形式显示：");
    for_each(my_list.begin(), my_list.end(), PrintPoint("{%d, %d}"));
    printf("\n");

    printf("现在抽象链表一共有%d个节点（元素）。\n", my_list.GetCount());

    return 0;
}