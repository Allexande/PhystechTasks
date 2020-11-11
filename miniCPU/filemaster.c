//version 0.2.0

#include "filemaster.h"

size_t getNumberOfBytesOfFile (const char *fileName) {

    assert (fileName);

    FILE *file = fopen (fileName, "r");

    assert(file);

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

    assert (text);

    FILE *file = fopen (fileName, "r");

    assert (file);

    if (file == NULL) {
        return NULL;

    }

    int lengthWasRead = fread (text, sizeof(char), length, file);

    assert (text);

    fclose (file);
    *(text+lengthWasRead) = '\0';
    return text;

};

char* readBinaryFromFile (const char *fileName) {

    assert (fileName);

    size_t length = getNumberOfBytesOfFile (fileName);

    if (length < 1) {
        return NULL;
    }

    char* binaryCode = (char *) calloc (sizeof(char), length);

    assert (binaryCode);

    FILE *file = fopen (fileName, "rb");

    assert (file);

    fread (binaryCode, sizeof(char), length, file);

    fclose (file);

    return binaryCode;
};

void clearStr (char* str) {

    for (int i = 0; i < MAXIMUM_LENGTH_OF_WORD; i++) {
        str[i] = 0;
    }

}

progText* readCommandsFromText (char* text) {

    assert (text);

    size_t linesWasRead = 0;
    unsigned int offsetFromBegining = 0;
    char str[MAXIMUM_LENGTH_OF_WORD]; clearStr (str);
    size_t wasReadInStr = 0;
    bool commandIsRead = true;

    progText* prog = (progText*) calloc (sizeof(progText), 1);
    assert(prog);

    prog->lines = (line*) calloc (sizeof(line), getNumberOfSymbol (text, '\n'));
    assert(prog->lines);

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
        //Size of header = 3 bytes
        fwrite(header, 3, sizeof(char), file);

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

    assert(fileName);

    char* text = readTextFromFile (fileName);

    assert(text);

    return readCommandsFromText (text);
};
