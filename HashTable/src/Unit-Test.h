//
// Created by AlexanderT on 18.05.2021.
//

#ifndef ENGRUSTRANS_UNIT_TEST_H
#define ENGRUSTRANS_UNIT_TEST_H

#include "HashTable.h"
#include "LinkedList.h"
#include <sys/time.h>
#include <stdlib.h>

#define END_OF_DATA 0

void GeneralTest ();

double TestFindByKey (struct HashTable* hashTable, size_t numOfIterations);

double TestFindInListByKey (struct HashTable* hashTable, size_t numOfIterations);

double TestStrlen (size_t numOfIterations);

double TestDBJ2 (size_t numOfIterations);

double TestFastGetDJB2Hash (size_t numOfIterations);

double TestWholeTranslating (size_t numOfIterations);

double TestFastStrcmp (size_t numOfIterations);

#endif //ENGRUSTRANS_UNIT_TEST_H
