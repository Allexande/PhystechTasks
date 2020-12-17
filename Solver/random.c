//Version 0.8

#include <time.h>

unsigned long int GetCurrentTime () {
    return (unsigned long int) time(NULL);
}

int GeterateRandomInt (int minimum, int maximum) {
    return (int)(rand () % (maximum - minimum) + minimum);
}

void SetRandSeed () {
    srand ((unsigned int) time (NULL));
}
