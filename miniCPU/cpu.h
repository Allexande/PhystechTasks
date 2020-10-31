struct CPU {
    Stack_t* computeStack;
    double*  program;
    int      pc;
    double*  registers[26];
}

/*
bool executeProgram (stack_t* programStack);
*/
