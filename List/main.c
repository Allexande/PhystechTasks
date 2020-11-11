//Version 1.4
#include <stdio.h>
#include <stdlib.h>

#include "list.c"

int main() {

    List* MyList = ListConstruct (6);

    // ------------------------------------------------
    //WHEN WE INSERT TO LOGICAL ADRESS
    //O(N)

    /*
    ListInsertAtIndex (MyList, 6,  1);
    ListInsertAtIndex (MyList, 14, 2);
    ListInsertAtIndex (MyList, 35, 3);
    */

    // ------------------------------------------------
    //WHEN WE INSERT TO PHYSICAL ADRESS
    //O(1)

    /*
    ListInsertAtPlace (MyList, 9, 1);
    */

    // ------------------------------------------------
    //WHEN WE INSERT TO LOGICAL ADRESS EFFECTIVLY (!!!!!)
    //~ O(1)

    index_t LastIndex = ListInsertEnd (MyList, 45);
    ListInsertEnd (MyList, 20);
    ListInsertAtPlace (MyList, 14, LastIndex);
    ListInsertAtPlace (MyList, 35, LastIndex);
    ListInsertAtPlace (MyList, 60, LastIndex);

    // ------------------------------------------------

    ListEraseFromBegin (MyList);

    ListInsertBegin (MyList, 55);
    ListInsertEnd   (MyList, 78);

    printf ("At 2 index is %d\n", ListGetByIndex (MyList, 2));
    printf ("At 2 order is %d\n", ListGetByOrder (MyList, 2));

    printf ("List contains 35 = %d\n", ListContains (MyList, 35));
    printf ("List contains 45 = %d\n", ListContains (MyList, 45));

    ConsoleData (MyList);
    ConsoleDump (MyList);

	HTMLList (MyList);

	ListDestroy (MyList);

    return 0;
}
