//version 0.1.2
#include "enum.h"
#include "checker.h"
#include "filemaster.c"

#define DEFAULT_READING_FILE_NAME "in.txt"

#define TYPE_OF_ASSEMBLER_FILES "asm"

int main(int argc, char* argv[]) {
    char *input  = DEFAULT_READING_FILE_NAME;
    fscanf("%s", input);
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-i") == 0  || strcmp(argv[i], "--input")   == 0) {
                input = argv[i];
            }
        }
    }

    //Определение расширения (по буквам расширения)
    char* extension = strstr (input, ".");
    extension += sizeof(char);

    printf ("THE FILE %s IS GOING TO BE CHECKED\n", input);

    if (strcmp (extension, TYPE_OF_ASSEMBLER_FILES) == 0) {
        printf ("This is assembler file.\n");
        return checkAssemblerFile (input);
    } else {
        printf ("This is text file.\n");
        return checkTextFile (input);
    }
};

bool checkAssemblerFile (char* input) {
    //TODO
    bool isOK = true;

    return isOK;
};

bool checkTextFile (char* input) {
    bool isOK = true;

    progText* prog = getCommandsFromText (input);

    for (int i = 0; i < prog->numberOfLines; i++) {

        printf("THIS IS %d LINE\n", i);

        //WARNINGS

        if (prog->lines[i].command[0] == '\0') {
            printf ("Line [%d]: Command '%s' is empty.", i, prog->lines[i].command);
        }

        printf("hey\n");

        if (containsCapitalLetter (prog->lines[i].command)) {
            printf ("Line [%d]: Command '%s' contains some capital letters.", i, prog->lines[i].command);
        }

        //ERRORS


    }


    return isOK;
};

bool containsCapitalLetter (char* str) {
    int pointer = 0;
    while (str[pointer] != '\0') {
        if ('A' <= str[pointer] && str[pointer] <= 'Z') {
            return true;
        }
    }

    return false;
};

