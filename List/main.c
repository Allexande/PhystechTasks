//Version 1.5.3

#include <stdio.h>
#include <stdlib.h>

//#define TESTING

#include "list.c"
#include "test.c"

int main() {

    //TODO
    //ÑÎĞÒÈĞÎÂÊÀ È Ó×ÈÒÛÂÀÍÈÅ ÅÅ ÏĞÈ ÂÇßÒÈÈ İËÅÌÅÍÒÀ

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
