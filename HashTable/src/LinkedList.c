//
// Created by AlexanderT on 09.04.2021.
//

#include "LinkedList.h"

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

    //printf (" thisList->head=%ld thisList->tail=%ld hisList->head==NULL=%d\n", thisList->head, thisList->tail, NULL);

    if ((int)thisList->tail == (int)NULL) {
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

struct Pair* CreatePair (char* first, char* second) {

    if (first == NULL || second == NULL) {
        return NULL;
    }

    struct Pair* newPair = (struct Pair*) calloc (1, sizeof (struct Pair));

    if (newPair == NULL) {
        return NULL;
    }

    newPair->engWord = first;
    newPair->rusWord = second;

    return newPair;
}

/*
inline bool FastStrcmp (char* first, char* second) {

    if (first == NULL || second == NULL) {
        return false;
    }

    int compareResult = _mm256_movemask_epi8(
            _mm256_cmpeq_epi8(_mm256_loadu_si256((__m256i*)first),
                              _mm256_loadu_si256((__m256i*)second)));

    return compareResult == -1;
}
 */

char* FindInListByKey (struct List* thisList, char* keyWord) {

    //printf ("FindInListByKey:: keyWord=%s\n", keyWord);

    if (thisList == NULL || keyWord == NULL) {
        return NULL;
    }

    struct ListNode* pointer = thisList->head;
    while (pointer != NULL) {
        if (strcmp (pointer->value->engWord, keyWord) == 0) {
            return  pointer->value->rusWord;
        }
        pointer = pointer->next;
    }

    return NULL;
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

bool ConsoleBumpOfLinkedList (struct List* thisList) {

    if (thisList == NULL) {
        return false;
    }

    printf ("ConsoleBumpOfLinkedList(%ld) : BUMP OF LINKED LIST : ", thisList);
    printf ("Head=%ld Tail=%ld : ", thisList->head, thisList->tail);

    struct ListNode* pointer = thisList->head;
    while (pointer != NULL && pointer->value->rusWord != NULL && pointer->value->engWord != NULL) {
        printf ("(%s|%s) -> ", pointer->value->rusWord, pointer->value->engWord);
        pointer = pointer->next;
    }

    return true;
}