#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <mem.h>

#include "random.c"
#include "filemaster.c"

//#include "translator.c"

char* generateRandomText (size_t length) {

    char* randomText = (char*) calloc (sizeof (char), length);

    setRandSeed();
    for (int i = 0; i < length; i++) {
        randomText[i] = geterateRandomChar ();
    }

    return randomText;
}

//TESTING OF FILEMASTER
bool testOfFilemaster (const char *fileName, size_t length) {

    char* randomText = generateRandomText (length);

    if (!writeTextInFile (fileName, randomText)) {
        return false;
    };

    char* result = readTextFromFile (fileName);

    return (strcmp(result, randomText) == 0);
}
/*
bool testOfGetLengthOfString (size_t length) {

    char* randomStr = generateRandomText (length);

    return length == getLengthOfString (randomStr);
}
*/
bool testGetCommandsFromText () {

    progText* prog = getCommandsFromText ("testin.txt");

    printf ("========== DUMP OUT OF THE TEST() ==========\n");
    for (int i = 0; i < prog->numberOfLines; i++) {
        printf ("LINE NUMBER %d\n", i);
        printf ("command=%s\n", prog->lines[i].command);
        printf ("arg=%s\n", prog->lines[i].arg);
    }

}

//TESTING OF TRANSLATOR
/*
bool testOfCleanText () {

    char* exampleText = "out\nOUUTUUT\n3dd 434\n\ndFffo    0\n";
    char* normText    = "out\nouutuut\n3dd 434\ndFffo 0\n\0";

    return (strcmp(cleanText (exampleText), normText) >= 0);
}

bool testOfGetTheNumberOfCommand () {

    setRandSeed();

    int randomInt = geterateRandomInt(0, NumberOfCommands);

    return (randomInt == getTheNumberOfCommand (command[randomInt]));
}

bool testOfCompileProgram () {

    char* exampleText = "in\nin\npush 6\nhlt";

}
*/

//Copy of functions from translator.c

struct label {
    char* name;
    unsigned int adress;
};

struct argumentFeatures {
    int numberOfArguments;
    bool haveConstant;
    bool haveRegister;
    bool haveMemory;
};


bool isInteger (char symbol) {
    return (symbol >= '0' && symbol <= '9');
};

bool isLetter (char symbol) {
    return ((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z'));
}


//Может не работать потому что новые метки все время пишутся в самый конец labels
//из-за sizeof(labels) / sizeof(label)
int labelsAdded = 0;

bool processLabel (char* labelName, label* labels, int adressOfLabel) {
printf("processLabel started\n");
printf("labelName=%s adressOfLabel=%d labelName[0]=%c\n", labelName, adressOfLabel, labelName[0]);

    bool thereAlreadyWasThisLabel = false;
    for (int i = 0; i < labelsAdded; i++) {
        if (strcmp(labels[i].name, labelName) == 0) {
            thereAlreadyWasThisLabel = true;
            break;
        }
    }

    printf("Now processLabel there. thereAlreadyWasThisLabel=%d\n",thereAlreadyWasThisLabel);

    if (thereAlreadyWasThisLabel) {
        return false;
    } else {
        printf("+Now there\n");
        int oi = 0;
        while (labelName[oi] != '\0') {
            printf("oi=%d labelName[oi]=%c\n", oi, labelName[oi]);
            printf("labels[labelsAdded].name=%s\n", labels[labelsAdded].name);
            labels[labelsAdded].name[oi] = labelName[oi];
            oi++;
        }
        printf("+++Now there\n");
        labels[labelsAdded].adress = adressOfLabel;
        labelsAdded++;
        printf("++++++Now there\n");
        return true;
    }
};

argumentFeatures* processArgument (char* argument) {
printf("processArgument started\n");

    argumentFeatures* features = (argumentFeatures*) calloc (sizeof(argumentFeatures), 1);

    features->numberOfArguments = getNumberOfSymbol (argument, '+')
                                + getNumberOfSymbol (argument, '-')
                                + 1;

    features->haveConstant = false;
    features->haveRegister = false;
    features->haveMemory = false;
    int pointer = 0;
    while (argument[pointer] != '\0') {
//printf("pointer=%d\n", pointer);

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

printf("processArgument finished\n");

    return features;
};

//OK
void testProcessArgument () {
    char* arg = "px";

    argumentFeatures* feat = processArgument (arg);

    printf("feat->numberOfArguments=%d\n", feat->numberOfArguments);
    printf("feat->haveConstant=%d\n", feat->haveConstant);
    printf("feat->haveRegister=%d\n", feat->haveRegister);
    printf("feat->haveMemory=%d\n", feat->haveMemory);
}

void testProcessLabel () {
    progText* prog = getCommandsFromText ("testin.txt");

    label* labels = (label*) calloc (sizeof(label), prog->numberOfLines);

printf("There is OK and prog->numberOfLines=%d\n", prog->numberOfLines);

    for (int i = 0; i < prog->numberOfLines; i++) {
        printf("i=%d\n", i);

        if (getNumberOfSymbol (prog->lines[i].command, ':') > 0) {
            processLabel (prog->lines[i].command, labels, i);
        }
    }

    printf ("========== DUMP OUT OF THE TEST() ==========\n");
    for (int i = 0; i < sizeof(labels) / sizeof(label); i++) {
        printf("labels[%d].name=%s labels[%d]=%d", i, labels[i].name, i, labels[i].adress);
    }

}

int main() {

    //testGetCommandsFromText ();
    //testProcessArgument ();

    //testProcessLabel ();



    return 0;
}
