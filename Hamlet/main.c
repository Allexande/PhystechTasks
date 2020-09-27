#include <stdio.h>
#include <stdlib.h>

#define DIRECTORY ""

#define DEFAULT_READING_FILE_NAME DIRECTORY"textin.txt"
#define DEFAULT_WRITING_FILE_NAME DIRECTORY"textout.txt"

#define DEFAULT_TESTING_READING_FILE_NAME DIRECTORY"testin.txt"
#define DEFAULT_TESTING_WRITING_FILE_NAME DIRECTORY"testout.txt"

#define READING_BUFFER_SIZE 255

//Files uploading
#include "functions.h"
#include "functions.c"
#include "test.c"

int main(int argc, char *argv[])
{

    char* input  = DEFAULT_READING_FILE_NAME;
    char* output = DEFAULT_WRITING_FILE_NAME;

    processMainArguments(argc, argv, &input, &output);

    int sortResult = doSort(input, output);
    switch (sortResult)
    {
        case 0:
            printf("%s\n", "Program completed successfully.");
            return 0;
        break;

        case 1:
            printf("%s\n", "Failed to read information from file.");
            return 1;
        break;

        case 2:
            printf("%s\n", "Failed to write information to file.");
            return 2;
        break;

        default:
            printf("%s%d\n", "Undefined program behavior. Code of error: ", sortResult);
            return sortResult;
        break;
    }

}
