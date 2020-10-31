#include "filemaster.h"

size_t getNumberOfBytesOfFile (const char *fileName) {

    assert (fileName);

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

char* readTextFromFile (const char *fileName) {

    assert (fileName);

    size_t length = getNumberOfBytesOfFile (fileName);

    if (length < 1) {
        return NULL;
    }

    char* text = (char *) calloc (length + 2, sizeof(char));

    FILE *file = fopen (fileName, "r");

    if (file == NULL) {
        return NULL;

    } else {
        int lengthWasRead = fread ((text), sizeof(char), length, file);
        fclose (file);
        *(text+lengthWasRead) = '\0';
        return text;
    }
};

void clearStr (char* str) {
    for (int i = 0; i < MAXIMUM_LENGTH_OF_WORD; i++) {
        str[i] = 0;
    }
}

progText* readCommandsFromText (char* text) {
    size_t linesWasRead = 0;
    unsigned int offsetFromBegining = 0;
    char str[MAXIMUM_LENGTH_OF_WORD]; clearStr (str);
    size_t wasReadInStr = 0;
    bool commandIsRead = true;

    progText* prog = (progText*) calloc (sizeof(progText), 1);
    prog->lines = (line*) calloc (sizeof(line), getNumberOfSymbol (text, '\n'));

    while (true) {
        if (text[offsetFromBegining] == '\0') {
            if (commandIsRead) {
                memcpy (prog->lines[linesWasRead].command, str, MAXIMUM_LENGTH_OF_WORD);
            } else {
                memcpy (prog->lines[linesWasRead].arg, str, MAXIMUM_LENGTH_OF_WORD);
            }
            linesWasRead++;
            break;
        }
        if (text[offsetFromBegining] == ' ' && commandIsRead) {
            commandIsRead = false;
            memcpy (prog->lines[linesWasRead].command, str, MAXIMUM_LENGTH_OF_WORD);
            wasReadInStr = 0;
            clearStr (str);
        } else {
            if (text[offsetFromBegining] == '\n') {
                if (commandIsRead) {
                    memcpy (prog->lines[linesWasRead].command, str, MAXIMUM_LENGTH_OF_WORD);
                } else {
                    memcpy (prog->lines[linesWasRead].arg, str, MAXIMUM_LENGTH_OF_WORD);
                }
                commandIsRead = true;
                wasReadInStr = 0;
                clearStr (str);
                linesWasRead++;
            } else {
                str[wasReadInStr] = text[offsetFromBegining];
                wasReadInStr++;
            }
        }
        offsetFromBegining++;
        //printf("y\n");
    }

    prog->numberOfLines = linesWasRead;
    return prog;
};

bool writeCodeToFile (const char *fileName, double* code) {

    assert (fileName);

    FILE *file = fopen (fileName, "w");

    if (file == NULL) {
        return false;

    } else {
        fwrite (code, sizeof(code), 1, file);
        fclose (file);
    }

    return true;

};

bool writeProgramInFile (const char *fileName, double* progText, int progLength, char* header) {

    assert (fileName);

    FILE *file = fopen (fileName, "wb");

    if (file == NULL) {
        return false;

    } else {
        // 3 - длина header (константа)
        fwrite(header, 3, sizeof(char), file);
        // если проблемы, поменять sizeof(char) на sizeof(double)
        fwrite(progText, progLength, sizeof(char), file);

        fclose(file);
    }

    return true;
};


bool writeTextInFile (const char *fileName, char* text) {

    assert (fileName);

    FILE *file = fopen (fileName, "w");

    if (file == NULL) {
        return false;

    } else {
        fputs(text, file);
        fclose(file);
    }

    return true;
};

size_t getNumberOfSymbol (const char *text, char symbol) {

    assert (text);

    size_t symbols = 0;
    int point = 1;

    while (*(text + point) != '\0') {
        if (*(text + point) == symbol) symbols++;
        point++;
    }

    return symbols;
};

progText* getCommandsFromText (const char *fileName) {
    char* text = readTextFromFile (fileName);
    return readCommandsFromText (text);
};
