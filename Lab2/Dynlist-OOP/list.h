#pragma once
#include "node.h"

class List
{
private:
    Node * plist;
    int listlength;
public:
    List();
    ~List();
    void ClearList();
    bool ListEmpty();                                    
	bool ListInsertHead(Node *pNode);                     
	bool ListInsertTail(Node *pNode);                    
	bool ListInsert(int idx, Node *pNode);                 
	bool ListDelete(int idx, Node *pNode);                 
	bool ListGetElem(int idx, Node *pNode);                
	int  LocateElem(Node *pNode);                        
	bool PriorElem(Node *pCurrentNode, Node *pPreNode);  
	bool NextElem(Node *pCurrentNode, Node *pNextNode);
	void ListTraverse();  
};