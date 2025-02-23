#include "list.h"
#include <cstddef>
#include <cstdio>
int transfromADTtoINT(ADT data)
{
    return *reinterpret_cast<int*>(data);
}

void printint(ADT data)
{
    printf("%d -> ",transfromADTtoINT(data));
}

List::List()
{
	plist = new Node;
	plist->data = nullptr;
	plist->next = NULL;
	listlength = 0;
}
 
bool List::ListEmpty()
{
	if (listlength == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
 
void List::ClearList()
{
	Node *currentNode = plist->next; 
	while (currentNode != NULL)
	{
		Node *temp = currentNode->next;
		delete currentNode;
		currentNode = temp;
	}
	plist->next = NULL;               
}
 
List::~List()
{
	ClearList();
	delete plist;
	plist = NULL;
}
 
bool List::ListInsertHead(Node *pNode)
{
	Node *temp = plist->next;            
	Node *newNode = new Node;              
	if (newNode == NULL)
		return false;
	newNode->data = pNode->data;
	plist->next = newNode;
	newNode->next = temp;
	listlength++;
	return true;
}
 
bool List::ListInsertTail(Node *pNode)
{
	Node *currentNode = plist;
	while (currentNode->next != NULL)
		currentNode = currentNode->next;  
	Node *newNode = new Node;
	if (newNode == NULL)
		return false;
	newNode->data = pNode->data;
	newNode->next = NULL;
	currentNode->next = newNode;
	listlength++;
	return true;
}
 
bool List::ListInsert(int i, Node *pNode)
{
	if (i<0 || i>listlength)
		return false;
	Node *currentNode = plist;
	for (int k = 0; k < i; k++)
	{
		currentNode = currentNode->next;
	}
 
	Node *newNode = new Node;
	if (newNode == NULL)
		return false;
	newNode->data = pNode->data;
	newNode->next = currentNode->next;
	currentNode->next = newNode;
	listlength++;
	return true;
 
}
 
bool List::ListDelete(int i, Node *pNode)
{
	if (i < 0 || i >listlength)
		return false;
	Node *currentNode = plist;
	Node *currentNodeBefore = NULL;
	for (int k = 0; k <= i; k++)
	{
		currentNodeBefore = currentNode;
		currentNode = currentNode->next;
	}
	currentNodeBefore->next = currentNode->next;
	pNode->data = currentNode->data;
	delete currentNode;
	currentNode = NULL;
	listlength--;
	return true;
}
 
bool List::ListGetElem(int i, Node *pNode)
{
	if (i < 0 || i >listlength)
		return false;
	Node *currentNode = plist;
	for (int k = 0; k <= i; k++)
	{
		currentNode = currentNode->next;
	}
	pNode->data = currentNode->data;
	return true;
}
 
int List::LocateElem(Node *pNode)
{
	Node *currentNode = plist;
	int count = 0;
	while (currentNode->next!= NULL)
	{
		currentNode = currentNode->next;
		if (currentNode->data == pNode->data)
		{
			return count;
		}
		count++;
	}
	return -1;
}
 
bool List::PriorElem(Node *pCurrentNode, Node *pPreNode)
{
	Node *currentNode = plist;
	Node *tempNode = NULL;
	while (currentNode->next != NULL)
	{
		tempNode = currentNode;
		currentNode = currentNode->next;
		if (currentNode->data == pCurrentNode->data)
		{
			if (tempNode == plist)
				return false;
			else
			{
				pPreNode->data = tempNode->data;
				return true;
			}
			
		}
	}
	return false;
}
 
bool List::NextElem(Node *pCurrentNode, Node *pNextNode)
{
	Node *currentNode = plist;
	while (currentNode->next != NULL)
	{
		currentNode = currentNode->next;
		if (currentNode->data == pCurrentNode->data)
		{
			if (currentNode->next == NULL)
			{
				return false;
			}
			else
			{
				pNextNode->data = currentNode->next->data;
				return true;
			}
 
		}
	}
	return false;
}
 
void List::ListTraverse()
{
	Node *currentNode = plist;
	while (currentNode->next != NULL)
	{
		currentNode = currentNode->next;
		currentNode->printNode(printint);
	}
 
}