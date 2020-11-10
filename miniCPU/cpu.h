//version 0.1.3
#define RAM_SIZE 10000

struct CPU {
    char* vers;
    stack_t* computeStack;
    stack_t* callings;
    char* code;
    double* registers;
    double* RAM;
    size_t totalSize;
    size_t ofs;
};

//TODO
//¬озможно нужно заменить на подсчитываемые
//enum Consts {
//
//}

bool CheckVersion    (CPU* cpu);

void ConstructCPU    (CPU* cpu, FILE* input);

void deleteCPU      (CPU* cpu);

void execute         (CPU* cpu);

void process         (CPU* cpu);
