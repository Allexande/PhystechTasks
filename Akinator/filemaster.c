//Version 0.8

#include "filemaster.h"

size_t GetNumberOfBytesOfFile (const char *fileName) {

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
}

char* ReadTextFromFile (const char *fileName) {

    assert (fileName);

    size_t length = GetNumberOfBytesOfFile (fileName);

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

}

bool WriteTextInFile (const char *fileName, char* text) {

    assert (fileName);

    FILE *file = fopen (fileName, "w");

    if (file == NULL) {
        return false;

    } else {

        fputs(text, file);
        fclose(file);

    }

    return true;
}

Lines* GetLinesFromText (char* text) {

    Lines* newLines = (Lines*) calloc (sizeof(Lines), 1);
    assert (newLines);

    size_t numberOfLines = GetNumberOfSymbol (text, '\n');

    newLines->line = (char**) calloc (sizeof(char*), numberOfLines);
    assert (newLines->line);

    newLines->numberOfLines = numberOfLines;

    size_t pointerOnText = 0;
    for (size_t lineNum = 0; lineNum < numberOfLines; lineNum++) {

        size_t length = 0;
        while (text[length + pointerOnText] != '\n') {
            length++;
        }
        newLines->line[lineNum] = (char*) calloc (sizeof(char), length + 2);

        size_t pointerOnLine = 0;
        while (text[pointerOnText] != '\n') {
            newLines->line[lineNum][pointerOnLine++] = text[pointerOnText++];
        }
        newLines->line[lineNum][++pointerOnLine] = '\0';
        pointerOnText++;
    }

    return newLines;
}


size_t GetNumberOfSymbol (const char *text, char symbol) {

    assert (text);

    size_t symbols = 0;
    int point = 0;

    while (*(text + point) != '\0') {

        if (*(text + point) == symbol) symbols++;
        point++;

    }

    return symbols;
}

bool FilesContainSameText (const char *first, const char *second) {

    char* firstText  = ReadTextFromFile (first);
    char* secondText = ReadTextFromFile (second);

    if ((first == NULL) || (second == NULL)) {
        return false;
    }

    if (strcmp (firstText, secondText) == 0) {
        return true;
    }

    return false;
}

int CheckIfTextIsDatabase (char* text) {

    if (text == NULL) {
        return EMPTY;
    }

    Lines* textLines = GetLinesFromText (text);

    char*   brackets = (char*) calloc (sizeof(char), textLines->numberOfLines);
    assert (brackets);
    size_t bracketsNumber = 0;

    for (size_t pointer = 0; pointer < textLines->numberOfLines; pointer++) {

        if ((textLines->line[pointer][0] == '}') && (bracketsNumber == 0)) {
            return OPEN_BLOCK;
        }

        if ((textLines->line[pointer][0] == '}') && (brackets[bracketsNumber] == '{')) {
            bracketsNumber--;
        }

        if (textLines->line[pointer][0] == '{') {
            brackets[++bracketsNumber] = '{';
        }

        if ((textLines->line[pointer][0] == '{') || (textLines->line[pointer][0] == '}')) {
            if (textLines->line[pointer][1] != '\0') {
                return WRONG_DIVIDER;
            }
        } else {
            if (CheckLine (textLines->line[pointer])) {
                return CheckLine (textLines->line[pointer]);
            }
        }

        if (bracketsNumber > MAXIMUM_TREE_DEEP) {
            return TOO_DEEP;
        }
    }

    if (bracketsNumber > 0) {
        return WRONG_BLOCKS;
    }

    return IS_OK;
}

DatabaseError CheckLine (char* line) {

    size_t pointer = 0;

    if (line[pointer] != '"') {
        return WRONG_BEGIN;
    }

    while (line[++pointer] != NULL) {

        if (line[pointer] == '"') {
            if (line[pointer + 1] == '\0') {
                return IS_OK;
            } else {
                return WRONG_LINE;
            }
        }

    }

    return WRONG_END;
}
