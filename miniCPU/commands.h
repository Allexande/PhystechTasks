//version 1.0.1

//#define DEBUG_COMMANDS

//Command (name, code, parameters, call)

#define GET_first_second                          \
    double first  = stackPop(cpu->computeStack);  \
    double second = stackPop(cpu->computeStack);

#define GET_first                                 \
    double first  = stackPop(cpu->computeStack);

#define WRITE_argument_TO_ofs                     \
    cpu->ofs = (int)(cpu->code[++cpu->ofs]) - 1;

#define M_CONST    type & 1

#define M_REGISTER type & 2

#define M_RAM      type & 4

DEF_CMD (hlt, 127, 0, {

    #ifdef DEBUG_COMMANDS
        printf("hlt: The programm ended.\n");
        #else
        //Abort of program
        printf("CPU COMPLITED PROCESS\n");
    #endif

    deleteCPU(cpu);

} )

// ---

DEF_CMD (in, 1, 0, {

    double elem = 0;

    //Is it really necessary to use printf there?...
    printf("Input:\n");

	scanf("%lf", &elem);
    stackPush (cpu->computeStack, elem);

    #ifdef DEBUG_COMMANDS
        printf("in: %lf was added in computeStack\n", elem);
    #endif

} )

DEF_CMD (out, 2, 0, {
    printf("CPU OUT > %lf\n", stackTop(cpu->computeStack));
} )

// ---

DEF_CMD (push, 32, 1, {

    cpu->ofs += sizeof(char);
    char type = cpu->code[cpu->ofs];
    cpu->ofs += sizeof(char);

    #ifdef DEBUG_COMMANDS
        printf("push: type = %d\n", type);
        printf("push: this push contains const    = %d\n", type & 1);
        printf("push: this push contains register = %d\n", type & 2);
        printf("push: this push contains RAM      = %d\n", type & 4);
    #endif

    if (M_RAM) {

        //RAM
        int buff = 0;

        if (M_REGISTER) {
            buff += (int) cpu->registers[cpu->code[cpu->ofs]];

            #ifdef DEBUG_COMMANDS
                printf("push: This push contains RAM and register, so after adding [%d] register buff = %d\n", cpu->code[cpu->ofs], buff);
            #endif

        }

        if (M_CONST) {
            buff += (int) cpu->code[cpu->ofs];

            #ifdef DEBUG_COMMANDS
                printf("push: This push contains const and register, so after adding %d const buff = %d\n", cpu->code[cpu->ofs], buff);
            #endif

        }

        cpu->RAM[buff] = stackTop(cpu->computeStack);

    } else {

        if (M_CONST) {

            double buff = 0;

            if (M_REGISTER) {
                buff += (int) cpu->registers[cpu->code[cpu->ofs]];

                #ifdef DEBUG_COMMANDS
                    printf("push: This push doesn't contain const but contains const and register, so after adding [%d] register buff = %lf\n", cpu->code[cpu->ofs], buff);
                #endif

            }

            buff += cpu->code[cpu->ofs];

            #ifdef DEBUG_COMMANDS
                printf("push: This push doesn't contain RAM but contains const and register, so after adding %d const buff = %lf\n", cpu->code[cpu->ofs], buff);
            #endif

            stackPush (cpu->computeStack, buff);

        } else {

            int buff = 0;

            buff += (int) cpu->code[cpu->ofs];

            #ifdef DEBUG_COMMANDS
                printf("push: This push doesn't contain RAM but contains register, so after adding %d const buff = %d\n", cpu->code[cpu->ofs], buff);
            #endif

            cpu->registers[buff] = stackTop(cpu->computeStack);


        }
    }
} )

//TODO add debug blocks if they will be needed
DEF_CMD (pop, 64, 1, {

    cpu->ofs += sizeof(char);
    char type = cpu->code[cpu->ofs];
    cpu->ofs += sizeof(char);

    if (M_RAM) {
        //RAM
        int buff = 0;

        if (M_REGISTER) {
            buff += (int) cpu->registers[cpu->code[cpu->ofs]];

        }

        if (M_CONST) {
            buff += (int) cpu->code[cpu->ofs];

        }

        stackPush (cpu->computeStack, cpu->RAM[buff]);

    } else {
        //NOT RAM
        if (M_REGISTER) {

            int buff = 0;
            buff = (int) cpu->code[cpu->ofs];

            stackPush (cpu->computeStack, cpu->registers[buff]);

        } else {
            stackPop (cpu->computeStack);
        }
    }
} )

