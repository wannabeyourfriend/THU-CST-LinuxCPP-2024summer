#include"storagepool.h"


inline void* Acquire( STORAGEPOOL* pool, size_t size )
{
    return pool->Acquire( size );
}

void Reclaim( void* ptr )
{
    BuddyNode* node = ((BuddyNode*) ptr ) - 1; 
    STORAGEPOOL* pool = node->pool;
    cout<<" delete in "<< pool->name <<endl;
    pool->Reclaim( node );
}

void* operator new[] ( size_t size, STORAGEPOOL* pool )
{
     cout<<" new[] in "<< pool->name <<endl;
     return Acquire( pool, size );
}

void* operator new( size_t size, STORAGEPOOL* pool )
{
    cout<<" new in "<< pool->name <<endl;
    return Acquire( pool, size );
}

void operator delete( void* ptr )
{
    Reclaim( ptr );
}



int main( int argv, char** argc )
{
    STORAGEPOOL pool_1( 2048 );
    STORAGEPOOL pool_2( 4096 );
    char name_1[] = "pool_1";
    char name_2[] = "pool_2";

    pool_1.name = name_1;
    pool_2.name = name_2;


    int* temp1 = new( &pool_1 ) int;
    double* temp2 = new( &pool_2 ) double;

    delete temp1;
    delete temp2;

    temp1 = new( &pool_1 ) int[40];
    temp2 = new( &pool_2 ) double[20];

    delete temp1;
    delete temp2;   

    return 0;
}