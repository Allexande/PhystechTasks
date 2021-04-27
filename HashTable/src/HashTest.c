//
// Created by AlexanderT on 11.04.2021.
//

#include "HashTest.h"

struct HashFunction* GetHashFunction (char* newName, hash_t (*newFunc)()) {

    if (newName == NULL || newFunc == NULL) {
        return NULL;
    }

    struct HashFunction* newFunction = (struct HashFunction*) calloc (1, sizeof(struct HashFunction));

    if (newFunction == NULL) {
        return NULL;
    }

    newFunction->name = newName;
    newFunction->func = newFunc;

    newFunction->elemsInBasket = NULL;

    size_t* lengthsOfHashTablesArray = (size_t*) calloc (9, sizeof(size_t));

    lengthsOfHashTablesArray[0] = 7;
    lengthsOfHashTablesArray[1] = 17;
    lengthsOfHashTablesArray[2] = 29;
    lengthsOfHashTablesArray[3] = 41;
    lengthsOfHashTablesArray[4] = 101;
    lengthsOfHashTablesArray[5] = 1949;
    lengthsOfHashTablesArray[6] = 9973;
    lengthsOfHashTablesArray[7] = 107;
    lengthsOfHashTablesArray[8] = END_OF_DATA;
    /*
     * size_t lengthsOfHashTablesArray = {
                7,
                17,
                29,
                41,
                101,
                1949,
                9973,
                107,    //THE LAST (results will be saved in statistics)
                END_OF_DATA
    };
     */

    newFunction->lengthsOfHashTables = lengthsOfHashTablesArray;

    newFunction->time           = 0.f;
    newFunction->worstCollision = 0;
    newFunction->bestCollision  = 0;
    newFunction->deviation      = 0;
    newFunction->dispersion     = 0.f;
    newFunction->scalability    = 0.f;

    return newFunction;
}

bool SetInfoForThisSize (struct HashFunction* func, size_t lengthOfHashTable, struct Lines* words, size_t* arrayOfBasketToFill) {

    if (func == NULL || lengthOfHashTable == 0 || words == NULL) {
        return false;
    }

    struct timeb start, end;

    ftime(&start);

    //Uncomment this if you want better time results
    /*
    for (size_t i = 0; i < words->numberOfLines; i++) {
        arrayOfBasketToFill[((func->func)(words->line[i]) % lengthOfHashTable)]++;
        arrayOfBasketToFill[((func->func)(words->line[i]) % lengthOfHashTable)]--;
    }

    for (size_t i = 0; i < words->numberOfLines; i++) {
        arrayOfBasketToFill[((func->func)(words->line[i]) % lengthOfHashTable)]++;
        arrayOfBasketToFill[((func->func)(words->line[i]) % lengthOfHashTable)]--;
    }
     */

    for (size_t i = 0; i < words->numberOfLines; i++) {
        arrayOfBasketToFill[((func->func)(words->line[i]) % lengthOfHashTable)]++;
    }

    ftime(&end);

    func->time +=  (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));

    func->dispersion = CountDispersion (arrayOfBasketToFill, lengthOfHashTable);

    func->worstCollision = 0;
    func->bestCollision  = words->numberOfLines + 1;
    for (size_t i = 0; i < lengthOfHashTable; i++) {
        if (func->bestCollision  > arrayOfBasketToFill[i]) func->bestCollision  = arrayOfBasketToFill[i];
        if (func->worstCollision < arrayOfBasketToFill[i]) func->worstCollision = arrayOfBasketToFill[i];
    }

    func->deviation = func->worstCollision - func->bestCollision;

    return true;
}

bool TestFunction (struct HashFunction* func, struct Lines* words) {

    if (func == NULL || words == NULL) {
        return false;
    }

    size_t numberOfLengthsOfHashTables = 0;
    while (func->lengthsOfHashTables[numberOfLengthsOfHashTables] != END_OF_DATA) {
        numberOfLengthsOfHashTables++;
    }

    func->elemsInBasket = (size_t**) calloc (numberOfLengthsOfHashTables, sizeof (size_t*));

    bool success = true;
    double previousDeviation;
    double currentDeviation = func->deviation;;
    for (size_t i = 0; i < numberOfLengthsOfHashTables; i++) {
        func->elemsInBasket[i] = (size_t*) calloc (func->lengthsOfHashTables[i], sizeof (size_t));
        success *= SetInfoForThisSize (func, func->lengthsOfHashTables[i], words, func->elemsInBasket[i]);

        previousDeviation = currentDeviation;
        currentDeviation  = func->deviation;

        if (i > 0) {
            func->scalability += fabs(sqrt((double)func->lengthsOfHashTables[i-1] / (double)func->lengthsOfHashTables[i])
                                                - ((double)currentDeviation              / (double)previousDeviation));
        }

    }

    return success;
}

