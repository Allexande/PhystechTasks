//version 0.2.0

struct CPU {

    char* vers;

    stack_t* computeStack;

    stack_t* callings;

    char*   code;

    double* registers;
    double* RAM;

    size_t totalSize;

    size_t ofs;

};

enum CPUfeatures {
    startComputeStackSize = 100,
    startCallingStackSize = 100,
    limitSizeOfCode       = 1000,
    numberOfRegisters     = 26,
    sizeOfRAM             = 10000,
};

bool CheckVersion (CPU* cpu);

void ConstructCPU (CPU* cpu, FILE* input);

void deleteCPU    (CPU* cpu);

void execute      (CPU* cpu);

void process      (CPU* cpu);
