//Version 0.7

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#define DEFAULT_READING_BASE "base.txt"
#define DEFAULT_WRITING_BASE "base.txt"

//#define TESTING

#include "game.c"

#ifdef TESTING
    #include "tests.c"
#endif

//TODO
/*
if (firstWay[pointer]->parent->right == firstWay[pointer]) {
                printf (" it ");
            } else {
                printf (" it is false that it ");
            }

        printf ("%s,", firstWay[pointer]->parent->text);

*/
//Можно вынести в функцию в game.c

//TODO проверка валидности файла перед считыванием
int main (const int argc, const char* argv[]) {

    const char* inputFile  = DEFAULT_READING_BASE;
    const char* outputFile = DEFAULT_WRITING_BASE;

    if (argc > 1) {

        for (int i = 1; i < argc; i++) {

            if (strcmp(argv[i], "-i") == 0  || strcmp(argv[i], "--input")   == 0) {
                inputFile = argv[i];
            }

            if (strcmp(argv[i], "-o") == 0  || strcmp(argv[i], "--output")   == 0) {
                outputFile = argv[i];
            }

        }

    }

    #ifndef TESTING
        //Functions to call in working mode
        StartGame (inputFile, outputFile);
    #else
        //Functions to call in testing mode
        Tets ();
    #endif

    return 0;
}
