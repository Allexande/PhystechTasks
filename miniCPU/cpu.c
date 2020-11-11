//version 0.2.0
#include "enum.h"
#include "filemaster.c"
#include "stack.c"
#include "string.c"
#include "cpu.h"

#define DEFAILT_READING_FILE_NAME "out.asm"

int main (const int argc, const char* argv[]) {

    const char* inputFile;

    if (argc > 1) {

        for (int i = 1; i < argc; i++) {

            if (strcmp(argv[i], "-i") == 0  || strcmp(argv[i], "--input")   == 0) {
                inputFile = argv[i];
            }

        }

    } else {
        inputFile = DEFAILT_READING_FILE_NAME;
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

    return 0;
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

    cpu->vers = nullptr;

    free(cpu->code);      cpu->code      = nullptr;
    free(cpu->registers); cpu->registers = nullptr;
    free(cpu->RAM);       cpu->RAM       = nullptr;

    stackDelete (cpu->computeStack);
    stackDelete (cpu->callings);
}

void execute (CPU* cpu) {

    int command = cpu->code[cpu->ofs];

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
            printf("THIS COMMAND DOES NOT EXIST: code[%d] = %d\n", cpu->ofs, cpu->code[cpu->ofs]);
        }
    }
    cpu->ofs += sizeof(char);

    #undef DEF_CMD
}

void process (CPU* cpu)
{
    while (cpu->ofs < cpu->totalSize) {
        execute(cpu);
    }
}
