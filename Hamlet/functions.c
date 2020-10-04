#include <string.h>

bool processMainArguments (int argc, char* argv[], char** input, char** output) {

    assert (input );
    assert (output);

    if (argc > 1) {

        for (int i = 1; i < argc; i++) {
            if (strcmp (argv[i], "-i") == 0 || strcmp (argv[i], "--input")  == 0) {
                *input = argv[i];
            }

            if (strcmp (argv[i], "-o") == 0 || strcmp (argv[i], "--output") == 0) {
                *output = argv[i];
            }

            if (strcmp (argv[i], "-p") == 0 || strcmp (argv[i], "--poem") == 0) {
                *output = argv[i];
            }

            if (strcmp (argv[i], "-t") == 0 || strcmp (argv[i], "--test")   == 0) {
                *input  = DEFAULT_TESTING_READING_FILE_NAME;
                *output = DEFAULT_TESTING_WRITING_FILE_NAME;
                test (*input, *output);
                return true;
            }
        }
    }

    return false;

}

char* getText (const char *fileName) {

    assert (fileName);

    size_t length = getNumberOfBytes (fileName);

    if (length < 1) {
        return NULL;
    }

    char* text = (char *) calloc (length + 2, sizeof(char));

    FILE *file = fopen (fileName, "r");

    if (file == NULL) {
        return NULL;

    } else {

        *(text) = '\0';

        int lengthWasRead = fread ((text + 1), sizeof(char), length, file);
        fclose (file);

        *(text+lengthWasRead) = '\0';

        return text;
    }
};

char** getPointers (char* text) {

    assert (text);

    int numberOfLines = getNumberOfSymbol (text, '\n');

    char** pointers = (char **) calloc (numberOfLines+2, sizeof(char*));

    int pointer = 1;
    pointers[0] = (text + 1);
    int pos = 2;

    while ( *(text + pos) != '\0') {

        if (text[pos] == '\n') {
            pointers[pointer] = (text + pos + 1);
            pointer++;
        }

        pos++;
    }

    pointers[numberOfLines + 1] = NULL;

    return pointers;
}

void sortPointers (char** pointers) {

    assert (pointers);

    int numberOfLines = getNumberOfSymbol (*pointers, '\n');

    for (int i = 1; i < numberOfLines; i++) {

        for (int j = 0; j < numberOfLines - i - 1; j++) {
            if (comparator((pointers[j]), (pointers[j+1]), 1)) {

                char* buf     = pointers[j];
                pointers[j]   = pointers[j+1];
                pointers[j+1] = buf;

            }
        }
    }
}

void sortPointersViseVersa (char** pointers) {

    assert (pointers);

    int numberOfLines = getNumberOfSymbol (*pointers, '\n');

    for (int i = 1; i < numberOfLines; i++) {
        *(pointers[i] - 1) = '\0';
    }

    for (int i = 0; i < numberOfLines - 1; i++) {
        strrev(pointers[i]);
    }

    sortPointers(pointers);

     for (int i = 0; i < numberOfLines - 1; i++) {
        strrev(pointers[i]);
    }

    for (int i = 1; i < numberOfLines; i++) {
        *(pointers[i] - 1) = '\n';
    }
}

char** getPointersOfPoem (char** pointers, unsigned int rhymedPairs) {

    assert (pointers);

    int numberOfLines = getNumberOfSymbol (*pointers, '\n');

    char** poem = (char **) calloc (2 * 256 * rhymedPairs, sizeof(char*));

    setRandSeed();

    for (int i = 0; i < rhymedPairs; i++) {
        int rand = geterateRandomInt(0, numberOfLines - 2);
        poem[i] = pointers[rand];
        poem[++i] = pointers[++rand];
    }

    return poem;
}

