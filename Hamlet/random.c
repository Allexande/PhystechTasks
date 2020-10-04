#include <time.h>

#define CODE_OF_FIRST_ENGLISH_LETTER   97
#define NUMBER_OF_ENGLISH_LETTERS      26
#define MAXIMUM_VALUE_OF_UNSIGNED_LONG 0xffffffff

unsigned long int getCurrentTime() {
    return (unsigned long int) time(NULL);
}

//Function for generating random chars which I have written myself
/*static unsigned long int seed = getCurrentTime() % MAXIMUM_VALUE_OF_UNSIGNED_LONG;
char geterateRandomChar(){

    unsigned long int time = getCurrentTime();
    seed = (time * seed + 12345) % MAXIMUM_VALUE_OF_UNSIGNED_LONG;
    int code = seed % NUMBER_OF_ENGLISH_LETTERS;

    return (char)(code + CODE_OF_FIRST_ENGLISH_LETTER);
};*/

//Function for generating random chars which uses tools made by K&R
char geterateRandomChar() {
    return (char)(rand() % NUMBER_OF_ENGLISH_LETTERS + CODE_OF_FIRST_ENGLISH_LETTER);
}

int geterateRandomInt(int minimum, int maximum) {
    return (int)(rand() % (maximum - minimum) + minimum);
}

void setRandSeed() {
    unsigned int time_ = (unsigned int)time(NULL);
    srand(time_);
}
