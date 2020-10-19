#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

//PATHS TO INPUT/OUTPUT FILES

#define DIRECTORY ""

#define DEFAULT_READING_FILE_NAME DIRECTORY"in.txt"
#define DEFAULT_WRITING_FILE_NAME DIRECTORY"out.txt"

//FILES FOR UPLOADING

//List of possible commands and their codes
#include "commands.h"

//The struct of stack
#include "stack.h"
#include "stack.c"

//The translator for assembler (to and from)
#include "translator.h"
#include "translator.c"

//The CPU which executes commands
#include "cpu.h"
#include "cpu.c"

//UNIT-tests
#include "tests.c"

//TROUBLES IN TRANSLATOR

int main() {

    stack_t* programStack = newStack (20);

    /*stackPush (programStack, 1);
    stackPush (programStack, 1);
    stackPush (programStack, 7);
    stackPush (programStack, 3);
    stackPush (programStack, -4);
    stackPush (programStack, 7);
    stackPush (programStack, 3);
    stackPush (programStack, 2);
    stackPush (programStack, 1);
    stackPush (programStack, 10);
    stackPush (programStack, 5);
    stackPush (programStack, 2);
    stackPush (programStack, 0);*/

    stackPush (programStack, 0);
    stackPush (programStack, 2);
    stackPush (programStack, 5);
    stackPush (programStack, 10);
    stackPush (programStack, 1);
    stackPush (programStack, 2);
    stackPush (programStack, 3);
    stackPush (programStack, 7);
    stackPush (programStack, -4);
    stackPush (programStack, 3);
    stackPush (programStack, 7);
    stackPush (programStack, 1);
    stackPush (programStack, 1);

    executeProgram (programStack);

    return 0;
}