//Version 1.6.0

void GeneralProcess (List* MyList) {

    assert(MyList);

    index_t LastIndex = ListInsertEnd (MyList, 45);
    ListInsertEnd (MyList, 20);
    ListInsertAtPlace (MyList, 14, LastIndex);
    ListInsertAtPlace (MyList, 35, LastIndex);
    ListInsertAtPlace (MyList, 60, LastIndex);

    ListEraseFromBegin (MyList);

    ListInsertBegin (MyList, 55);
    ListInsertEnd   (MyList, 78);

    ListGraphLogical(MyList);
    ListGraphPhysical(MyList);

}

bool GeneralTest () {

    List* MyList = ListConstruct (10);
    assert(MyList);

    GeneralProcess (MyList);

    elem_t rightSequence[] = {55, 60, 35, 14, 20, 78};

    index_t link = MyList->head;

    for (index_t point = 1; point <= MyList->length; point++) {

        if (rightSequence[point - 1] != MyList->data[link]) {

            ListDestroy (MyList);
            return false;

        }

        link = MyList->next[link];

    }

    ListDestroy (MyList);
    return true;
}

void GeneralShow () {

    List* MyList = ListConstruct (10);
    assert(MyList);

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

    GeneralProcess (MyList);

    // ------------------------------------------------

    printf ("At 2 index is %d\n", ListGetByIndex (MyList, 2));
    printf ("At 2 order is %d\n", ListGetByOrder (MyList, 2));

    printf ("List contains 35 = %d\n", ListContains (MyList, 35));
    printf ("List contains 45 = %d\n", ListContains (MyList, 45));

    ConsoleData (MyList);
    ConsoleDump (MyList);

	HTMLList (MyList);

	ListDestroy (MyList);

}

//For testing
int Test () {

    List* MyList = ListConstruct (10);

    ListInsertEnd (MyList, 11);
    ListInsertEnd (MyList, 22);
    ListInsertEnd (MyList, 33);
    ListInsertEnd (MyList, 44);
    ListInsertEnd (MyList, 55);
    ListInsertEnd (MyList, 66);
    ListInsertEnd (MyList, 77);

    ListEraseAtIndex (MyList, 3);
    ListInsertEnd (MyList, 99);

    ListEraseFromBegin(MyList);
    ListEraseFromEnd(MyList);

    ListEraseAtPlace(MyList, 4);

    ListEraseFromEnd(MyList);
    ListEraseFromEnd(MyList);

    ListInsertEnd (MyList, 44);
    ListInsertEnd (MyList, 55);
    ListInsertEnd (MyList, 66);

    ListMakeLinear (&MyList);

    HTMLList (MyList);
    ConsoleData (MyList);

}
