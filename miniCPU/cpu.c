//version 1.0.1

#include "enum.h"
#include "filemaster.c"
#include "stack.c"
#include "string.c"
#include "cpu.h"

//#define DEBUG_CPU

#define DEFAILT_READING_FILE_NAME "prog_sqr.asm"

int main (const int argc, const char* argv[]) {

    const char* inputFile = DEFAILT_READING_FILE_NAME;

    if (argc > 1) {

        for (int i = 1; i < argc; i++) {

            if (strcmp(argv[i], "-i") == 0  || strcmp(argv[i], "--input")   == 0) {
                inputFile = argv[i];
            }

        }

    }

    FILE* input = fopen(inputFile, "rb");

    if (input == NULL) {
        return -1;

    }

    CPU* cpu = (CPU*) calloc (sizeof(CPU), 1);

    assert(cpu);

    ConstructCPU (cpu, input);

    fclose(input);

    process (cpu);

    return 1;
}

bool CheckVersion (CPU* cpu) {

    return (cpu->code[0] == cpu->vers[0] &&
            cpu->code[1] == cpu->vers[1] &&
            cpu->code[2] == cpu->vers[2]);

}

void ConstructCPU (CPU* cpu, FILE* file ) {

    cpu->vers = "TA1";

    cpu->computeStack = newStack (startComputeStackSize);
    cpu->callings =     newStack (startCallingStackSize);

    cpu->code = (char*) calloc (limitSizeOfCode, sizeof(char));
    assert(cpu->code);

    cpu->totalSize = fread (cpu->code, sizeof(char), limitSizeOfCode, file);

    cpu->registers = (double*) calloc (numberOfRegisters, sizeof(double));
    assert(cpu->registers);

    cpu->RAM = (double*) calloc (sizeOfRAM, sizeof(double));
    assert(cpu->RAM);

    if (!CheckVersion (cpu)) {
        printf("The version of file is wrong!\n");
        assert(!"OK");
    }

    //Move at size of header
    cpu->ofs = 3;
}

void deleteCPU (CPU* cpu) {

    free(cpu->code);
    free(cpu->registers);
    free(cpu->RAM);

    stackDelete (cpu->computeStack);
    stackDelete (cpu->callings);
}

void execute (CPU* cpu) {

    int command = cpu->code[cpu->ofs];

    #ifdef DEBUG_CPU
        printf("\n");
        for (size_t k = 0; k < cpu->totalSize; k++) {
            if (k == cpu->ofs) {
                printf(">%x< ", cpu->code[k]);
            } else {
                printf("%x ", cpu->code[k]);
            }
        }
        printf("\n\n");
    #endif

    #ifdef DEBUG_CPU
        printf("execute: Current command cpu->code[%d]=%d\n", cpu->ofs, command);
    #endif

    #define DEF_CMD(name, num, arg, code) \
        case num :                        \
        {                                 \
            code                          \
            break;                        \
        }

    switch (command) {
        #include "commands.h"

        default :
        {
            #ifdef DEBUG_CPU
                printf("THIS COMMAND DOES NOT EXIST: code[%d] = %d\n", cpu->ofs, cpu->code[cpu->ofs]);
            #endif
        }
    }
    #undef DEF_CMD

    cpu->ofs += sizeof(char);
}

void process (CPU* cpu) {

    while (cpu->ofs < cpu->totalSize && cpu->code[cpu->ofs] != 127) {
        execute(cpu);
    }

}
