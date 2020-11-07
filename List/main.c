//Version 1.0
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main()
{

    List* MyList = ListConstruct(10);

    ListInsertBegin(MyList, 6);
    ListInsertBegin(MyList, 12);
    ListInsertBegin(MyList, 8);
    ListInsertBegin(MyList, 9);
    ListInsertBegin(MyList, 9);
    ListInsertBegin(MyList, 34);

    ListEraseFromBegin(MyList);
    ListEraseFromEnd(MyList);

    ListInsertBegin(MyList, 55);
    ListInsertEnd(MyList, 78);

    ConsoleData(MyList);
    ConsoleDump(MyList);

	HTMLList(MyList);

	ListDestroy(MyList);

    return 0;
}
