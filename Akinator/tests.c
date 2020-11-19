//Version 0.1

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

void Tets () {

    //OK
    //TestGetLinesFromText ();

    //OK
    //TestCutBothSides ();

}
