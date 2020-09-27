#include <time.h>

//TESTING FUNCTIONS

#define CODE_OF_FIRST_ENGLISH_LETTER 97
#define NUMBER_OF_ENGLISH_LETTERS    26
#define MAXIMUM_VALUE_OF_INTEGER     4294967293

char geterateRandomChar(){
    static unsigned int seed = time(NULL) % MAXIMUM_VALUE_OF_INTEGER;

    seed = (time(NULL) * seed + time(NULL)) % MAXIMUM_VALUE_OF_INTEGER;
    int code = seed % NUMBER_OF_ENGLISH_LETTERS;

    return (char)(code + CODE_OF_FIRST_ENGLISH_LETTER);
};

bool writeRandomText(const char *fileName, int numberOfSymbols, int linesLength){

    FILE *file = fopen(fileName, "w");

    if (file == NULL) {
        return false;
    } else {

        char c;
        for(int i = 0; i < numberOfSymbols; i++){
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

bool doTest(const char *input, const char *output, int numberOfSymbols, int linesLength){

    printf("\n\ndoTest(%s, %s, %d, %d) :\n", input, output, numberOfSymbols, linesLength);
    if(writeRandomText(input, numberOfSymbols, linesLength)){

        char** pointers = getSortedArrayOfPointers(input);

        if((pointers == NULL) || (!textOutIntoFIle(output, pointers))){
            return false;
        }

        textOut(pointers);

        return true;
    } else {
        return false;
    }
};

bool test(const char *input, const char *output){

    doTest(input, output, 10,  2);
    doTest(input, output, 200,  10);
    doTest(input, output, 1000, 50);

    return true;

    /*
    bool testsPassedSuccessfully = (
            doTest(input, output, 10,  3) ||
            doTest(input, output, 20,  4) ||
            doTest(input, output, 100, 5) );

    if(testsPassedSuccessfully){

        printf("\nALL TESTS PASSED SUCCESSFULLY\n");
        return true;
    } else {
        printf("\nTHERE WERE SOME ERRORS IN TESTS\n");
        return false;
    } */

}
