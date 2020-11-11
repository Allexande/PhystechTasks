//version 0.2.0
#include "enum.h"

#include "checker.h"
#include "filemaster.c"

#define DEFAULT_READING_FILE_NAME "in.txt"

#define TYPE_OF_ASSEMBLER_FILES "asm"

int main(int argc, char* argv[]) {

    char *input  = DEFAULT_READING_FILE_NAME;

    if (argc > 1) {

        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-i") == 0  || strcmp(argv[i], "--input")   == 0) {
                input = argv[i];
            }
        }

    }

    //Getting file extension
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
            printf ("WARNING Line [%d]: Command '%s' is empty.\n", i, prog->lines[i].command);
        }

        if (containsCapitalLetter (prog->lines[i].command)) {
            printf ("WARNING Line [%d]: Command '%s' contains some capital letters.\n", i, prog->lines[i].command);
        }

        //ERRORS
        #define DEF_CMD(name, num, arg, code) \
            strcmp(prog->lines[i].command, #name) != 0 &&
        if (
            #include "commands.h"
            prog->lines[i].command[0] != '\0') {
                printf ("ERROR Line [%d]: Command '%s' does not exist.\n", i, prog->lines[i].command);
            }
        #undef DEF_CMD

        // ----

        size_t rigthArg;
        if (prog->lines[i].arg[0] == '\0') {
            rigthArg = 0;
        } else {
            rigthArg = getNumberOfSymbol (prog->lines[i].arg, ' ') + 1;
        }

        //Checking number of arguments
        /*
        #define DEF_CMD(name, num, arg, code)                               \
            ((rigthArg != arg) && (strcmp(prog->lines[i].command, #name) == 0)) ||

        if (
            #include "commands.h"
            false) {
                printf ("ERROR Line [%d]: Command '%s' have too few arguments (%d).\n", i, prog->lines[i].command, rigthArg);
            }
        #undef DEF_CMD
        */


    }

    return isOK;
};

bool containsCapitalLetter (char* str) {
    int pointer = 0;
    while (str[pointer] != '\0') {
        if ('A' <= str[pointer] && str[pointer] <= 'Z') {
            return true;
        }
        pointer++;
    }

    return false;
};

