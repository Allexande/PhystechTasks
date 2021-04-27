//
// Created by AlexanderT on 20.04.2021.
//

#include "HashTable.h"
#include "Filemaster.h"

struct HashTable* CreateHashTable (size_t length, hash_t (*newFunc)()) {

    if (length < 1) {
        return NULL;
    }

    struct HashTable* newHashTable = (struct HashTable*) calloc (1, sizeof (struct HashTable));

    if (newHashTable == NULL) {
        return NULL;
    }

    newHashTable->buckets = (bucket_t*) calloc (length, sizeof (bucket_t));

    if (newHashTable->buckets == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < length; i++) {
        newHashTable->buckets[i] = CreatList ();
        if (newHashTable->buckets[i] == NULL) {
            return NULL;
        }
    }

    newHashTable->tableLength = length;
    newHashTable->func = newFunc;

    return newHashTable;
}

bool AddPair (struct HashTable* hashTable, char* endWord, char* rusWord) {

    //printf ("AddPair::: endWord=%s rusWord=%s\n", endWord, rusWord);

    if (hashTable == NULL || endWord == NULL || rusWord == NULL) {
        return false;
    }


    //struct Pair* testingP = CreatePair (endWord, rusWord);
    //printf ("AddPair:::testingP->engWord=%s testingP->rusWord=%\n", testingP->engWord, testingP->rusWord);

    return AppendNode (hashTable->buckets[hashTable->func(endWord) % hashTable->tableLength], CreatePair (endWord, rusWord));
}

char* FindByKey (struct HashTable* hashTable, char* keyWord) {

    if (hashTable == NULL || keyWord == NULL) {
        return NULL;
    }

    size_t keyLength = strlen (keyWord);
    char* wordToCut = (char*) calloc (keyLength, sizeof (char));
    memcpy (wordToCut, keyWord, keyLength);
    wordToCut[keyLength] = '\0';
    char* value = NULL;

    for (size_t i = 0; i < keyLength / 2; i++) {
        value = FindInListByKey (hashTable->buckets[hashTable->func(wordToCut) % hashTable->tableLength], wordToCut);
        if (value != NULL) {
            break;
        }
        wordToCut[keyLength - i - 1] = '\0';
    }

    memcpy (wordToCut, keyWord, keyLength);
    wordToCut[keyLength] = '\0';

    if (value == NULL) {
        for (size_t i = 0; i < keyLength / 2; i++) {
            printf ("%s\n", wordToCut);
            value = FindInListByKey(hashTable->buckets[hashTable->func(wordToCut) % hashTable->tableLength], wordToCut);
            if (value != NULL) {
                break;
            }
            wordToCut += 1;
        }
    }

    if (value == NULL) {
        value = PhoneticTranslation (keyWord);
    }

    return value;
}

//WARNING first line is second arg for strtok
struct HashTable* BuildHashTable (char* filename, size_t length, hash_t (*newFunc)()) {

    if (filename == NULL) {
        return NULL;
    }

    struct HashTable* newHashTable = CreateHashTable (length, newFunc);

    /*
    FILE* file = fopen (filename, "w");

    if (file == NULL) {
        return false;
    }
    */


    //!!! NOT EFFICIENT
    //char* filetext = ReadTextFromFile ();

    struct Lines* fileLines = GetLinesFromText (ReadTextFromFile(filename));

    if (fileLines->numberOfLines < 2) {
        printf ("File %s have less than 2 lines (%ld)\n", filename, fileLines->numberOfLines);
        return NULL;
    }

    char** wordsList = (char**) calloc (fileLines->numberOfLines * 2, sizeof(char*));

    for (size_t i = 1; i < fileLines->numberOfLines; i++) {
        wordsList[(i-1)*2] = fileLines->line[i];

        char offset = 0;
        while (fileLines->line[i][offset] != fileLines->line[0][0]) {
            offset++;
        }
        fileLines->line[i][offset] = '\0';

        wordsList[(i-1)*2 + 1] = fileLines->line[i] + offset + 1;
    }
    /*
    for (size_t i = 0; i < fileLines->numberOfLines * 2; i++) {
        printf("wordsList[%ld]=%s\n", i , wordsList[i]);
    }
     */

