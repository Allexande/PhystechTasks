//version 0.2.1

#include "enum.h"

#include "filemaster.c"
#include "translator.h"
#include "stack.h"
#include "string.c"

#define DEFAULT_READING_FILE_NAME "in.txt"
#define DEFAULT_WRITING_FILE_NAME "out.asm"

int main(int argc, char* argv[]) {

    char *input  = DEFAULT_READING_FILE_NAME;
    char *output = DEFAULT_WRITING_FILE_NAME;

    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-i") == 0  || strcmp(argv[i], "--input")   == 0) {
                input = argv[i];
            }

            if (strcmp(argv[i], "-o") == 0  || strcmp(argv[i], "--output")  == 0) {
                output = argv[i];
            }
        }
    }

    progText* prog = getCommandsFromText (input);

    int resultSize = 0;

    char* code = convertToCode (prog, &resultSize);

    writeProgramInFile (output, code, resultSize, getHeader ());

    return 0;
};

char* convertToCode (progText* prog, int* resultSize) {

    assert(prog);
    assert(prog->numberOfLines);

    char* codeOfProg = (char*) calloc (sizeof(char), prog->numberOfLines * 4);
    assert(codeOfProg);

    size_t ofs = 0;

    labelsList* labels = createLabelsList (prog->numberOfLines);

    //Pre-adding of labels
    for (size_t i = 0; i < prog->numberOfLines; i++) {
        //Checking is it a label
        if (getNumberOfSymbol (prog->lines[i].command, ':') > 0) {
            FunctionalString* thisCommand = convertToFunctionalString (prog->lines[i].command);
            thisCommand->length--;
            addLabel (thisCommand->str, labels, i);
        }
    }

    for (size_t i = 0; i < prog->numberOfLines; i++) {

        argumentFeatures* features = processArgument (prog->lines[i].arg);

        #define DEF_CMD(name, num, argum, code)                                             \
                if (strcmp(prog->lines[i].command, #name) == 0) {                           \
                    if (argum == 1) {                                                       \
                        codeOfProg[ofs] = num + addingNumberForCodeOfCommand (features);    \
                    } else {                                                                \
                        codeOfProg[ofs] = num;                                              \
                    }                                                                       \
                    ofs += sizeof(char);	                                                \
                    if (argum == 1) {                                                       \
                        writeArguments (prog->lines[i].arg, codeOfProg, features, &ofs);    \
                    }                                                                       \
                    if (argum == 2) {                                                       \
                        writeJumpArguments (prog->lines[i].arg, labels, codeOfProg, &ofs);  \
                    }                                                                       \
                } else
        #include "commands.h"

            //else
            {
                printf("ERROR ON LINE %d\n%s\n", i, prog->lines[i].command);
            }

    }

    #undef DEF_CMD
    *resultSize = ofs;
    return codeOfProg;
};

char* getHeader () {
    return "TA1";
};

bool isInteger (char symbol) {
    return (symbol >= '0' && symbol <= '9');
};

bool isLetter (char symbol) {
    return ((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z'));
};

void addLabel (char* labelName, labelsList* labels, size_t adressOfLabel) {

    assert(labels);

    labels->labels[labels->length].name = labelName;
    labels->labels[labels->length].adress = adressOfLabel;
    labels->length++;

};

labelsList* createLabelsList (size_t capacity) {

    labelsList* newLabelsList = (labelsList*) calloc (sizeof(labelsList), 1);
    assert(newLabelsList);

    newLabelsList->labels = (label*) calloc (sizeof(label), capacity);
    newLabelsList->length = 0;

    return newLabelsList;
};

argumentFeatures* processArgument (char* argument) {

    argumentFeatures* features = (argumentFeatures*) calloc (sizeof(argumentFeatures), 1);
    assert(features);

    features->numberOfArguments = getNumberOfSymbol (argument, '+') + 1;

    features->haveConstant = false;
    features->haveRegister = false;
    features->haveMemory = false;

    int pointer = 0;
    while (argument[pointer] != '\0') {

        if (isLetter(argument[pointer])) {
            features->haveRegister = true;
        }

        if (isInteger(argument[pointer])) {
            features->haveConstant = true;
        }

        if (argument[pointer] == '[') {
            features->haveMemory = true;
        }

        pointer++;
    }

    return features;
};

int addingNumberForCodeOfCommand (argumentFeatures* features) {

    assert(features);

    int addingNumber = 0;

    if (features->haveConstant) {
        addingNumber += 1;
    }

    if (features->haveRegister) {
        addingNumber += 2;
    }

    if (features->haveMemory) {
        addingNumber += 4;
    }

    return addingNumber;
};

void writeArguments (char* arg, char* codeOfProg, argumentFeatures* features, size_t* ofs) {

    assert(codeOfProg);
    assert(features);

    FunctionalString* argValue = convertToFunctionalString (arg);

    if (features->haveMemory) {
        //Deleting of '[' and ']'
        argValue = cutFunctionalString (argValue, 1, argValue->length - 1);
    }

    if (features->haveRegister) {

        codeOfProg[*ofs] = argValue->str[2] - 'a';
        *ofs += sizeof(double);
        //Deleting of register ("r_x+")
        argValue = cutFunctionalString (argValue, 4, argValue->length);

    }

    if (features->haveConstant) {

        codeOfProg[*ofs] = atof(argValue->str);
        *ofs += sizeof(double);

    }

};

void writeJumpArguments (char* arg, labelsList* labels, char* codeOfProg, size_t* ofs) {

    assert(labels);
    assert(codeOfProg);

    if (isInteger(arg[0])) {
        codeOfProg[*ofs] = atof(arg);

    } else {

        for (int i = 0; i < labels->length; i++) {
            if (labels->labels[i].name == arg) {
                codeOfProg[*ofs] = labels->labels[i].adress;
                break;
            }
        }

    }

    *ofs += sizeof(double);
};
