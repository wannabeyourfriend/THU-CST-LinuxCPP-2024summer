#ifndef __STORAGEPOOL_H__
#define __STORAGEPOOL_H__

#include<iostream>
#include<stdlib.h>
using namespace std;

class STORAGEPOOL;

struct BuddyNode  
{              
    bool rdy;
    short log2size;
    void* data;
    STORAGEPOOL* pool;
    BuddyNode* parent;
    BuddyNode* buddy;
    BuddyNode* front;
    BuddyNode* next;
};




class STORAGEPOOL
{
    public:
        STORAGEPOOL(int);
        ~STORAGEPOOL();

        void* Acquire( int );
        void Reclaim( BuddyNode* );


        static int poolCount;
        char* name;

        static BuddyNode** buddysArray;
        static int buddysArraySize;
        static int buddysArrayCount;
        static BuddyNode* freeNodesList;   
        static int NodesCount;



    private:
        int size;
        void* dataPool;

        BuddyNode** SizeArray;  


        
        void split( BuddyNode* );
        bool merge( BuddyNode* ); 
        void join( BuddyNode* );
        void pop( BuddyNode* );

        void initBuddyNodes();
        void deleteBuddyNodes();

        void increaseBuddysSize();
        void increaseBuddysArraySize();
        BuddyNode* newNodes();
        BuddyNode* initNodes( BuddyNode* );
        void freeNode( BuddyNode* );
        void freeAllNodes();

        int log2size( int );
        void initDataPool( void*, BuddyNode* );
        void* startAddr( void* );
};


#endif

