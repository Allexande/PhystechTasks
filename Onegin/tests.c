#include <time.h>

//TESTING FUNCTIONS

#define TESTING_FILE_NAME "tests.txt"

char geterateRandomChar(){
    static unsigned int seed = time(NULL);
    seed = (time(NULL) * seed + time(NULL));
    int code = seed % 26;
    return (char)(code + 97);
};

bool writeRandomText(const char *fileName, int numberOfSymbols, int possabilityOfSpace){
    FILE *file;

    if ((file = fopen(fileName, "w")) == NULL) {
        return false;
    } else {
        char c;
        for(int i = 0; i < numberOfSymbols; i++){
            if(i % possabilityOfSpace == 0){
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

bool doTest(const char *fileName, int numberOfSymbols, int possabilityOfSpace){
    printf("\n\ndoTest(%s, %d, %d) :\n", fileName, numberOfSymbols, possabilityOfSpace);
    if(writeRandomText(fileName, numberOfSymbols, possabilityOfSpace)){

        char** pointers = getSortedArrayOfPointers(fileName);

        if(pointers == NULL){
            return false;
        }

        textOut(pointers);

        return true;
    } else {
        return false;
    }
};

void test(){
    printf("TESTS\n");

    doTest(TESTING_FILE_NAME, 100, 10);
    doTest(TESTING_FILE_NAME, 100, 5);

    printf("\nEND OF TESTS\n");
};
