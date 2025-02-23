#include"storagepool.h"


int STORAGEPOOL::poolCount = 0;

BuddyNode** STORAGEPOOL::buddysArray = NULL;
BuddyNode* STORAGEPOOL::freeNodesList = NULL;
int STORAGEPOOL::NodesCount = 0;
int STORAGEPOOL::buddysArraySize = 0;
int STORAGEPOOL::buddysArrayCount = 0;



STORAGEPOOL::STORAGEPOOL( int size_0 )
{
    if( poolCount == 0 )
        initBuddyNodes();
    poolCount++;

    if( size_0 < 16 )  size_0 = 16;  
    dataPool = new char[size_0];

    size = log2size( size_0 ) - 1;
    SizeArray = new BuddyNode* [size - 3];

    for( int i = 0; i < size - 3; i++ )
        SizeArray[i] = NULL;

    char* tempPtr = (char*) dataPool;
    while( size_0 > 16 )
    {
        int tempSize = log2size( size_0 ) - 1;
        BuddyNode* node = newNodes();
        node->log2size = tempSize;
        node->data = tempPtr;
        SizeArray[ tempSize - 4 ] = node;
        initDataPool( tempPtr, node );

        tempPtr += ( 1 << tempSize );
        size_0 -= ( 1 << tempSize );
    }

}

STORAGEPOOL::~STORAGEPOOL()
{
    freeAllNodes();

    free( dataPool );
    free( SizeArray );

    poolCount--;
    if( poolCount == 0 )
        deleteBuddyNodes();

}

void* STORAGEPOOL::Acquire( int size_0 )  
{
    size_0 += 8; 
    int Count = log2size( size_0 ) - 4;
    if( size < Count + 4 ) return NULL;

    BuddyNode* node;
    if( SizeArray[Count] )
    {
        node = SizeArray[Count];
        pop( node );
    } else
    {
        int splitCount = Count + 1;
        while( splitCount <= size - 4 && ! SizeArray[splitCount] )
            splitCount++;

        if( splitCount > size - 4 ) return NULL;

        while( Count < splitCount ) {
            split( SizeArray[splitCount] );
            splitCount--;
        }
        node = SizeArray[Count];
    }

    pop( node );
    return startAddr( node );
}

void STORAGEPOOL::Reclaim( BuddyNode* node )
{
    node->rdy = true;
    join( node );
    int count = node->log2size - 4;
    while( count < size - 3 && merge( SizeArray[count] ))  
        count++;                                        
}

// buddy system
void STORAGEPOOL::split( BuddyNode* node )
{
    if( node->log2size <= 4 || ! node->rdy ) return;

    pop( node );

    BuddyNode* child_1 = newNodes();
    BuddyNode* child_2 = newNodes();

    child_1->parent = child_2->parent = node;
    child_1->buddy = child_2;
    child_2->buddy = child_1;

    child_1->log2size = child_2->log2size = node->log2size - 1;
    child_1->data = node->data;
    child_2->data = (void*) ((char*) node->data + (int)(1 << int(child_1->log2size)));
    initDataPool( child_1->data, child_1 );
    initDataPool( child_2->data, child_2 );


    join( child_1 );
    join( child_2 );
}

bool STORAGEPOOL::merge( BuddyNode* node )
{
    if( ! ( node->buddy && node->parent && node->buddy->rdy )) return false;

    BuddyNode* buddy = node->buddy;
    BuddyNode* parent = node->parent;
    parent->rdy = true;
    initDataPool( parent->data, parent );
    join( parent );

    pop( node );
    pop( buddy );
    freeNode( node );
    freeNode( buddy );
    return true;
}

void STORAGEPOOL::join( BuddyNode* node )
{
    int count = node->log2size - 4;
    if( SizeArray[count] ) {
        node->next = SizeArray[count];
        SizeArray[count]->front = node;
        SizeArray[count] = node;
    } else
        SizeArray[count] = node;

    node->front = NULL;
}

void STORAGEPOOL::pop( BuddyNode* node )
{
    node->rdy = false;
    if( node->next )
        node->next->front = node->front;

    if( node->front )
        node->front->next = node->next;
    else
        SizeArray[node->log2size - 4] = node->next;
}


int STORAGEPOOL::log2size( int size )
{
    int count = 4;
    size >>= 4;  

    while( size ) {
        count++;
        size >>= 1;
    }

    return count;
}


void STORAGEPOOL::initBuddyNodes()
{
    buddysArray = NULL;
    freeNodesList = NULL;

    buddysArray = new BuddyNode*[20];
    buddysArraySize = 20;
    buddysArrayCount = NodesCount = 0;

    increaseBuddysSize();
}

void STORAGEPOOL::deleteBuddyNodes()
{

    for( int i = 0; i < buddysArraySize; i++ )
        free( buddysArray[i] );

    free( buddysArray );

    buddysArray = NULL;
    freeNodesList = NULL;
}


void STORAGEPOOL::increaseBuddysSize()
{
    if( buddysArraySize <= ( buddysArrayCount + 2 ) )
        increaseBuddysArraySize();


    buddysArray[buddysArrayCount] = new BuddyNode[1 << (buddysArrayCount + 4)];
    buddysArrayCount++;
    NodesCount = 0;
}

void STORAGEPOOL::increaseBuddysArraySize()
{
    BuddyNode** temp = buddysArray;
    buddysArray = new BuddyNode*[buddysArraySize << 1];

    for( int i = 0; i < buddysArraySize; i++ )
        buddysArray[i] = temp[i];

    buddysArraySize <<= 1;
    free( temp );
}


BuddyNode* STORAGEPOOL::newNodes()
{
    if( freeNodesList )
    {
        BuddyNode* temp = freeNodesList;
        freeNodesList = freeNodesList->next;
        return initNodes( temp );
    }
    else
    {
        if( (1 << (buddysArrayCount + 3)) <= (NodesCount + 2 ))
            increaseBuddysSize();


        return initNodes( &buddysArray[buddysArrayCount - 1][NodesCount++] );
    }
}

BuddyNode* STORAGEPOOL::initNodes( BuddyNode* node )
{
    node->rdy = true;
    node->pool = this;
    node->data = node->parent = node->buddy = node->front = node->next = NULL;

    return node;
}

void STORAGEPOOL::freeNode( BuddyNode* node )
{
    node->next = freeNodesList;
    freeNodesList = node;
}

void STORAGEPOOL::freeAllNodes()
{
    for( int i = 0; i < size - 3; i++ ) {
        BuddyNode* now = SizeArray[i];
        while( now ) {
            BuddyNode* next = now->next; 
            freeNode( now );
            now = next;
        }
    }
}

inline void STORAGEPOOL::initDataPool( void* DataPool, BuddyNode* node )
{
    *(BuddyNode**)DataPool = node;
}
inline void* STORAGEPOOL::startAddr( void* DataAddr )
{
    return (void*) ((BuddyNode*) DataAddr + 1);
}