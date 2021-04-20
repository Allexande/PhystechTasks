//
// Created by AlexanderT on 10.04.2021.
//

#ifndef ENGRUSTRANS_FILEMASTER_H
#define ENGRUSTRANS_FILEMASTER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

struct Lines {

    //The text of lines
    char** line;

    //Number of lines
    size_t numberOfLines;

};

//Work with info from file
size_t GetNumberOfBytesOfFile (const char* fileName);
char*  ReadTextFromFile       (const char* fileName);

//Write to file
bool WriteTextInFile (const char* fileName, char* text);

//Work with strings
struct Lines* GetLinesFromText  (char* text);
size_t GetNumberOfSymbol (const char* text, char symbol);

#endif //ENGRUSTRANS_FILEMASTER_H
