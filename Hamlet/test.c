
//TESTING FUNCTIONS

bool writeRandomText(const char *fileName, int numberOfSymbols, int linesLength) {

    FILE *file = fopen(fileName, "w");

    if (file == NULL) {
        return false;
    } else {

        char c;

        setRandSeed();

        for(int i = 0; i < numberOfSymbols; i++) {
            if(i % linesLength == 0){
                c = '\n';
            } else {
                c = geterateRandomChar();
            }

            fputc(c, file);
            printf("%c", c);
        }

        fclose(file);
        return true;
    }
}

bool doTest(const char *input, const char *output, int numberOfSymbols, int linesLength) {

    printf("\n\ndoTest(%s, %s, %d, %d) :\n", input, output, numberOfSymbols, linesLength);
    if(writeRandomText(input, numberOfSymbols, linesLength)) {

        char** pointers = getSortedArrayOfPointers(input);

        if((pointers == NULL) || (!textOutIntoFIle(output, pointers))) {
            return false;
        }

        textOut(pointers);

        free(pointers);
        pointers = NULL;

        return true;
    } else {
        return false;
    }
};

bool test(const char *input, const char *output) {

    doTest(input, output, 10,  2);
    doTest(input, output, 500,  10);
    doTest(input, output, 50, 50);

    return true;

}
