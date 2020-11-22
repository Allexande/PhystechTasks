//Version 1.0

void TestGetLinesFromText () {

    char text[] = {"Hey\n{\n}\nueu\nsdfd\n\ndfdfw444\n"};
    Lines* linesOfText = GetLinesFromText (text);

    printf("linesOfText->numberOfLines=%d\n", linesOfText->numberOfLines);
    for (size_t i = 0; i < linesOfText->numberOfLines; i++) {
        printf("linesOfText->line[%d]=%s\n", i, linesOfText->line[i]);
    }

}

void TestCutBothSides () {

    char str[] = {"_HELLO_"};
    printf("CutBothSides(%s)=%s\n", str, CutBothSides(str));

}

void TestMakingTreeAndDump () {

    Tree* myTree = GetTreeFromFile ("base.txt");

    ConsoleTreeDump (myTree);
    GraphTree (myTree);

    printf("Test ended.");
}

void TestWritingTreeInFile () {

    Tree* myTree = GetTreeFromFile ("base.txt");
    PutTreeToFile ("newBase.txt", myTree);
    printf("FilesContainSameText(base.txt, newBase.txt)=%d\n", FilesContainSameText("newBase.txt", "base.txt"));

}

void Tets () {

    //EVERYTHING IS OK

    //OK
    //TestGetLinesFromText ();

    //OK
    //TestCutBothSides ();

    //OK
    //TestMakingTreeAndDump ();

    //OK
    //TestWritingTreeInFile ();
}
