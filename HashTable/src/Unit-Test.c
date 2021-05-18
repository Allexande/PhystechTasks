//
// Created by AlexanderT on 07.05.2021.
//

#include "Unit-Test.h"

void GeneralTest () {

    struct HashTable* hashTable = BuildHashTable ("C:\\Cprojects\\dictionary\\dic.txt", 199, GetDJB2Hash);

    //printf ("TestWholeTranslating After 10000 iterations: %lf\n", TestWholeTranslating(1));

    //printf ("TestFindByKey After 10000 iterations: %lf\n", TestFindByKey (hashTable, 10000));
    //printf ("TestFindInListByKey After 10000 iterations: %lf\n", TestFindInListByKey (hashTable, 10000));
    //printf ("TestStrlen After 10000 iterations: %lf\n", TestStrlen (100000));
    //printf ("TestDBJ2 After 10000 iterations: %lf\n", TestDBJ2 (10000));
    //printf ("TestFastStrcmp After 10000 iterations: %lf\n", TestFastStrcmp (10000));
    printf ("TestFastGetDJB2Hash After 10000 iterations: %lf\n", TestFastGetDJB2Hash (10000));
}

double TestFindByKey (struct HashTable* hashTable, size_t numOfIterations) {

    char* TestingKeys[] ={
        "hello",
        "i",
        "am",
        "the",
        "best",
        "human",
        "in",
        "the",
        "world",
        END_OF_DATA
    };

    struct timeb start, end;
    double totalTime = 0;

    for (size_t i = 0; i < numOfIterations; i++) {
        size_t numOfKey = 0;
        while (TestingKeys[numOfKey] != END_OF_DATA) {
            ftime(&start);
            FindByKey (hashTable, TestingKeys[numOfKey]);
            ftime(&end);
            totalTime += (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
            numOfKey++;
        }
    }

    return totalTime;
}

double TestFindInListByKey (struct HashTable* hashTable, size_t numOfIterations) {

    char* TestingKeys[] ={
            "hello",
            "i",
            "zoo",
            "the",
            "zoo",
            "zoo",
            "in",
            "the",
            "world",
            END_OF_DATA
    };

    struct timeb start, end;
    double totalTime = 0;

    size_t numOfKey = 0;
    while (TestingKeys[numOfKey] != END_OF_DATA) {
        size_t place = hashTable->func(TestingKeys[numOfKey]) % hashTable->tableLength;

        ftime(&start);

        for (size_t i = 0; i < numOfIterations; i++) {
            FindInListByKey (hashTable->buckets[place], TestingKeys[numOfKey]);
        }

        ftime(&end);
        totalTime += (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));

        numOfKey++;
    }

    return totalTime;
}

double TestStrlen (size_t numOfIterations) {

    char* TestingKeys[] ={
            "hello",
            "i",
            "am",
            "the",
            "best",
            "human",
            "in",
            "the",
            "world",
            END_OF_DATA
    };

    struct timeb start, end;
    double totalTime = 0;

    for (size_t i = 0; i < numOfIterations; i++) {
        size_t numOfKey = 0;
        while (TestingKeys[numOfKey] != END_OF_DATA) {
            ftime(&start);
            strlen (TestingKeys[numOfKey]);
            ftime(&end);
            totalTime += (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
            numOfKey++;
        }
    }

    return totalTime;
}

double TestDBJ2 (size_t numOfIterations) {

    char* TestingKeys[] ={
            "hello",
            "i",
            "am",
            "the",
            "best",
            "human",
            "in",
            "the",
            "world",
            END_OF_DATA
    };

    struct timeb start, end;
    double totalTime = 0;

    for (size_t i = 0; i < numOfIterations; i++) {
        size_t numOfKey = 0;
        while (TestingKeys[numOfKey] != END_OF_DATA) {
            ftime(&start);
            strcmp (TestingKeys[numOfKey], TestingKeys[numOfKey]));
            ftime(&end);
            totalTime += (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
            numOfKey ++;
        }
    }

    return totalTime;
}

/*
double TestFastStrcmp (size_t numOfIterations) {

    char* TestingKeys[] = {
            "hello",
            "i",
            "am",
            "the",
            "best",
            "human",
            "in",
            "the",
            "world",
            END_OF_DATA
    };

    struct timeb start, end;

    ftime(&start);

    for (size_t i = 0; i < numOfIterations; i++) {
        size_t numOfKey = 0;
        while (TestingKeys[numOfKey] != END_OF_DATA) {
            printf("%d\n", FastStrcmp (TestingKeys[numOfKey], TestingKeys[numOfKey]));
            numOfKey ++;
        }
    }

    ftime(&end);

    return (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
}
 */

double TestWholeTranslating (size_t numOfIterations) {

    struct timeb start, end;

    ftime(&start);

    for (size_t i = 0; i < numOfIterations; i++) {
        TranslateWebPage ("C:\\Users\\AlexanderT\\CLionProjects\\EngRusTrans\\data\\test.html", "C:\\Users\\AlexanderT\\CLionProjects\\EngRusTrans\\data\\out.html");
    }

    ftime(&end);

    return (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
}

double TestFastGetDJB2Hash (size_t numOfIterations) {

    char* TestingKeys[] = {
            "hello",
            "i",
            "am",
            "the",
            "best",
            "human",
            "in",
            "the",
            "world",
            END_OF_DATA
    };

    struct timeb start, end;

    ftime(&start);
    double totalTime = 0;

    for (size_t i = 0; i < numOfIterations; i++) {
        size_t numOfKey = 0;
        while (TestingKeys[numOfKey] != END_OF_DATA) {
            FastGetDJB2Hash (TestingKeys[numOfKey]);
            totalTime += (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
            numOfKey ++;
        }
    }

    ftime(&end);

    return totalTime;
}


