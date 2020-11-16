//version 1.0.0

struct label {

    char* name;
    size_t adress;

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

char* convertToCode (progText* prog, int* resultSize);

char* getHeader ();

bool isInteger (char symbol);

bool isLetter (char symbol);

void addLabel (char* labelName, labelsList* labels, size_t adressOfLabel);

labelsList* createLabelsList (size_t capacity);

argumentFeatures* processArgument (char* argument);

int addingNumberForCodeOfCommand (argumentFeatures* features);

void writeArguments (char* arg, char* codeOfProg, argumentFeatures* features, size_t* ofs);

void writeJumpArguments (char* arg, labelsList* labels, char* codeOfProg, size_t* ofs);
