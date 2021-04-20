//
// Created by AlexanderT on 09.04.2021.
//

#ifndef ENGRUSTRANS_LINKEDLIST_H
#define ENGRUSTRANS_LINKEDLIST_H

#include <stdbool.h>
#include <stdlib.h>

typedef char* list_t;

struct ListNode {
    //Value saved in this node
    list_t value;
    //Pointer on next node (NULL if this node is the last)
    struct ListNode* next;
};

struct List {
    //Pointer on head node (NULL if this list is empty)
    struct ListNode* head;
    //Pointer on tail (last) node (NULL if this list is empty)
    struct ListNode* tail;
};

//Returns pointer on created list (NULL if creating failed)
struct List* CreatList ();

//Return if new node was appended to the list
bool AppendNode (struct List* thisList, list_t newValue);

//Returns pointer on head node (NULL if it does not exist)
struct ListNode* GetListHead (struct List* thisList);

//Returns pointer on next node  (NULL if it does not exist)
struct ListNode* GetNextListNode (struct ListNode* thisListNode);

//Returns value of node (NULL if it does not exist)
list_t GetValueOfListNode (struct ListNode* thisListNode);

//Free memory allocated for list
//Returns if it succeeded
bool DeleteList (struct List* thisList);

#endif //ENGRUSTRANS_LINKEDLIST_H
