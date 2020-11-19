//Version 0.1

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#define TESTING

#include "akinator.c"

#include "tests.c"

int main()
{
    #ifndef TESTING
        //Functions to call in working mode

    #else
        //Functions to call in testing mode
        Tets ();
    #endif

    return 0;
}
