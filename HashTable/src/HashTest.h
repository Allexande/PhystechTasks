//
// Created by AlexanderT on 11.04.2021.
//

#ifndef ENGRUSTRANS_HASHTEST_H
#define ENGRUSTRANS_HASHTEST_H

#include <stdlib.h>

#define _BSD_SOURCE
#include <sys/time.h>
#include <sys\timeb.h>

#include <stdbool.h>
#include <math.h>
#include <assert.h>

#include "HashFuncs.h"
#include "FileMaster.h"

#define END_OF_DATA 0

#define REPORT_PATH "C:\\Cprojects\\test.csv"

struct HashFunction {
    //Name of function
    char* name;
    //Pointer on function
    hash_t (*func)();
    //Number of element in every basked
    //For every test an array
    size_t** elemsInBasket;
    //List of lengths of hash tables function will be tasted on
    size_t* lengthsOfHashTables;
    //Total time of N repeats of this function (N - number of elements to hash)
    double time;
    //Max number of collision for this function
    size_t worstCollision;
    //Min number of collision for this function
    size_t bestCollision;
    //Difference between max and min numbers of collision for this function
    size_t dispersion;
    //Square root of variance
    double deviation;
    //Dynamic of changing deviation in case of changing params of hash input
    double scalability;
};

struct HashFunction* GetHashFunction (char* newName, hash_t (*newFunc)());

bool SetInfoForThisSize (struct HashFunction* func, size_t lengthOfHashTable, struct Lines* words, size_t* arrayOfBasketToFill);

bool TestFunction (struct HashFunction* func, struct Lines* words);

bool TestFunctions (char* fileDatabase, struct HashFunction** TestingFunctionsList);

bool CreateReport (char* fileDatabase);

double CountDeviation (size_t* data, size_t length);

bool CreateReportFile (struct HashFunction** functionInfo, char* filename);

#endif //ENGRUSTRANS_HASHTEST_H
