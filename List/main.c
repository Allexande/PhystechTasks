//Version 1.1
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main()
{

    List* MyList = ListConstruct(6);

    ListInsertBegin (MyList, 6);
    ListInsertBegin (MyList, 12);
    ListInsertBegin (MyList, 35);
    ListInsertBegin (MyList, 9);

    ListEraseFromBegin (MyList);
    ListEraseFromEnd (MyList);

    ListInsertBegin (MyList, 55);
    ListInsertEnd (MyList, 78);

    printf ("At 2 index is %d\n", ListGetByIndex (MyList, 2));
    printf ("At 2 order is %d\n", ListGetByOrder (MyList, 2));
    printf ("List contains 35 = %d\n", ListContains (MyList, 35));
    printf ("List contains 45 = %d\n", ListContains (MyList, 45));

    ConsoleData (MyList);
    ConsoleDump (MyList);

	HTMLList (MyList);

	//ListDestroy(MyList);

    return 0;
}
