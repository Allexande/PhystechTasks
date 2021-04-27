//
// Created by AlexanderT on 20.04.2021.
//

#include "LinkedList.h"
#include "HashFuncs.h"

#ifndef ENGRUSTRANS_HASHTABLE_H
#define ENGRUSTRANS_HASHTABLE_H

typedef struct List* bucket_t;

struct HashTable {
    //Array of bucket
     bucket_t* buckets;
    //Size of hash table (length of bucket array)
    size_t tableLength;
    //Pointer on function
    hash_t (*func)();
};

struct HashTable* CreateHashTable (size_t length, hash_t (*newFunc)());

bool AddPair (struct HashTable* hashTable, char* endWord, char* rusWord);

char* FindByKey (struct HashTable* hashTable, char* keyWord);

struct HashTable* BuildHashTable (char* filename, size_t length, hash_t (*newFunc)());

bool ConsoleBumpOfHashTable (struct HashTable* hashTable);

char* PhoneticTranslation (char* engWord);

bool TranslateWebPage (char* filename, char* fileoutput);

#endif //ENGRUSTRANS_HASHTABLE_H
