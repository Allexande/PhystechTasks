//Version 0.5

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

//TODO обработка аргументов

//TODO проверка валидности файла перед считыванием
int main()
{
    #ifndef TESTING
        //Functions to call in working mode
        StartGame (DEFAULT_READING_BASE, DEFAULT_WRITING_BASE);
    #else
        //Functions to call in testing mode
        Tets ();
    #endif

    return 0;
}