// ---

DEF_CMD (add,  10, 0, {

    GET_first_second
    stackPush(cpu->computeStack, first + second);

    #ifdef DEBUG_COMMANDS
        printf("add: first=%lf second=%lf; first+second=%lf added in stack\n", first, second, first+second);
    #endif

} )

DEF_CMD (sub,  11, 0, {

    GET_first_second
    stackPush(cpu->computeStack, first - second);

    #ifdef DEBUG_COMMANDS
        printf("sub: first=%lf second=%lf; first-second=%lf added in stack\n", first, second, first-second);
    #endif

} )

DEF_CMD (mul,  12, 0, {

    GET_first_second
    stackPush(cpu->computeStack, first * second);

    #ifdef DEBUG_COMMANDS
        printf("mul: first=%lf second=%lf; first * second=%lf added in stack\n", first, second, first * second);
    #endif

} )

DEF_CMD (div,  13, 0, {

    GET_first_second
    stackPush(cpu->computeStack, first / second);

    #ifdef DEBUG_COMMANDS
        printf("div: first=%lf second=%lf; first / second=%lf added in stack\n", first, second, first / second);
    #endif

} )

DEF_CMD (sqrt, 14, 0, {

    GET_first
    stackPush(cpu->computeStack, sqrt (first));

    #ifdef DEBUG_COMMANDS
        printf("sqrt: first=%lf; sqrt (first)=%lf added in stack\n", first, sqrt (first));
    #endif

} )

DEF_CMD (sin,  15, 0, {

    GET_first
    stackPush(cpu->computeStack, sin (first));

    #ifdef DEBUG_COMMANDS
        printf("sin: first=%lf; sin (first)=%lf added in stack\n", first, sin (first));
    #endif

} )

DEF_CMD (cos,  16, 0, {

    GET_first
    stackPush(cpu->computeStack, cos (first));

    #ifdef DEBUG_COMMANDS
        printf("cos: first=%lf; sin (first)=%lf added in stack\n", first, cos (first));
    #endif

} )

// ---

#define MOVE_ADRESS_BECAUSE_OF_HEADER cpu->ofs += 3;

DEF_CMD (jmp, 20, 2, {

    cpu->ofs += sizeof(char);

    WRITE_argument_TO_ofs

    MOVE_ADRESS_BECAUSE_OF_HEADER

    #ifdef DEBUG_COMMANDS
        printf("jmp: was jump to %d\n", cpu->ofs);
    #endif

} )

DEF_CMD (ja, 21, 2, {

    GET_first_second

    #ifdef DEBUG_COMMANDS
        printf("ja: first = %lf second = %lf", first, second);
        if (second > first) {
            printf("second > first = %d and because of this was jump to %d\n", second > first, (int)(cpu->code[++cpu->ofs]));
        } else {
            printf("second > first = %d and because of this there WAS NOT jump to %d\n", second > first, (int)(cpu->code[++cpu->ofs]));
        }
    #endif

    if (second > first) {

        WRITE_argument_TO_ofs

        MOVE_ADRESS_BECAUSE_OF_HEADER
    } else {
        cpu->ofs++;
    }
} )

DEF_CMD (jae, 22, 2, {

    GET_first_second

    #ifdef DEBUG_COMMANDS
        printf("jae: first = %lf second = %lf", first, second);
        if (second >= first) {
            printf("second >= first = %d and because of this was jump to %d\n", second >= first, (int)(cpu->code[++cpu->ofs]));
        } else {
            printf("second >= first = %d and because of this there WAS NOT jump to %d\n", second >= first, (int)(cpu->code[++cpu->ofs]));
        }
    #endif

    if (second >= first) {

        WRITE_argument_TO_ofs

        MOVE_ADRESS_BECAUSE_OF_HEADER
    } else {
        cpu->ofs++;
    }
} )

DEF_CMD (jb, 23, 2, {

    GET_first_second

    #ifdef DEBUG_COMMANDS
        printf("jb: first = %lf second = %lf", first, second);
        if (second < first) {
            printf("second < first = %d and because of this was jump to %d\n", second < first, (int)(cpu->code[++cpu->ofs]));
            cpu->ofs--;
        } else {
            printf("second < first = %d and because of this there WAS NOT jump to %d\n", second < first, (int)(cpu->code[++cpu->ofs]));
            cpu->ofs--;
        }
    #endif

    if (second < first) {

        WRITE_argument_TO_ofs

        MOVE_ADRESS_BECAUSE_OF_HEADER

        printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> now cpu->ofs=%d\n",cpu->ofs);

    } else {
        cpu->ofs++;
    }
} )

