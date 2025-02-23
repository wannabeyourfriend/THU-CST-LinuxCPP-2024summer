#ifndef DYNLIST_H
#define DYNLIST_H

typedef struct LIST * PLIST;

typedef void * ADT;
typedef const void * CADT;
typedef int (*COMPARE_OBJECT)(CADT e1, CADT e2);
typedef void (*DESTROY_OBJECT)(ADT e);
typedef void (*MANIPULATE_OBJECT)(ADT e, ADT tag);

PLIST LICreate();
void LIDestroy(PLIST list, DESTROY_OBJECT destroy);
void LIAppend(PLIST list, ADT object);
void LIInsert(PLIST list, ADT object, int pos);
void LIDelete(PLIST list, int pos, DESTROY_OBJECT destroy);
void LIClear(PLIST list, DESTROY_OBJECT destroy);
void LITraverse(PLIST list, MANIPULATE_OBJECT manipulate, ADT tag);
bool LISearch(PLIST list, ADT object, COMPARE_OBJECT compare);
int LIGetCount(PLIST list);//
bool LIIsEmpty(PLIST list);//
#endif