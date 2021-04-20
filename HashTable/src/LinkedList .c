//
// Created by AlexanderT on 09.04.2021.
//

#include "LinkedList .h"

struct List* CreatList () {

    struct List* newList = (struct List*) calloc (1, sizeof(struct List*));

    if (newList == NULL) {
        return NULL;
    }

    newList->head = NULL;
    newList->tail = NULL;

    return newList;
}

bool AppendNode (struct List* thisList, list_t newValue) {

    if (thisList == NULL) {
        return false;
    }

    struct ListNode* newListNode = (struct ListNode*) calloc (1, sizeof(struct ListNode*));

    if (newListNode == NULL) {
        return false;
    }

    newListNode->next  = NULL;
    newListNode->value = newValue;

    if (thisList->tail == NULL) {
        thisList->tail = newListNode;
        thisList->head = newListNode;
    } else {
        thisList->tail->next = newListNode;
        thisList->tail       = newListNode;
    }

    return true;
}

struct ListNode* GetListHead (struct List* thisList) {

    if (thisList == NULL) {
        return NULL;
    }

    return thisList->head;
}

//Returns pointer on next node  (NULL if it does not exist)
struct ListNode* GetNextListNode (struct ListNode* thisListNode) {

    if (thisListNode == NULL) {
        return NULL;
    }

    return thisListNode->next;
}

list_t GetValueOfListNode (struct ListNode* thisListNode) {

    if (thisListNode == NULL) {
        return NULL;
    }

    return thisListNode->value;
}

bool DeleteList (struct List* thisList) {

    if (thisList == NULL) {
        return false;
    }

    struct ListNode* currToBeDeleted = thisList->head;
    struct ListNode* nextToBeDeleted = NULL;

    while (currToBeDeleted != NULL) {
        nextToBeDeleted = currToBeDeleted->next;
        free (currToBeDeleted);
        currToBeDeleted = nextToBeDeleted;
    }

    free (thisList);

    return true;
}