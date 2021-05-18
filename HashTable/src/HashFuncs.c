//
// Created by AlexanderT on 10.04.2021.
//

#include "HashFuncs.h"

#define END_OF_DATA 0

hash_t GetConstantHash (input_t* data) {

    assert (data);

    return _CONSTANT_HASH;
}

hash_t GetLengthHash (input_t* data) {

    assert (data);

    hash_t pointer = 0;
    while (data[pointer] != END_OF_DATA) {
        pointer++;
    }

    return pointer;
}

hash_t GetFirstLetterHash (input_t* data) {

    assert (data);

    return (hash_t) data[0];
}

hash_t GetSumHash (input_t* data) {

    assert (data);

    size_t pointer = 0;
    hash_t sum     = 0;
    while (data[pointer] != END_OF_DATA) {
        sum += data[pointer];
        pointer++;
    }

    return sum;
}

hash_t GetBitRotateHash (input_t* data) {

    assert (data);

    size_t pointer = 0;
    hash_t hash    = 0;
    bool   leftBit = false;
    while (data[pointer] != END_OF_DATA) {

        hash = (hash>>1)|(hash<<31);

        hash ^= data[pointer];
        pointer++;
    }

    return hash;
}

hash_t GetSumWithPlaceHash (input_t* data) {

    assert (data);

    size_t pointer = 0;
    hash_t sum     = 0;
    while (data[pointer] != END_OF_DATA) {
        sum += data[pointer] * (pointer + 1);
        pointer++;
    }

    return sum;
}

hash_t GetJenkinsHash (input_t* data) {

    assert (data);

    hash_t hash    = 0;
    size_t pointer = 0;
    while (data[pointer] != END_OF_DATA) {
        hash += data[pointer];
        hash += (hash << 10);
        hash ^= (hash >> 6);
        pointer++;
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

hash_t GetDJB2Hash (input_t* data) {

    assert (data);

    hash_t hash    = 5381;
    size_t pointer = 0;
    while (data[pointer] != END_OF_DATA) {
        hash = ((hash << 5) + hash) + data[pointer];
        pointer++;
    }

    return hash;
}

hash_t FastGetDJB2Hash (input_t* data) {

    assert (data);

    hash_t hash;

    asm(".intel_syntax noprefix \n"
        "mov rax, 5381          \n"  //Hash
        "mov rbx, %1            \n"  //Pointer
        "HANDLING_LOOP:         \n"
        "cmp byte ptr [rbx], 1  \n"
        "je END_OF_HANDLING     \n"
        "shl rax, 6             \n"
        "add rax, [rbx]         \n"
        "inc rbx                \n"
        "jmp HANDLING_LOOP      \n"
        "END_OF_HANDLING:       \n"
        "mov %0, rax            \n"
        ".att_syntax            \n"
        :"=r"(hash)             // список выходных параметров.
        :"r"(data)              // список входных параметров.
        :"rax", "rbx"           // список разрушаемых регистров.
    );

    return hash;
}

hash_t GetSBDMHash (input_t* data) {

    assert (data);

    hash_t hash    = 0;
    size_t pointer = 0;
    while (data[pointer] != END_OF_DATA) {
        hash = data[pointer] + (hash << 6) + (hash << 16) - hash;
        pointer++;
    }

    return hash;
}

hash_t GetRandomHash (input_t* data) {

    assert (data);

    hash_t  hash    = 0;
    size_t  pointer = 0;
    input_t nextElem;
    while (data[pointer] != END_OF_DATA) {
        nextElem = data[pointer];
        hash += nextElem;
        nextElem << (hash % (sizeof(input_t) * 4));
        hash += nextElem + (hash << (pointer % (sizeof(input_t) * 2)));
        pointer++;
    }

    return hash;
}

//For english strings only!
hash_t GetTuzmanHash (input_t* data) {

    assert (data);

    hash_t hash    = 0;
    size_t pointer = 0;
    size_t factor  = 1;
    while (data[pointer] != END_OF_DATA) {
        hash += (data[pointer] - 'a') * factor;
        factor *= 'z' - 'a';
        pointer++;
    }

    return hash;
}
