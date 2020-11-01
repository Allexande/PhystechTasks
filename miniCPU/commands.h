//version 0.1.2

//Command (name, code, parameters, call)

DEF_CMD (hlt, 0, 0, {
    deleteCPU(cpu);
    printf("The programm ended.\n");
} )

// ---

DEF_CMD (in, 1, 0, {
    double elem = 0;
	scanf("%lf", &elem);
    stackPush(cpu->computeStack, elem);
} )

DEF_CMD (out, 2, 0, {
    printf("CPU OUT >> %lf\n", stackTop(cpu->computeStack));
} )

// ---

DEF_CMD (push, 32, 1, {
    cpu->ofs += sizeof(char);
    char type = cpu->code[cpu->ofs];
    cpu->ofs += sizeof(char);

    if (type & 4) {
        //RAM
        int buff = 0;

        if (type & 2) {
            buff += (int) cpu->registers[cpu->code[cpu->ofs]];
            cpu->ofs += sizeof(char);
        }

        if (type & 1) {
            buff += (int) cpu->code[cpu->ofs];
            cpu->ofs += sizeof(int);
        }

        cpu->RAM[buff] = stackTop(cpu->computeStack);

    } else {
        //NOT RAM
        if (type & 1) {
            double buff = 0;

            if (type & 2) {
                buff += (int) cpu->registers[cpu->code[cpu->ofs]];
                cpu->ofs += sizeof(char);
            }

            buff += cpu->code[cpu->ofs];
            cpu->ofs += sizeof(double);

            stackPush (cpu->computeStack, buff);

        } else {
            int buff = 0;

            buff += (int) cpu->code[cpu->ofs];
            cpu->ofs += sizeof(int);

            cpu->registers [buff] = stackTop(cpu->computeStack);
        }
    }
    cpu->ofs += sizeof(char);
} )

DEF_CMD (pop, 64, 1, {
    cpu->ofs += sizeof(char);
    char type = cpu->code[cpu->ofs];
    cpu->ofs += sizeof(char);

    if (type & 4) {
        //RAM
        int buff = 0;

        if (type & 2) {
            buff += (int) cpu->registers[cpu->code[cpu->ofs]];
            cpu->ofs += sizeof(char);
        }

        if (type & 1) {
            buff += (int) cpu->code[cpu->ofs];
            cpu->ofs += sizeof(int);
        }

        stackPush (cpu->computeStack, cpu->RAM[buff]);

    } else {
        //NOT RAM
        if (type & 2) {
            int buff = 0;
            buff = (int) cpu->code[cpu->ofs];
            cpu->ofs += sizeof(int);

            stackPush (cpu->computeStack, cpu->registers[buff]);

        } else {
            stackPop (cpu->computeStack);
        }
    }
} )

// ---

DEF_CMD (add,  10, 0, {
    double first  = stackPop(cpu->computeStack);
    double second = stackPop(cpu->computeStack);
    stackPush(cpu->computeStack, first + second);
} )

DEF_CMD (sub,  11, 0, {
    double first  = stackPop(cpu->computeStack);
    double second = stackPop(cpu->computeStack);
    stackPush(cpu->computeStack, first - second);
} )

DEF_CMD (mul,  12, 0, {
    double first  = stackPop(cpu->computeStack);
    double second = stackPop(cpu->computeStack);
    stackPush(cpu->computeStack, first * second);
} )

DEF_CMD (div,  13, 0, {
    double first  = stackPop(cpu->computeStack);
    double second = stackPop(cpu->computeStack);
    stackPush(cpu->computeStack, first / second);
} )

DEF_CMD (sqrt, 14, 0, {
    double first  = stackPop(cpu->computeStack);
    stackPush(cpu->computeStack, sqrt (first));
} )

DEF_CMD (sin,  15, 0, {
    double first  = stackPop(cpu->computeStack);
    stackPush(cpu->computeStack, sin (first));
} )

DEF_CMD (cos,  16, 0, {
    double first  = stackPop(cpu->computeStack);
    stackPush(cpu->computeStack, cos (first));
} )

// ---

//TODO Надо ли всем jump прибавлять +3 (смещение на header)?
#define MOVE_ADRESS_BECAUSE_OF_HEADER cpu->ofs += 3;

DEF_CMD (jmp, 20, 2, {
    int argument = *(int*)(cpu->code + cpu->ofs + 1);
    cpu->ofs = argument;
    MOVE_ADRESS_BECAUSE_OF_HEADER
} )

DEF_CMD (ja, 21, 2, {
    double first  = stackPop(cpu->computeStack);
    double second = stackPop(cpu->computeStack);
    if (second > first) {
        int argument = *(int*)(cpu->code + cpu->ofs + 1);
        cpu->ofs = argument;
        MOVE_ADRESS_BECAUSE_OF_HEADER
    }
} )

DEF_CMD (jae, 22, 2, {
    double first  = stackPop(cpu->computeStack);
    double second = stackPop(cpu->computeStack);
    if (second >= first) {
        int argument = *(int*)(cpu->code + cpu->ofs + 1);
        cpu->ofs = argument;
        MOVE_ADRESS_BECAUSE_OF_HEADER
    }
} )

DEF_CMD (jb, 23, 2, {
    double first  = stackPop(cpu->computeStack);
    double second = stackPop(cpu->computeStack);
    if (second < first) {
        int argument = *(int*)(cpu->code + cpu->ofs + 1);
        cpu->ofs = argument;
        MOVE_ADRESS_BECAUSE_OF_HEADER
    }
} )

DEF_CMD (jbe, 24, 2, {
    double first  = stackPop(cpu->computeStack);
    double second = stackPop(cpu->computeStack);
    if (second <= first) {
        int argument = *(int*)(cpu->code + cpu->ofs + 1);
        cpu->ofs = argument;
        MOVE_ADRESS_BECAUSE_OF_HEADER
    }
} )

DEF_CMD (je, 25, 2, {
    double first  = stackPop(cpu->computeStack);
    double second = stackPop(cpu->computeStack);
    if (second == first) {
        int argument = *(int*)(cpu->code + cpu->ofs + 1);
        cpu->ofs = argument;
        MOVE_ADRESS_BECAUSE_OF_HEADER
    }
} )

DEF_CMD (jne, 26, 2, {
    double first  = stackPop(cpu->computeStack);
    double second = stackPop(cpu->computeStack);
    if (second != first) {
        int argument = *(int*)(cpu->code + cpu->ofs + 1);
        cpu->ofs = argument;
        MOVE_ADRESS_BECAUSE_OF_HEADER
    }
} )

DEF_CMD (jt, 27, 2, {
    time_t t = time(NULL);
    struct tm* timeInfo = localtime(&t);
    if (timeInfo->tm_wday == 2) {
        int argument = *(int*)(cpu->code + cpu->ofs + 1);
        cpu->ofs = argument;
        MOVE_ADRESS_BECAUSE_OF_HEADER
    }
} ) //Joke

// ---

DEF_CMD (call, 30, 2, {
    stackPush(cpu->callings, cpu->ofs + sizeof(double));
	int argument = *(int*)(cpu->code + cpu->ofs + 1);
    cpu->ofs = argument;
    MOVE_ADRESS_BECAUSE_OF_HEADER
} )

DEF_CMD (ret, 31, 0, {
    cpu->ofs = stackPop(cpu->callings);
} )
