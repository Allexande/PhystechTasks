//Version 1.2
#include <assert.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define DEBUG
#ifdef DEBUG
	#define ASSERT_OK(thisList) if (!ListOK(thisList)) { ConsoleDump(thisList); assert(!"ERROR"); }
#else
	#define ASSERT_OK(thisList) ;
#endif

typedef int    elem_t;
typedef size_t index_t;

enum ReallocCONSTS {
    REALLOC_UP   = 2,
    REALLOC_DOWN = 2  //NOT USED
};

struct List {

    //Nodes
    elem_t*  data;
    index_t* next;
    index_t* prev;

    //Params
    index_t head;
    index_t tail;
    index_t free;

    //Size
    size_t length;
    size_t capacity;

};

//FUNCTIONS

//Create new list
List* ListConstruct (size_t capacity);

//Get information about elements and their position
index_t GetIndexFromOrder (List* thisList, elem_t number);

//Work with list and it's data
bool TryToRealloc (List* thisList);
bool ListDestroy  (List* thisList);

//Insert in list
index_t ListInsertAtIndex     (List* thisList, elem_t newElem, index_t index);
index_t ListInsertAfterIndex  (List* thisList, elem_t newElem, index_t index);
index_t ListInsertBeforeIndex (List* thisList, elem_t newElem, index_t index);
index_t ListInsertBegin       (List* thisList, elem_t newElem);
index_t ListInsertEnd         (List* thisList, elem_t newElem);

//Delete from list
bool ListEraseAtIndex   (List* thisList, index_t index);
bool ListEraseFromBegin (List* thisList);
bool ListEraseFromEnd   (List* thisList);

//Get data from list
elem_t ListGetByOrder (List* thisList, index_t order);
elem_t ListGetByIndex (List* thisList, index_t index);
bool   ListContains   (List* thisList, elem_t element);

//Make HTML dump
bool HTMLList (List* thisList);

//Debug functions
bool ListOK      (List* thisList);
void ConsoleDump (List* thisList);
void ConsoleData (List* thisList);
