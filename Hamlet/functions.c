#include <string.h>

bool processMainArguments (int argc, char* argv[], char** input, char** output) {

    if (argc > 1) {

        for (int i = 1; i < argc; i++) {
            if (strcmp (argv[i], "-i") == 0 || strcmp (argv[i], "--input")  == 0) {
                *input = argv[i];
            }

            if (strcmp (argv[i], "-o") == 0 || strcmp (argv[i], "--output") == 0) {
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

bool getText (const char *fileName, char* text) {

    assert(fileName);

    FILE *file = fopen (fileName, "r");

    if (file == NULL) {
        return false;

    } else {
        char buffer[READING_BUFFER_SIZE] = {};
        int buffersReaded = 0;
        int readed = 0;

        while ((readed = fread (buffer, sizeof(char), READING_BUFFER_SIZE, file)) == READING_BUFFER_SIZE) {
            for (int i = 0; i < READING_BUFFER_SIZE; i++) {
                *(text + (buffersReaded * READING_BUFFER_SIZE) + i) = buffer[i];
            }
            buffersReaded++;
        }

        for (int i = 0; i < readed; i++) {
            *(text+(buffersReaded*READING_BUFFER_SIZE)+i) = buffer[i];
        }

        fclose (file);

        return true;
    }
};

/*
int getNumberOfBytes (const char *fileName) {

    FILE *file = fopen (fileName, "r");

    if (file == NULL) {
        return NULL;
    } else {
        long int save_pos, size_of_file;

        save_pos = ftell(file);
        fseek(file, 0L, SEEK_END);
        size_of_file = ftell(file);
        fseek(file, save_pos, SEEK_SET);

        return (int)(size_of_file - 1) ;
    }
};*/

int getNumberOfBytes (const char *fileName) {

    assert(fileName);

    FILE *file = fopen (fileName, "r");

    if (file == NULL) {
        return -1;
    } else {

        int number = 0;
        while (fgetc(file) != EOF) {
            number++;
        }

        fclose (file);
        return number;
    }
};

int getNumberOfLines (const char *text, int length) {

    int lines = 1;
    for (int i = 0; i < length; i++) {
        if (text[i] == '\n') lines++;
    }

    return lines;
};

/*void quickSort (char** pointers, int first, int last) {
    printf ("first=%d last=%d", first, last);
    if (first < last) {

        int left = first, right = last;
        char* middle = pointers[(left + right) / 2];
        do {

            while (comparator(pointers[left], middle)) {
                left++;
            }
            while (!comparator(pointers[right], middle)) {

                right--;
            }

            if (left <= right)
            {

                char* tmp = pointers[left];
                pointers[left] = pointers[right];
                pointers[right] = tmp;
                left++;
                right--;
            }

        } while (left <= right);

        quickSort (pointers, first, right);
        quickSort (pointers, left, last);
    }
} */

char** getSortedArrayOfPointers (const char *fileName) {

    assert(fileName);

    int length = getNumberOfBytes (fileName);

    char* text = (char *) calloc (length, sizeof(char));

    if(!getText(fileName, text)) {
        return NULL;
    }

    if (length < 1) {
        return NULL;
    }

    int numberOfLines = getNumberOfLines(text, length);
    char** pointers = (char **) calloc (numberOfLines, sizeof(char*));
    int pointer = 1;
    pointers[0] = &text[0];

    for(int i = 1; i < length-1; i++) {
        if(text[i] == '\n') {
            pointers[pointer] = (&text[i]+1);
            pointer++;
        }
    }

    //quickSort(pointers, numberOfLines - 1);

    for (int i = 1; i < numberOfLines; i++) {

        for (int j = 0; j < numberOfLines - i - 1; j++) {
            if (comparator((pointers[j]), (pointers[j+1]))) {

                char* buf     = pointers[j];
                pointers[j]   = pointers[j+1];
                pointers[j+1] = buf;

            }
        }
    }

    pointers[numberOfLines] = NULL;

    return pointers;

};

bool comparator (char* adress1, char* adress2) {

    char char1 = getChar(adress1);
    char char2 = getChar(adress2);

    while (((int)char1 != (int)'\n') && ((int)char2 != (int)'\n')) {
        if ((char1 != NULL) && (char2 != NULL)) {
            if ((int)char1 != (int)char2) {
                return ((int)char1 > (int)char2);
            }
        }

        if ((char1 != NULL) && ((int)char1 == (int)char2)) {
            adress1++;
            adress2++;
        }

        if (char1 == NULL) adress1++;
        if (char2 == NULL) adress2++;

        char1 = getChar(adress1);
        char2 = getChar(adress2);
    }
    return false;
};

char getChar (char* adress) {

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

    FILE *file = fopen (fileName, "w");

    if (file == NULL) {
        return false;
    } else {

        int point  = 0;
        int symbol = 0;

        while((pointers[point] + symbol) != NULL) {
            char sum = *(pointers[point]+symbol);
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
