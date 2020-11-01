//version 0.1.2
#define MAXIMUM_LENGTH_OF_WORD 100

struct line {
    char command[MAXIMUM_LENGTH_OF_WORD];
    char arg[MAXIMUM_LENGTH_OF_WORD];
};

struct progText {
    line* lines;
    size_t numberOfLines;
};

size_t getNumberOfBytesOfFile (const char *fileName);

void clearStr (char* str);

progText* getCommandsFromText (const char *fileName);

char* readTextFromFile (const char *fileName);

bool writeProgramInFile (const char *fileName, double* progText, int progLength, char* header);

bool writeTextInFile (const char *fileName, char* text);

size_t getNumberOfSymbol (const char *text, char symbol);

progText* readCommandsFromText (const char *fileName);