DEF_CMD (jbe, 24, 2, {

    GET_first_second

    #ifdef DEBUG_COMMANDS
        printf("jbe: first = %lf second = %lf", first, second);
        if (second <= first) {
            printf("second <= first = %d and because of this was jump to %d\n", second <= first, (int)(cpu->code[++cpu->ofs]));
        } else {
            printf("second <= first = %d and because of this there WAS NOT jump to %d\n", second <= first, (int)(cpu->code[++cpu->ofs]));
        }
    #endif

    if (second <= first) {

        WRITE_argument_TO_ofs

        MOVE_ADRESS_BECAUSE_OF_HEADER

    } else {
        cpu->ofs++;
    }
} )

DEF_CMD (je, 25, 2, {

    GET_first_second

    #ifdef DEBUG_COMMANDS
        printf("je: first = %lf second = %lf", first, second);
        if (second == first) {
            printf("second == first = %d and because of this was jump to %d\n", second == first, (int)(cpu->code[++cpu->ofs]));
        } else {
            printf("second == first = %d and because of this there WAS NOT jump to %d\n", second == first, (int)(cpu->code[++cpu->ofs]));
        }
    #endif

    if (second == first) {

        WRITE_argument_TO_ofs

        MOVE_ADRESS_BECAUSE_OF_HEADER

    } else {
        cpu->ofs++;
    }
} )

DEF_CMD (jne, 26, 2, {

    GET_first_second

    #ifdef DEBUG_COMMANDS
        printf("jne: first = %lf second = %lf", first, second);
        if (second != first) {
            printf("second != first = %d and because of this was jump to %d\n", second != first, (int)(cpu->code[++cpu->ofs]));
        } else {
            printf("second != first = %d and because of this there WAS NOT jump to %d\n", second != first, (int)(cpu->code[++cpu->ofs]));
        }
    #endif

    if (second != first) {

        WRITE_argument_TO_ofs

        MOVE_ADRESS_BECAUSE_OF_HEADER

    } else {
        cpu->ofs++;
    }
} )

//Joke
DEF_CMD (jt, 27, 2, {
    time_t t = time(NULL);
    struct tm* timeInfo = localtime(&t);

    #ifdef DEBUG_COMMANDS
        printf("jt: timeInfo->tm_wday = %d", timeInfo->tm_wday);
        if (timeInfo->tm_wday == 2) {
            printf("timeInfo->tm_wday == 2 = %d and because of this was jump to %d\n", timeInfo->tm_wday == 2, (int)(cpu->code[++cpu->ofs]));
        } else {
            printf("timeInfo->tm_wday == 2 = %d and because of this there WAS NOT jump to %d\n", timeInfo->tm_wday == 2, (int)(cpu->code[++cpu->ofs]));
        }
    #endif

    if (timeInfo->tm_wday == 2) {

        WRITE_argument_TO_ofs

        MOVE_ADRESS_BECAUSE_OF_HEADER

    } else {
        cpu->ofs++;
    }
} )

// ---

DEF_CMD (draw, 50, 2, {

    size_t lengthToShow = cpu->code[++cpu->ofs];

    #ifdef DEBUG_COMMANDS
        printf("draw: Will be painted %d symbols\n", lengthToShow);
    #endif

    for (size_t i = beginingOfVideoRAM; i < beginingOfVideoRAM + lengthToShow; i++) {
        printf("%c", (char)cpu->RAM[i]);
    }

} )

// ---

DEF_CMD (call, 30, 2, {

    stackPush(cpu->callings, cpu->ofs + sizeof(char));

    WRITE_argument_TO_ofs

    cpu->ofs--;

    MOVE_ADRESS_BECAUSE_OF_HEADER

    #ifdef DEBUG_COMMANDS
        printf("call: was jump to %d\n", cpu->ofs);
    #endif

} )

DEF_CMD (ret, 31, 0, {
    cpu->ofs = stackPop(cpu->callings);

    #ifdef DEBUG_COMMANDS
        printf("ret: was jump (return) to %d\n", cpu->ofs);
    #endif
} )

#ifdef DEBUG_COMMANDS
#undef DEF_CMD
#endif
