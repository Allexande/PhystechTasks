//version 0.2.0

#include <time.h>

#define CODE_OF_FIRST_ENGLISH_LETTER   97
#define NUMBER_OF_ENGLISH_LETTERS      26

unsigned long int getCurrentTime() {
    return time(NULL);
}

void setRandSeed() {
    srand(getCurrentTime());
}

int geterateRandomInt(int minimum, int maximum) {
    return (rand() % (maximum - minimum) + minimum);
}

char geterateRandomChar() {
    return (rand() % NUMBER_OF_ENGLISH_LETTERS + CODE_OF_FIRST_ENGLISH_LETTER);
}
