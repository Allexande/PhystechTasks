//version 1.0.0

#include "string.h"

FunctionalString* createFunctionalString (size_t capacity) {

    FunctionalString* fstring = (FunctionalString*) calloc (sizeof(FunctionalString), 1);
    fstring->str = (char*) calloc (sizeof(char), capacity);
    fstring->length = 0;

    return fstring;
};

FunctionalString* convertToFunctionalString (char* str) {

    FunctionalString* fstring = (FunctionalString*) calloc (sizeof(FunctionalString), 1);

    unsigned int pointer = 0;
    do {
        pointer++;
    } while (str[pointer] != '\0');

    fstring->str = (char*) calloc (sizeof(char), pointer);

    pointer = 0;
    do {
        fstring->str[pointer] = str[pointer];
        pointer++;
    } while (str[pointer] != '\0');

    fstring->length = pointer;

    return fstring;
};

bool compareFunctionalStrings (FunctionalString* first, FunctionalString* second) {

    if (first->length != second->length) {
        return false;

    }

    for (int i = 0; i < first->length; i++) {

        if (first->str[i] != second->str[i]) {
            return false;

        }
    }

    return true;
};

FunctionalString* cutFunctionalString (FunctionalString* str, size_t left, size_t right) {

    if ((left >= right) || (left < 0) || (right > str->length)) {
        return NULL;

    }

    FunctionalString* newStr = createFunctionalString (right - left + 1);

    for (int i = 0; i <= right - left; i++) {
        newStr->str[i] = str->str[left + i];
    }

    newStr->length = right - left + 1;

    return newStr;
};

FunctionalString* mergeFunctionalStrings (FunctionalString* first, FunctionalString* second) {

    FunctionalString* newStr = createFunctionalString (first->length + second->length);

    for (int i = 0; i < first->length; i++) {
        newStr->str[i] = first->str[i];
    }

     for (int i = 0; i < second->length; i++) {
        newStr->str[i + first->length] = second->str[i];
    }

    newStr->length = first->length + second->length;

    return newStr;
};
