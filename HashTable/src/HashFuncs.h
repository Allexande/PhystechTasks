//
// Created by AlexanderT on 10.04.2021.
//

#ifndef ENGRUSTRANS_HASHFUNCS_H
#define ENGRUSTRANS_HASHFUNCS_H

//SHOULD BE DELETEN WITH PRINTFS "DELETE ME"
#include <stdio.h>

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

//List of hash functions which have to be tasted
//Any of them could be used in hash table

#define BITS_IN_BYTE 8
#define NUMBER_OF_HASH_FUNCTIONS 11

//Type of variable hash functions return
typedef unsigned long long hash_t;
//Type of array hash functions handle
typedef char         input_t;

//Returns constant _CONSTANT_HASH
#define _CONSTANT_HASH 0
hash_t GetConstantHash (input_t* data);

//Returns length of array
hash_t GetLengthHash (input_t* data);

//Returns value of first element in array
hash_t GetFirstLetterHash (input_t* data);

//Returns sum value of all elements in array
hash_t GetSumHash (input_t* data);

//Returns hash generated with bit rotation of elements of array
//and xor operation
hash_t GetBitRotateHash (input_t* data);

//Returns sum value of all elements in array multiplied on their positions
hash_t GetSumWithPlaceHash (input_t* data);

//NEXT LINKS WERE VALID 10.04.2021

//Jenkins hash function - https://en.wikipedia.org/wiki/Jenkins_hash_function
hash_t GetJenkinsHash (input_t* data);

//djb2 - http://www.cse.yorku.ca/~oz/hash.html
hash_t GetDJB2Hash (input_t* data);

hash_t FastGetDJB2Hash (input_t* data);

//sbdm - http://www.cse.yorku.ca/~oz/hash.html
hash_t GetSBDMHash (input_t* data);

//Just some random operations to make hash
hash_t GetRandomHash (input_t* data);

//My own hash function
hash_t GetTuzmanHash (input_t* data);

#endif //ENGRUSTRANS_HASHFUNCS_H
