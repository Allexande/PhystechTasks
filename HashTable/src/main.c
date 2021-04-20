#include <stdio.h>

#include "HashFuncs.h"
#include "HashTest.h"

#define ENG_WORDS_LIST_FILE "C://Cprojects//dictionary//WordsList.txt"

int main() {
    printf ("DELETE ME: Program began\n");
    return CreateReport (ENG_WORDS_LIST_FILE);
}