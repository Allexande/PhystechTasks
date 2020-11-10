//version 0.1.3
struct label {
    char* name;
    unsigned int adress;
};

struct labelsList {
    label* labels;
    size_t length;
};

struct argumentFeatures {
    int numberOfArguments;
    bool haveConstant;
    bool haveRegister;
    bool haveMemory;
};

double* convertToCode (progText* prog, int* resultSize);

char* getHeader ();

bool isInteger (char symbol);

bool isLetter (char symbol);

void addLabel (char* labelName, labelsList* labels, int adressOfLabel);

labelsList* createLabelsList (size_t capacity);

argumentFeatures* processArgument (char* argument);

int addingNumberForCodeOfCommand (argumentFeatures* features);

void writeArguments (char* arg, double* codeOfProg, argumentFeatures* features, unsigned int* ofs);

void writeJumpArguments (char* arg, labelsList* labels, double* codeOfProg, unsigned int* ofs);

//char* getTextOfProgram (const char *fileName); //DONT WORK???

/*
char* cleanText (char* text);

size_t getLengthOfString (char* str);

double* compileProgram (const char *textOfProgram);

int getTheNumberOfCommand (const char* textOfCommand);
*/
