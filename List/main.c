//Version 1.6.0

#include <stdio.h>
#include <stdlib.h>

//#define TESTING

#include "list.c"
#include "test.c"

int main() {

    #ifndef TESTING

        //For demonstration
        GeneralShow ();
        //Test ();

    #else

        //For testing
        if (!GeneralTest ()) {
            printf("General test was failed!\n");
            return -1;

        } else {
            printf("General test was passed!\n");
        };

    #endif

    return 1;
}
