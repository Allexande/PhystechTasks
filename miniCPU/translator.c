//version 1.0.0

#include "enum.h"

#include "filemaster.c"
#include "translator.h"
#include "stack.h"
#include "string.c"

//#define DEBUG_TRANSLATOR

#define DEFAULT_READING_FILE_NAME "prog_demo.txt"
#define DEFAULT_WRITING_FILE_NAME "prog_demo.asm"

int main (int argc, char* argv[]) {

    char *input  = DEFAULT_READING_FILE_NAME;
    char *output = DEFAULT_WRITING_FILE_NAME;

    if (argc > 1) {
        for (int i = 1; i < argc; i++) {

            if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input")  == 0) {
                input = argv[i];
            }

            if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
                output = argv[i];
            }
        }
    }

    progText* prog = getCommandsFromText (input);

    int resultSize = 0;

    char* code = convertToCode (prog, &resultSize);

    #ifdef DEBUG_TRANSLATOR
        for (int i = 0; i < resultSize; i++) {
            printf("main: code[%d]=%d\n", i, code[i]);
        }
    #endif

    #ifndef DEBUG_TRANSLATOR
        writeProgramInFile (output, code, resultSize, getHeader ());
    #endif

    return 1;
};

char* convertToCode (progText* prog, int* resultSize) {

    assert(prog);

    char* codeOfProg = (char*) calloc (sizeof(char), prog->numberOfLines * 4);
    assert(codeOfProg);

    size_t ofs = 0;

    labelsList* listOfLabels = createLabelsList (prog->numberOfLines);

    //Pre-adding of labels
    for (size_t i = 0; i < prog->numberOfLines; i++) {

        argumentFeatures* features = processArgument (prog->lines[i].arg);

        #define DEF_CMD(name, num, argum, code)                                             \
                if (strcmp(prog->lines[i].command, #name) == 0) {                           \
                    if (argum == 1) {                                                       \
                        ofs += sizeof(char);                                                \
                        if (features->haveConstant) {                                       \
                            ofs += sizeof(char);                                            \
                        }                                                                   \
                        if (features->haveRegister) {                                       \
                            ofs += sizeof(char);                                            \
                        }                                                                   \
                    }                                                                       \
                    if (argum == 2) {                                                       \
                        ofs += sizeof(char);                                                \
                    }                                                                       \
                } else

        #include "commands.h"

            //else
            {
                #ifdef DEBUG_TRANSLATOR
                    printf("convertToCode: Unknown command during pre-translation prog->lines[%d].command=%s\n", i, prog->lines[i].command);
                #endif
            }



        #undef DEF_CMD

        //Checking is it a label
        if (getNumberOfSymbol (prog->lines[i].command, ':') > 0) {

            #ifdef DEBUG_TRANSLATOR
                printf("convertToCode: New label prog->lines[%d].command=%s\n", i, prog->lines[i].command);
            #endif

            FunctionalString* thisCommand = convertToFunctionalString (prog->lines[i].command);
            addLabel (thisCommand->str, listOfLabels, ofs);

            #ifdef DEBUG_TRANSLATOR
                printf("convertToCode: New label was added. It's adress is %d\n", listOfLabels->labels[listOfLabels->length-1].adress);
            #endif

        }

        ofs++;
    }

    #ifdef DEBUG_TRANSLATOR
        for(size_t k = 0; k < listOfLabels->length; k++) {
            printf("convertToCode: listOfLabels->labels[%d].name=%s listOfLabels->labels[%d].adress=%d\n", k, listOfLabels->labels[k].name, k, listOfLabels->labels[k].adress);
        }
    #endif

    ofs = 0;

    for (size_t i = 0; i < prog->numberOfLines; i++) {

        if (prog->lines[i].command == "skip") {
            continue;
        }

        argumentFeatures* features = processArgument (prog->lines[i].arg);

        #ifdef DEBUG_TRANSLATOR
            printf("convertToCode: prog->lines[%d].command=%s prog->lines[%d].arg=%s\n", i, prog->lines[i].command, i, prog->lines[i].arg);
        #endif

        #define DEF_CMD(name, num, argum, code)                                                   \
                if (strcmp(prog->lines[i].command, #name) == 0) {                                 \
                    codeOfProg[ofs] = num;                                                        \
                    ofs += sizeof(char);                                                          \
                    if (argum == 1) {                                                             \
                        codeOfProg[ofs] = addingNumberForCodeOfCommand (features);                \
                        ofs += sizeof(char);                                                      \
                        writeArguments (prog->lines[i].arg, codeOfProg, features, &ofs);          \
                    }                                                                             \
                    if (argum == 2) {                                                             \
                        writeJumpArguments (prog->lines[i].arg, listOfLabels, codeOfProg, &ofs);  \
                    }                                                                             \
                } else
        #include "commands.h"

            //else
            {
                #ifdef DEBUG_TRANSLATOR
                    printf("convertToCode: Unknown command during translation prog->lines[%d].command=%s\n", i, prog->lines[i].command);
                 #endif
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
    assert(newLabelsList->labels);

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
        codeOfProg[*ofs] = argValue->str[1] - 'a';
        *ofs += sizeof(char);
        //Deleting of register ("r_x+")
        argValue = cutFunctionalString (argValue, 4, argValue->length);

    }

    if (features->haveConstant) {

        codeOfProg[*ofs] = atof(argValue->str);
        *ofs += sizeof(char);

    }

};

void writeJumpArguments (char* arg, labelsList* labels, char* codeOfProg, size_t* ofs) {

    assert(labels);
    assert(codeOfProg);

    if (isInteger(arg[0])) {
        codeOfProg[*ofs] = atof(arg);

    } else {

        for (int i = 0; i < labels->length; i++) {

            if (strcmp(labels->labels[i].name, arg) == 0) {

                codeOfProg[*ofs] = labels->labels[i].adress;
                break;

            }
        }

    }

    *ofs += sizeof(char);
};
