#include "list.h"
#include <cstdlib>
#include <cstdio>
int transfromADTtoINT(ADT data);
void printint(ADT data);
int main(void)
{
    Node node_0;
    Node node_1;
    Node node_2;
    Node node_3;
    Node node_4;
    Node node_5;

    int array[6] = {2,3,4,5,6,7};
    
    node_0.data = new int(array[0]);
    node_1.data = new int(array[1]);
    node_2.data = new int(array[2]);
    node_3.data = new int(array[3]);
    node_4.data = new int(array[4]);
    node_5.data = new int(array[5]);
    Node temp;
 
	List *pList = new List();
	pList->ListInsertTail(&node_0);
	pList->ListInsertTail(&node_1);
	pList->ListInsertTail(&node_2);
	pList->ListInsertTail(&node_3);
	pList->ListInsertTail(&node_4);
 
	pList->ListInsert(1, &node_5);
    pList->NextElem(&node_5, &temp);
	pList->ListTraverse();
    printf("\n");

    printf("temp:");
    temp.printNode(printint);
    printf("\n");
	delete pList;
	pList = NULL;
    return 0;
}
