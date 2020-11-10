//version 0.1.3
#include "enum.h"
#include "filemaster.c"
#include "stack.c"
#include "string.c"
#include "cpu.h"

//#define DIRECTORY "programs/"

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
    //TODO делать с нормальными размерами!!!
    cpu->computeStack = newStack (10);
    cpu->callings = newStack (1000);
    cpu->code = (char*) calloc (1000, sizeof(char));
    cpu->totalSize = fread (cpu->code, sizeof(char), 1000, file);
    cpu->registers = (double*) calloc (20, sizeof(double));
    cpu->RAM = (double*) calloc (RAM_SIZE, sizeof(double));

    CheckVersion (cpu);
    cpu->ofs = 3; //Сдвиг на версию (header)
}

void deleteCPU (CPU* cpu) {
    cpu->vers = nullptr;

    //TODO убить стак
    //Destroy(&cpu->computeStack);

    free(cpu->code);
}

void execute (CPU* cpu) {
    int command = cpu->code[cpu->ofs];

    printf("cpu->ofs=%d cpu->code[cpu->ofs]=%x command=%d\n\n", cpu->ofs, cpu->code[cpu->ofs], command);



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

    printf("\n");
    /*if (cpu->computeStack->length > 0) {
    printf("TOP IS %lf\n", stackTop(cpu->computeStack));
    }
    stackDump (cpu->computeStack);*/
}

void process (CPU* cpu)
{
    while (cpu->ofs <= cpu->totalSize) {
        execute(cpu);
    }
}


/*
bool executeProgram (stack_t* programStack) {
    stack_t* computeStack = newStack (4);
    int currentCommand;

    while (true) {
        currentCommand = (int) stackPop (programStack);

        switch(currentCommand) {
            case 0:
            {
                return true;
            }
            case 1:
            {
                stackDump (computeStack);
                double input;
                scanf("%lf", &input);
                stackPush (computeStack, input);
                stackDump (computeStack);
                break;
            }
            case 2:
            {
                double forOutput = stackTop (computeStack);
                break;
            }
            case 3:
            {
                double toPush = stackPop (programStack);
                stackPush (computeStack, toPush);
                break;
            }
            case 4:
            {
                stackPop (computeStack);
                break;
            }
            case 5:
            {
                double first  = stackPop (computeStack);
                double second = stackPop (computeStack);
                stackPush (computeStack, first + second);
                break;
            }
            case 6:
            {
                double first  = stackPop (computeStack);
                double second = stackPop (computeStack);
                stackPush (computeStack, first - second);
                break;
            }
            case 7:
            {
                double first  = stackPop (computeStack);
                double second = stackPop (computeStack);
                stackPush (computeStack, first * second);
                break;
            }
            case 8:
            {
                double first  = stackPop (computeStack);
                double second = stackPop (computeStack);
                stackPush (computeStack, first / second);
                break;
            }
            case 9:
            {
                double first  = stackPop (computeStack);
                double second = stackPop (computeStack);
                stackPush (computeStack, pow (first, 1/second));
                break;
            }
            case 10:
            {
                double first  = stackPop (computeStack);
                double second = stackPop (computeStack);
                stackPush (computeStack, pow (first, second));
                break;
            }
            case 11:
            {
                double first  = stackPop (computeStack);
                stackPush (computeStack, sin (first));
                break;
            }
            case 12:
            {
                double first  = stackPop (computeStack);
                stackPush (computeStack, cos (first));
                break;
            }
        }
    }
}; */
