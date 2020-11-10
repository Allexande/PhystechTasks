//version 0.1.3
#include "enum.h"

#include "string.c"
#include "filemaster.c"
#include "retranslator.h"
#include "stack.h"

/*
#define ADD(ArrayOfChar); text = mergeFunctionalStrings (text,  \
convertToFunctionalString (ArrayOfChar));
*/

#define ADD(adding);                                                      \
    /*printf("Adding %s: ", adding);*/                                                \
    positionInAdding = 0;                                               \
    while (adding[positionInAdding]!='\0') {                                                                   \
        text[positionInText+positionInAdding]=adding[positionInAdding];      \
        /*printf("%c ", adding[positionInAdding]);*/     \
        positionInAdding++;                                                 \
    }                                                                   \
    positionInText+=positionInAdding;
    /*printf("\n");*/

//#define DEFAULT_READING_FILE_NAME "out.asm"
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

    /*char* FunctionalBinaryCode = convertToFunctionalString (BinaryCode);*/

    /*
    printf("FunctionalBinaryCode->length = %d", FunctionalBinaryCode->length);
    */
    char* text = convertToText (BinaryCode);

    bool success = writeTextInFile (output, text);

    return success;
};

char* convertToText (char* BinaryCode) {

    /*
    FunctionalString* text = createFunctionalString (0);

    ADD(";This is retranslated code.\n");
    */
    char* text = (char*) calloc (sizeof(char), strlen(BinaryCode) * 10); //Память выделяется с запасом

    unsigned int ofs = 3;

    size_t positionInAdding = 0;
    size_t positionInText   = 0;

    while (true) {

        printf("BinaryCode[%d] = %d\n",ofs, BinaryCode[ofs]);

        #define DEF_CMD(name, num, argum, code)                                               \
                    case num:                                                                 \
                    {                                                                         \
                        ADD(#name);                                                           \
                        if (num == 32 || num == 64) {                                         \
                            ADD(" ");                                                         \
                            int mode = BinaryCode[++ofs]; printf("mode=%d\n",mode);                                     \
                            FunctionalString* toInsert = createFunctionalString(0);           \
                            char reg[4];                                                      \
                            if (mode & 2) {                                                   \
                            reg[0] = 'r';                                                     \
                                reg[0] = 'r';                                                 \
                                reg[1] = 'a'+ BinaryCode[++ofs] - 1;                              \
                                reg[2] = 'x';                                                 \
                                reg[3] = '\0';                                                 \
                                /*ADD(reg); printf("reg=%s\n",reg);*/                                                     \
                            }                                                                 \
                            char* number;                \
                            if (mode == 0) {ofs+=1;}                                                    \
                            if (mode & 1) {                                                   \
                                number = intToString(BinaryCode[++ofs]);                      \
                                /*ADD("+");                                                     \
                                ADD(number); printf("number=%d\n",number);*/                                                  \
                            }                                                                 \
                            if (mode & 4) {                                                   \
                                ADD("[");                                                     \
                                if (mode & 2) {ADD(reg);}    /*printf("reg=%s\n",reg);*/                                                 \
                                if (mode & 1) {ADD(number);} /*printf("number=%d\n",number);*/                                                 \
                                ADD("]");                                                     \
                            } else {                                                          \
                                if (mode & 2) {ADD(reg);}    /*printf("reg=%s\n",reg);*/                                                 \
                                if (mode & 1) {ADD(number);} /*printf("number=%d\n",number);*/                                                 \
                            }                                                                 \
                                                                                              \
                        }                                                                     \
                        if (num >= 20 && num <= 27) {                                                        \
                            for(int i = 0; i < 5; i++){printf("BinaryCode[ofs+%d]=%d\n",i,BinaryCode[ofs+i]);};                                    \
                            ADD(" ");                                                                         \
                            ofs+=1;                                                     \
                            ADD(intToString(BinaryCode[ofs])); printf("jump: BinaryCode[ofs]=%d\n",BinaryCode[ofs]);                              \
                        }                                                                     \
                        ADD("\n");                                                            \
                        break;                                                                \
                    }

        /*
        printf("BinaryCode[%d] = %d\n",ofs, BinaryCode[ofs]);
        #define DEF_CMD(name, num, argum, code)               \
                    case num:                                     \
                    {                                              \
                        ADD(#name);                              \
                        if (num == 32 || num == 64) {            \
                            ADD(" ")\
                            int mode = BinaryCode[++ofs];                                                             \
                            FunctionalString* toInsert = createFunctionalString(0);                                     \
                            if (mode & 2) {                                                                           \
                                char reg[3];                                         \
                                reg[0] = 'r';                                        \
                                reg[1] = 'a'+ BinaryCode[++ofs];                      \
                                reg[2] = 'x';                                        \
                                toInsert = mergeFunctionalStrings (toInsert, convertToFunctionalString (reg));   \
                                printf("After adding register: toInsert=%s\n",toInsert); \
                            }                                                                                         \
                            if (mode & 1) {                                                                           \
                                char* number = intToString(BinaryCode[++ofs]);                          \
                                toInsert = mergeFunctionalStrings (toInsert, convertToFunctionalString ("+"));        \
                                toInsert = mergeFunctionalStrings (toInsert, convertToFunctionalString (number));     \
                                printf("After adding constant: number=%s toInsert=%s\n",number, toInsert);                                 \
                            }                                                                                         \
                            if (mode & 4) {                                                                           \
                                toInsert = mergeFunctionalStrings (toInsert, convertToFunctionalString ("]"));        \
                                toInsert = mergeFunctionalStrings (convertToFunctionalString ("["), toInsert);        \
                                printf("After adding RAM: toInsert=%s\n",toInsert);   \
                            }                                                      \
                            ADD(toInsert->str);                           \
                               \
                        }                                         \
                        if (num >= 20 && num <= 27) {             \
                            ADD(" ")                              \
                            ADD(intToString(BinaryCode[++ofs]));                     \
                        }                                         \
                        ADD("\n")                                 \
                        break;                                    \
                    }
            */

        switch (BinaryCode[ofs]) {

            #include "commands.h"

            default:
            {
                printf("UNKNOWN COMMAND!!! BinaryCode[%d]=%d\n", ofs, BinaryCode[ofs]);
                ADD("Unknown command");
                break;
            }
        }

        #undef DEF_CMD


        if (BinaryCode[ofs] == 127) {break;}
        ofs++;
    }

    /*
    printf("LAST: BinaryCode[%d] = %d\n",ofs, BinaryCode[ofs]);
    */
    for (int i = 0; i < 300; i++) {
        printf("text[%d]=%c (%d)",i, text[i],text[i]);
        if(text[i]==127){printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");}
        printf("\n");
    }


    return text;
};

char* intToString (int number) {

    char* result = (char*) calloc (sizeof(char), numberOfNumerals (number));

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