bool TestFunctions (char* fileDatabase, struct HashFunction** TestingFunctionsList) {

    if (fileDatabase == NULL || TestFunctions == NULL) {
        return false;
    }

    struct Lines* TestingWords = GetLinesFromText (ReadTextFromFile (fileDatabase));

    assert (TestingWords);

    for (size_t i = 0; i < NUMBER_OF_HASH_FUNCTIONS; i++) {
        if (!TestFunction (TestingFunctionsList[i], TestingWords)) {
            printf ("Error: Hash function №%d (%s) was not tasted.\n", i + 1, TestingFunctionsList[i]->name);
        }
    }

    return true;
}

bool CreateReport (char* fileDatabase) {

    if (fileDatabase == NULL) {
        return false;
    }

    struct HashFunction* TestingFunctionsList[NUMBER_OF_HASH_FUNCTIONS] = {
            GetHashFunction ("GetConstantHash",    GetConstantHash),
            GetHashFunction ("GetLengthHash",      GetLengthHash),
            GetHashFunction ("GetFirstLetterHash", GetFirstLetterHash),
            GetHashFunction ("GetSumHash",         GetSumHash),
            GetHashFunction ("GetBitRotateHash",   GetBitRotateHash),
            GetHashFunction ("GetSumWithPlaceHash",GetSumWithPlaceHash),
            GetHashFunction ("GetJenkinsHash",     GetJenkinsHash),
            GetHashFunction ("GetDJB2Hash",        GetDJB2Hash),
            GetHashFunction ("GetSBDMHash",        GetSBDMHash),
            GetHashFunction ("GetRandomHash",      GetRandomHash),
            GetHashFunction ("GetTuzmanHash",      GetTuzmanHash)
    };

    if (!TestFunctions (fileDatabase, TestingFunctionsList)) {
        return false;
    }

    for (size_t i = 0; i < NUMBER_OF_HASH_FUNCTIONS; i++) {
        printf (
                "[%d] %s (%ld) time:%lf "
                "worstCollision:%ld bestCollision:%ld dispersion:%d deviation:%lf scalability:%lf\n",
                i,
                TestingFunctionsList[i]->name,
                TestingFunctionsList[i]->func,
                TestingFunctionsList[i]->time,
                TestingFunctionsList[i]->worstCollision,
                TestingFunctionsList[i]->bestCollision,
                TestingFunctionsList[i]->deviation,
                TestingFunctionsList[i]->dispersion,
                TestingFunctionsList[i]->scalability
                );
    }

    return CreateReportFile (TestingFunctionsList, REPORT_PATH);
}

double CountDispersion (size_t* data, size_t length) {

    assert (data);

    hash_t sum = 0;
    for (int i = 0; i < length; i++) {
        sum += data[i];
    }

    double mean = (double)sum / (double)length;

    double sqDiff = 0;
    for (int i = 0; i < length; i++) {
        sqDiff += (data[i] - mean) *
                  (data[i] - mean);
    }

    return sqrt(sqDiff / length);
}

bool CreateReportFile (struct HashFunction** functionInfo, char* filename) {

    if (functionInfo == NULL || filename == NULL) {
        return false;
    }

    FILE* file = fopen (filename, "w");

    if (file == NULL) {
        return false;
    }

    for (size_t i = 0; i < NUMBER_OF_HASH_FUNCTIONS; i++) {
        size_t position = 0;
        size_t shift = 0;
        while (functionInfo[i]->lengthsOfHashTables[position] != END_OF_DATA) {//printf ("> > > position=%ld!\n", position);
            for (size_t j = 0; j < functionInfo[i]->lengthsOfHashTables[position]; j++) {//printf ("j=%ld! shift=%ld\n", j, shift);
                fprintf (file, "%ld;", functionInfo[i]->elemsInBasket[position][j]);
                shift++;
            }
            fprintf (file, ";\n");
            position++;
        }
    }

    for (size_t i = 0; i < NUMBER_OF_HASH_FUNCTIONS; i++) {
        fprintf (file, "%d;%s;%lf;%ld;%ld;%d;%lf;%lf;\n",
                 i,
                 functionInfo[i]->name,
                 functionInfo[i]->time,
                 functionInfo[i]->worstCollision,
                 functionInfo[i]->bestCollision,
                 functionInfo[i]->deviation,
                 functionInfo[i]->dispersion,
                 functionInfo[i]->scalability
        );
    }

    fclose (file);

    return true;
}
