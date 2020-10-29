struct CPU {
    Stack_t* computeStack;
    double*  program;
    int      pc;
    //double*  registers;
    //double r
}

bool executeProgram (stack_t* programStack);
