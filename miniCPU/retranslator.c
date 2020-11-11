//version 0.2.0
#include "enum.h"

#include "string.c"
#include "filemaster.c"
#include "retranslator.h"
#include "stack.h"

#define ADD(adding);                                                        \
    positionInAdding = 0;                                                   \
    while (adding[positionInAdding]!='\0') {                                \
        text[positionInText+positionInAdding]=adding[positionInAdding];     \
        positionInAdding++;                                                 \
    }                                                                       \
    positionInText+=positionInAdding;

#define DEFAULT_READING_FILE_NAME "out.asm"
#define DEFAULT_WRITING_FILE_NAME "retranslated.txt"

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

    char* BinaryCode = readBinaryFromFile (input);

    char* text = convertToText (BinaryCode);

    bool success = writeTextInFile (output, text);

    return success;
};

char* convertToText (char* BinaryCode) {

    //Memory allocated with enough
    char* text = (char*) calloc (sizeof(char), strlen(BinaryCode) * 10);
    assert(text);

    size_t ofs = 3;

    size_t positionInAdding = 0;
    size_t positionInText   = 0;

    while (true) {

        #define DEF_CMD(name, num, argum, code)                                         \
                    case num:                                                           \
                    {                                                                   \
                        ADD(#name);                                                     \
                        if (num == 32 || num == 64) {                                   \
                            ADD(" ");                                                   \
                            int mode = BinaryCode[++ofs];                               \
                            FunctionalString* toInsert = createFunctionalString (0);    \
                                                                                        \
                            char reg[4];                                                \
                            if (mode & 2) {                                             \
                                reg[0] = 'r';                                           \
                                reg[1] = 'a'+ BinaryCode[++ofs] - 1;                    \
                                reg[2] = 'x';                                           \
                                reg[3] = '\0';                                          \
                            }                                                           \
                                                                                        \
                            char* number;                                               \
                            if (mode == 0) { ofs += 1; }                                \
                            if (mode & 1) {                                             \
                                number = intToString(BinaryCode[++ofs]);                \
                            }                                                           \
                                                                                        \
                            if (mode & 4) {                                             \
                                ADD("[");                                               \
                                if (mode & 2) { ADD(reg);    }                          \
                                if (mode & 1) { ADD(number); }                          \
                                ADD("]");                                               \
                            } else {                                                    \
                                if (mode & 2) { ADD(reg);    }                          \
                                if (mode & 1) { ADD(number); }                          \
                            }                                                           \
                        }                                                               \
                                                                                        \
                        if (num >= 20 && num <= 27) {                                   \
                            ADD(" ");                                                   \
                            ofs++;                                                      \
                            ADD(intToString (BinaryCode[ofs]));                         \
                        }                                                               \
                                                                                        \
                        ADD("\n");                                                      \
                        break;                                                          \
                    }

        switch (BinaryCode[ofs]) {

            #include "commands.h"

            default:
            {
                ADD("Unknown command\n");
                break;
            }
        }

        #undef DEF_CMD


        if (BinaryCode[ofs] == 127) {
            break;
        }

        ofs++;
    }

    return text;
};

char* intToString (int number) {

    char* result = (char*) calloc (sizeof(char), numberOfNumerals (number));

    assert(result);

    sprintf(result, "%d", number);

    return result;
};

size_t numberOfNumerals (int number) {

    size_t numerals = 1;

    while ((number /= 10) > 0) {
        numerals++;
    }

    return numerals;
}