    for (size_t i = 0; i < fileLines->numberOfLines - 1; i++) {
        //printf ("IS LOADING (%s,%s) pair.\n",
        //        wordsList[i*2], wordsList[i*2+1]);
        if (!AddPair (newHashTable, wordsList[i*2], wordsList[i*2+1])) {
            printf ("Failed to upload (%s,%s) pair.\n", wordsList[i*2], wordsList[i*2+1]);
        }
    }

    return newHashTable;
}

bool ConsoleBumpOfHashTable (struct HashTable* hashTable) {

    if (hashTable == NULL) {
        return false;
    }

    printf ("ConsoleBumpOfHashTable(%ld) : BUMP OF HASH TABLE\n", hashTable);
    printf ("Length=%ld Function=%ld\n", hashTable->tableLength, hashTable->func);

    for (size_t i = 0; i < hashTable->tableLength; i++) {
        printf ("[%ld]", i);
        ConsoleBumpOfLinkedList (hashTable->buckets[i]);
        printf (" |\n");
    }

    return true;
}

char* PhoneticTranslation (char* engWord) {

    if (engWord == NULL) {
        return NULL;
    }

    char* phoneticDictionary[] = {
            "а",  //a
            "б",  //b
            "ц",  //c
            "д",  //d
            "е",  //e
            "ф",  //f
            "дж", //g
            "х",  //h
            "и",  //i
            "дще",//j
            "к",  //k
            "л",  //l
            "м",  //m
            "н",  //n
            "о",  //o
            "п",  //p
            "ку", //q
            "р",  //r
            "с",  //s
            "т",  //t
            "уу", //u
            "ви", //v
            "вэ", //w
            "кс", //x
            "уо", //y
            "з",  //z
    };

    size_t lengthOfWord = strlen(engWord);

    char* result = (char*) calloc (lengthOfWord * 3, sizeof(char));
    size_t lengthOfResult = 0;

    for (size_t i = 0; i < lengthOfWord; i++){
        if (engWord[i] <= 'z' && engWord[i] >= 'a') {
            strcat(result, phoneticDictionary[(engWord[i] - 'a')]);
            lengthOfResult += strlen (phoneticDictionary[(engWord[i] - 'a')]);
        } else {
            result[lengthOfResult] = engWord[i];
            lengthOfResult++;
        }
    }

    return result;
}

bool TranslateWebPage (char* filename, char* fileoutput) {

    if (filename == NULL || fileoutput == NULL) {
        return false;
    }

    struct HashTable* hashTable = BuildHashTable ("C:\\Cprojects\\dictionary\\dic.txt", 199, GetDJB2Hash);

    if (hashTable == NULL) {
        return false;
    }

    char* pageText = ReadTextFromFile (filename);

    if (pageText == NULL) {
        return false;
    }

    FILE* output = fopen (fileoutput, "w");

    if (output == NULL) {
        return false;
    }

    size_t offset = 0;
    bool inBrackets = false;
    while (pageText[offset] != '\0') {

        if (pageText[offset] == '<') {
            inBrackets = true;
        }

        if (pageText[offset] == '>') {
            pageText[offset] = '\0';
            fprintf (output, "%s>", pageText);
            printf ("fprintf printed (%s)\n", pageText);
            pageText += offset + 1; //*pageText += offset
            offset = 0;
            inBrackets = false;
        }

        if (pageText[offset] == ' ' && (inBrackets == false)) {
            pageText[offset] = '\0';
            fprintf (output, " %s ", FindByKey (hashTable, pageText));
            printf ("fprintf printed (%s)\n", pageText);
            pageText += offset + 1; //*pageText += offset
            offset = 0;
        }

        offset++;
    }

    fclose (output);

    return true;
}