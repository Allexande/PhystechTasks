size_t getNumberOfBytes (const char *fileName) {

    assert (fileName);

    FILE *file = fopen (fileName, "r");

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

char* getText (const char *fileName) {

    assert (fileName);

    size_t length = getNumberOfBytes (fileName);

    if (length < 1) {
        return NULL;
    }

    char* text = (char *) calloc (length + 2, sizeof(char));

    FILE *file = fopen (fileName, "r");

    if (file == NULL) {
        return NULL;

    } else {

        //*(text) = '\0';

        int lengthWasRead = fread ((text + 1), sizeof(char), length, file);
        fclose (file);
        *(text+lengthWasRead) = '\0';
        return text;
    }
};

char* getTextOfProgram (const char *fileName) {

    assert (fileName);

    char* text = getText (fileName);

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

};

bool isInteger (char symbol) {
    return (symbol >= '0' && symbol <= '9');
};

bool isLetter (char symbol) {
    return ((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z'));
}

size_t getLengthOfString (char* str) {
    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    };

    return length;
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
};

int getTheNumberOfCommand (char* textOfCommand) {

     for (int i = 0; i < (sizeof (command) / sizeof (command[0])); i++) {
        if (strcmp (textOfCommand, command[i]) == 0) {
            return i;
        }
     }

     return NAN;
}