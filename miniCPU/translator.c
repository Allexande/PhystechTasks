//version 0.1.2
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


    double* code = convertToCode (prog, &resultSize);

    writeProgramInFile (output, code, resultSize, getHeader ());

    return 0;
};

double* convertToCode (progText* prog, int* resultSize) {
    double* codeOfProg = (double*) calloc (sizeof(double), prog->numberOfLines * 2);
    unsigned int ofs = 0;

    //Память выделяется с запасом: сколько меток сколько строк
    labelsList* labels = createLabelsList (prog->numberOfLines);

    //Предварительная запись всех меток
    for (int i = 0; i < prog->numberOfLines; i++) {
        //Проверка является ли меткой
        if (getNumberOfSymbol (prog->lines[i].command, ':') > 0) {
            FunctionalString* thisCommand = convertToFunctionalString (prog->lines[i].command);
            thisCommand->length--;
            addLabel (thisCommand->str, labels, i);
        }
    }

    for (int i = 0; i < prog->numberOfLines; i++) {

        argumentFeatures* features = processArgument (prog->lines[i].arg);
        //int toAdd = addingNumberForCodeOfCommand (features);

        #define DEF_CMD(name, num, argum, code)                                                   \
                if (strcmp(prog->lines[i].command, #name) == 0) {                              \
                    if (argum == 1) {                                                                            \
                        codeOfProg[ofs] = num + addingNumberForCodeOfCommand (features);           \
                    } else {                                                                \
                        codeOfProg[ofs] = num;                                                 \
                    }                                                                        \
                    ofs += sizeof(char);	                                                    \
                    if (argum == 1) {                                                                           \
                        writeArguments (prog->lines[i].arg, codeOfProg, features, &ofs);                      \
                    }                                                                         \
                    if (argum == 2) {                                                                           \
                        writeJumpArguments (prog->lines[i].arg, labels, codeOfProg, &ofs); \
                    }                                                                           \
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

void addLabel (char* labelName, labelsList* labels, int adressOfLabel) {
    labels->labels[labels->length].name = labelName; //!!!!!
    labels->labels[labels->length].adress = adressOfLabel;
    labels->length++;
};

labelsList* createLabelsList (size_t capacity) {
    labelsList* newLabelsList = (labelsList*) calloc (sizeof(labelsList), 1);
    newLabelsList->labels = (label*) calloc (sizeof(label), capacity);
    newLabelsList->length = 0;
    return newLabelsList;
};

argumentFeatures* processArgument (char* argument) {
    argumentFeatures* features = (argumentFeatures*) calloc (sizeof(argumentFeatures), 1);

    features->numberOfArguments = getNumberOfSymbol (argument, '+')
                                //+ getNumberOfSymbol (argument, '-')
                                + 1;

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

void writeArguments (char* arg, double* codeOfProg, argumentFeatures* features, unsigned int* ofs) {
    FunctionalString* argValue = convertToFunctionalString (arg);

    if (features->haveMemory) {
        //Удаление скобочек
        argValue = cutFunctionalString (argValue, 1, argValue->length - 1);
    }

    if (features->haveRegister) {
        codeOfProg[*ofs] = argValue->str[2] - 'a';
        *ofs += sizeof(double);
        //Удаление регистра и знака после него ("rdx+")
        argValue = cutFunctionalString (argValue, 4, argValue->length);
    }

    if (features->haveConstant) {
        codeOfProg[*ofs] = atof(argValue->str);
        *ofs += sizeof(double);
    }

};

void writeJumpArguments (char* arg, labelsList* labels, double* codeOfProg, unsigned int* ofs) {
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



//Может не работать потому что новые метки все время пишутся в самый конец labels
//из-за sizeof(labels) / sizeof(label)
/*
bool processLabel (char* labelName, labelsList* labels, int adressOfLabel) {
    bool thereAlreadyWasThisLabel = false;
    for (int i = 0; i < (sizeof(labels) / sizeof(label)); i++) {
        if (strcmp(labels[i].name, labelName) == 0) {
            thereAlreadyWasThisLabel = true;
            break;
        }
    }
    if (thereAlreadyWasThisLabel) {
        return false;
    } else {
        //Вот тут что-то не так
        labels[sizeof(labels) / sizeof(label)].name = labelName;
        labels[sizeof(labels) / sizeof(label)].adress = adressOfLabel;
        return true;
    }
};
*/

/*char* getTextOfProgram (const char *fileName) {

    assert (fileName);

    char* text = readTextFromFile (fileName);

    char* textOfProgram = (char *) calloc (getLengthOfString(text), sizeof(char));

    int pointOnText = 0;
    int pointOnTextOfProgram = 0;

    while (text[pointOnText] != '\0') {
        if (isLetter(text[pointOnText])) {
            textOfProgram[pointOnTextOfProgram] = tolower(text[pointOnText]);
            pointOnTextOfProgram++;
        } else {
            if (isInteger(text[pointOnText])) {
                textOfProgram[pointOnTextOfProgram] = text[pointOnText];
                pointOnTextOfProgram++;
            }
        }
        pointOnText++;
    }

    return textOfProgram;

};*/

/*
char* cleanText (char* text) {

    char* cleanText = (char *) calloc (getLengthOfString(text), sizeof(char));
    int pointInCleanText = 0;

    for (int i = 0; i < getLengthOfString(text); i++) {

        if (isInteger (text[i])) {
            cleanText[pointInCleanText] = text[i];
            pointInCleanText++;
        }

        if (isLetter (text[i])) {
            cleanText[pointInCleanText] = tolower (text[i]);
            pointInCleanText++;
        }

        if ((i > 0) && (text[i] == '\n') && (text[i-1] != '\n')) {
            cleanText[pointInCleanText] = '\n';
            pointInCleanText++;
        }

        if ((i > 0) && (text[i] == ' ') && (text[i-1] != ' ')) {
            cleanText[pointInCleanText] = ' ';
            pointInCleanText++;
        }

    }

    return cleanText;

};

size_t getLengthOfString (char* str) {
    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    };

    return length;
};*/

/*
stack_t* compileProgram (const char *textOfProgram) {

    stack_t* programStack = newStack (getNumberOfSymbol (textOfProgram, '\n'));

    int point = 0;
    char* InputCommand = "";
    while (textOfProgram[point] != '\0') {

        for (int i = 0; i < 3; i++) {
            InputCommand[i] = textOfProgram[point + i];
        }

        stackPush (programStack, getTheNumberOfCommand (InputCommand));

        point += 4;
        if (InputCommand == "pus") {
            char* doubleValue = "";
            int pointerOnDoubleValue = 0;

            while (textOfProgram[point] != '\0' || textOfProgram[point] != '\n') {
                doubleValue[pointerOnDoubleValue] = textOfProgram[point];
                point++;
                pointerOnDoubleValue++;
            }

            char** rubbish;
            stackPush (programStack, strtod (doubleValue, rubbish));
            point++;
        }
    }

    return programStack;
};*/

/*
double* compileProgram (const char *textOfProgram) {

    double* program = (double*) calloc (getNumberOfSymbol (textOfProgram, '\n'), sizeof (double));

    int point = 0;
    char* InputCommand = "";
    while (textOfProgram[point] != '\0') {

    }

    return program;
}

int getTheNumberOfCommand (const char* textOfCommand) {

     for (int i = 0; i < NumberOfCommands; i++) {
        if (strcmp (textOfCommand, command[i]) == 0) {
            return i;
        }
     }

     return NAN;
}
*/