size_t getNumberOfBytes (const char *fileName) {

    assert(fileName);

    FILE *file = fopen (fileName, "r");

    if (file == NULL) {
        return 0;

    } else {
        fseek(file, 0, SEEK_END);
        size_t pos = ftell(file);
        fseek(file, 0, SEEK_SET);
        fclose (file);
        return pos;
    }
};

int getNumberOfSymbol (const char *text, char symbol) {

    assert (text);

    int symbols = 0;
    int point = 1;

    while (*(text + point) != '\0') {
        if (*(text + point) == symbol) symbols++;
        point++;
    }

    return symbols;
};

char** getSortedArrayOfPointers (const char *fileName) {

    assert (fileName);

    char*   text = getText (fileName);
    assert (text);

    char**  pointers = getPointers (text);
    assert (pointers);

    //sortPointersViseVersa (pointers);
    sortPointers (pointers);

    //pointers = getPointersOfPoem (pointers, 20);

    return pointers;

};

bool comparator (char* adress1, char* adress2, int direction) {

    assert (adress1);
    assert (adress2);

    char char1 = getChar(adress1);
    char char2 = getChar(adress2);

    while (((int)char1 != (int)'\n') && ((int)char2 != (int)'\n')) {

        if ((char1 != NULL) && (char2 != NULL)) {
            if ((int)char1 != (int)char2) {
                return ((int)char1 > (int)char2);

            }

        }

        if ((char1 != NULL) && ((int)char1 == (int)char2)) {
            adress1 += direction;
            adress2 += direction;
        }

        if (char1 == NULL) adress1 += direction;
        if (char2 == NULL) adress2 += direction;

        char1 = getChar(adress1);
        char2 = getChar(adress2);
    }
    return false;
};

char getChar (char* adress) {

    assert (adress);

    char charFromAdress = *(adress);

    if (((int)charFromAdress >= (int)'A') && ((int)charFromAdress <= (int)'Z')) {
        return (charFromAdress + 32);

    } else {
        if (((int)charFromAdress >= (int)'a') && ((int)charFromAdress <= (int)'z') || ((int)charFromAdress == (int)'\n')) {
            return charFromAdress;

        } else {
            return NULL;

        }
    }
};

bool textOutIntoFIle (const char *fileName, char** pointers) {

    assert(fileName);
    assert(pointers);

    FILE *file = fopen (fileName, "w");

    if (file == NULL) {
        return false;

    } else {

        int point  = 0;
        int symbol = 0;

        while((pointers[point] + symbol) != NULL) {
            char sum = *(pointers[point]+symbol);

            if (sum == '\0'){
                break;
            }

            if((int)sum == (int)'\n') {
                point++;
                symbol = 0;
                fputc ('\n', file);

            } else {
                fputc (sum, file);
                symbol++;

            }
        }

        fclose (file);

        return true;

    }
};

int doSort (const char *input, const char *output) {

    assert(input);
    assert(output);

    char** pointers = getSortedArrayOfPointers (input);
    if (pointers == NULL) {
        return 1; //Error during reading from file
    }

    if (!textOutIntoFIle(output, pointers)) {
        return 2; //Error during writing to file
    }

    //textOut(pointers);

    free (pointers);
    pointers = NULL;

    return 0; //No errors
};

void writePoem (const char *fileName, unsigned int rhymedPairs) {
    assert (fileName);

    char*   text = getText (fileName);
    assert (text);

    char**  pointers = getPointers (text);
    assert (pointers);

    sortPointersViseVersa (pointers);
    pointers = getPointersOfPoem (pointers, rhymedPairs);

    textOut (pointers);
}

void textOut (char** pointers) {

    int point  = 0;
    int symbol = 0;

    while((pointers[point] + symbol) != NULL) {
        char sum = *(pointers[point]+symbol);
        if((int)sum == (int)'\n'){
            point++;
            symbol = 0;
            printf ("\n");
        } else {
            if (sum == NULL) {
                break;
            }
            printf ("%c", sum);
            symbol++;
        }
    }

};
