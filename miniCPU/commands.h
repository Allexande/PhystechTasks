//version 0.1.3

//#define DEBUG

//Command (name, code, parameters, call)

DEF_CMD (hlt, 127, 0, {
    deleteCPU(cpu);
    #ifdef DEBUG
        printf("hlt: The programm ended.\n");
        #else
        exit(0);
    #endif
} )

// ---

DEF_CMD (in, 1, 0, {
    double elem = 0;
	scanf("%lf", &elem);
    stackPush (cpu->computeStack, elem);
    #ifdef DEBUG
        printf("in: %lf was added in computeStack\n", elem);
    #endif
} )

DEF_CMD (out, 2, 0, {
    printf("CPU OUT >>>>>>>>>>>>>>>>>>>>>>>>>>>>> %lf\n", stackTop(cpu->computeStack));
} )

// ---

DEF_CMD (push, 32, 1, {

    cpu->ofs += sizeof(char);
    char type = cpu->code[cpu->ofs];
    cpu->ofs += sizeof(char);

    #ifdef DEBUG
        printf("push: type = %d\n", type);
        printf("push: this push contains const    = %d\n", type & 1);
        printf("push: this push contains register = %d\n", type & 2);
        printf("push: this push contains RAM      = %d\n", type & 4);
    #endif

    if (type & 4) {

        //RAM
        int buff = 0;

        if (type & 2) {
            buff += (int) cpu->registers[cpu->code[cpu->ofs]];
            #ifdef DEBUG
                printf("push: This push contains RAM and register, so after adding [%d] register buff = %d\n", cpu->code[cpu->ofs], buff);
            #endif
            //cpu->ofs += sizeof(char);
        }

        if (type & 1) {
            buff += (int) cpu->code[cpu->ofs];
            #ifdef DEBUG
                printf("push: This push contains const and register, so after adding %d const buff = %d\n", cpu->code[cpu->ofs], buff);
            #endif
            //cpu->ofs += sizeof(char);
        }

        cpu->RAM[buff] = stackTop(cpu->computeStack);

    } else {
        //NOT RAM
        //printf("THERE2\n");

        if (type & 1) {

            double buff = 0;
            //cpu->ofs += sizeof(char);

            if (type & 2) {
                buff += (int) cpu->registers[cpu->code[cpu->ofs]];
                #ifdef DEBUG
                    printf("push: This push doesn't contain const but contains const and register, so after adding [%d] register buff = %lf\n", cpu->code[cpu->ofs], buff);
                #endif
                //cpu->ofs += sizeof(char);
            }

            buff += cpu->code[cpu->ofs];
            #ifdef DEBUG
                printf("push: This push doesn't contain RAM but contains const and register, so after adding %d const buff = %lf\n", cpu->code[cpu->ofs], buff);
            #endif
            //cpu->ofs += sizeof(char);

            printf("PUSHED buff=%lf\n", buff);

            stackPush (cpu->computeStack, buff);

        } else {
            //printf("THERE3\n");

            int buff = 0;

            buff += (int) cpu->code[cpu->ofs];
            #ifdef DEBUG
                printf("push: This push doesn't contain RAM but contains register, so after adding %d const buff = %d\n", cpu->code[cpu->ofs], buff);
            #endif
            //cpu->ofs += sizeof(int);

            //printf("buff=%d cpu->computeStack.length=%d stackTop(cpu->computeStack)=%d\n",buff, cpu->computeStack->length, stackTop(cpu->computeStack));

            cpu->registers[buff] = stackTop(cpu->computeStack);

            //printf("OK\n");
        }
    }
    //cpu->ofs += sizeof(char);
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
            //cpu->ofs += sizeof(char);
        }

        if (type & 1) {
            buff += (int) cpu->code[cpu->ofs];
            //cpu->ofs += sizeof(char);
        }

        stackPush (cpu->computeStack, cpu->RAM[buff]);

    } else {
        //NOT RAM
        if (type & 2) {
            int buff = 0;
            buff = (int) cpu->code[cpu->ofs];
            //cpu->ofs += sizeof(int);

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
    #ifdef DEBUG
        printf("add: first=%lf second=%lf; first+second=%lf added in stack\n", first, second, first+second);
    #endif
} )

DEF_CMD (sub,  11, 0, {
    double first  = stackPop(cpu->computeStack);
    double second = stackPop(cpu->computeStack);
    stackPush(cpu->computeStack, first - second);
    #ifdef DEBUG
        printf("sub: first=%lf second=%lf; first-second=%lf added in stack\n", first, second, first-second);
    #endif
} )

DEF_CMD (mul,  12, 0, {
    double first  = stackPop(cpu->computeStack);
    double second = stackPop(cpu->computeStack);
    stackPush(cpu->computeStack, first * second);
    #ifdef DEBUG
        printf("mul: first=%lf second=%lf; first * second=%lf added in stack\n", first, second, first * second);
    #endif
} )

DEF_CMD (div,  13, 0, {
    double first  = stackPop(cpu->computeStack);
    double second = stackPop(cpu->computeStack);
    stackPush(cpu->computeStack, first / second);
    #ifdef DEBUG
        printf("div: first=%lf second=%lf; first / second=%lf added in stack\n", first, second, first / second);
    #endif
} )

DEF_CMD (sqrt, 14, 0, {
    double first  = stackPop(cpu->computeStack);
    stackPush(cpu->computeStack, sqrt (first));
    #ifdef DEBUG
        printf("sqrt: first=%lf; sqrt (first)=%lf added in stack\n", first, sqrt (first));
    #endif
} )

DEF_CMD (sin,  15, 0, {
    double first  = stackPop(cpu->computeStack);
    stackPush(cpu->computeStack, sin (first));
    #ifdef DEBUG
        printf("sin: first=%lf; sin (first)=%lf added in stack\n", first, sin (first));
    #endif
} )

DEF_CMD (cos,  16, 0, {
    double first  = stackPop(cpu->computeStack);
    stackPush(cpu->computeStack, cos (first));
    #ifdef DEBUG
        printf("cos: first=%lf; sin (first)=%lf added in stack\n", first, cos (first));
    #endif
} )

// ---

//TODO Íàäî ëè âñåì jump ïðèáàâëÿòü +3 (ñìåùåíèå íà header)?
#define MOVE_ADRESS_BECAUSE_OF_HEADER cpu->ofs += 3;

DEF_CMD (jmp, 20, 2, {
    cpu->ofs += sizeof(char);
    int argument = (int)(cpu->code[++cpu->ofs]);
    cpu->ofs = argument;
    cpu->ofs--;
    MOVE_ADRESS_BECAUSE_OF_HEADER
    #ifdef DEBUG
        printf("jmp: was jump to %d\n", argument);
    #endif
} )

DEF_CMD (ja, 21, 2, {
    double first  = stackPop(cpu->computeStack);
    double second = stackPop(cpu->computeStack);
    #ifdef DEBUG
        printf("ja: first = %lf second = %lf", first, second);
        if (second > first) {
            printf("second > first = %d and because of this was jump to %d\n", second > first, (int)(cpu->code[++cpu->ofs]));
        } else {
            printf("second > first = %d and because of this there WAS NOT jump to %d\n", second > first, (int)(cpu->code[++cpu->ofs]));
        }
    #endif
    if (second > first) {
        int argument = (int)(cpu->code[++cpu->ofs]);
        cpu->ofs = argument;
        cpu->ofs--;
        MOVE_ADRESS_BECAUSE_OF_HEADER
    }
} )

DEF_CMD (jae, 22, 2, {
    double first  = stackPop(cpu->computeStack);
    double second = stackPop(cpu->computeStack);
    #ifdef DEBUG
        printf("jae: first = %lf second = %lf", first, second);
        if (second >= first) {
            printf("second >= first = %d and because of this was jump to %d\n", second >= first, (int)(cpu->code[++cpu->ofs]));
        } else {
            printf("second >= first = %d and because of this there WAS NOT jump to %d\n", second >= first, (int)(cpu->code[++cpu->ofs]));
        }
    #endif
    if (second >= first) {
        int argument = (int)(cpu->code[++cpu->ofs]);
        cpu->ofs = argument;
        cpu->ofs--;
        MOVE_ADRESS_BECAUSE_OF_HEADER
    }
} )

//TODO ÂÑÅ JUMP ÏÎ ÒÈÏÓ JB Ñ ÎÒÑÓÒÑÒÂÈÅÌ ÑÄÂÈÃÀ
DEF_CMD (jb, 23, 2, {
    double first  = stackPop(cpu->computeStack);
    double second = stackPop(cpu->computeStack);
    #ifdef DEBUG
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
        int argument = (int)(cpu->code[++cpu->ofs]);
        cpu->ofs = argument;
        cpu->ofs--;
        MOVE_ADRESS_BECAUSE_OF_HEADER
    } else {
        cpu->ofs++;
    }
} )

DEF_CMD (jbe, 24, 2, {
    double first  = stackPop(cpu->computeStack);
    double second = stackPop(cpu->computeStack);
    #ifdef DEBUG
        printf("jbe: first = %lf second = %lf", first, second);
        if (second <= first) {
            printf("second <= first = %d and because of this was jump to %d\n", second <= first, (int)(cpu->code[++cpu->ofs]));
        } else {
            printf("second <= first = %d and because of this there WAS NOT jump to %d\n", second <= first, (int)(cpu->code[++cpu->ofs]));
        }
    #endif
    if (second <= first) {
        int argument = (int)(cpu->code[++cpu->ofs]);
        cpu->ofs = argument;
        cpu->ofs--;
        MOVE_ADRESS_BECAUSE_OF_HEADER
    }
} )

DEF_CMD (je, 25, 2, {
    double first  = stackPop(cpu->computeStack);
    double second = stackPop(cpu->computeStack);
    #ifdef DEBUG
        printf("je: first = %lf second = %lf", first, second);
        if (second == first) {
            printf("second == first = %d and because of this was jump to %d\n", second == first, (int)(cpu->code[++cpu->ofs]));
        } else {
            printf("second == first = %d and because of this there WAS NOT jump to %d\n", second == first, (int)(cpu->code[++cpu->ofs]));
        }
    #endif
    if (second == first) {
        int argument = (int)(cpu->code[++cpu->ofs]);
        cpu->ofs = argument;
        cpu->ofs--;
        MOVE_ADRESS_BECAUSE_OF_HEADER
    }
} )

DEF_CMD (jne, 26, 2, {
    double first  = stackPop(cpu->computeStack);
    double second = stackPop(cpu->computeStack);
    #ifdef DEBUG
        printf("jne: first = %lf second = %lf", first, second);
        if (second != first) {
            printf("second != first = %d and because of this was jump to %d\n", second != first, (int)(cpu->code[++cpu->ofs]));
        } else {
            printf("second != first = %d and because of this there WAS NOT jump to %d\n", second != first, (int)(cpu->code[++cpu->ofs]));
        }
    #endif
    if (second != first) {
        int argument = (int)(cpu->code[++cpu->ofs]);
        cpu->ofs = argument;
        cpu->ofs--;
        MOVE_ADRESS_BECAUSE_OF_HEADER
    }
} )

DEF_CMD (jt, 27, 2, {
    time_t t = time(NULL);
    struct tm* timeInfo = localtime(&t);
    printf ("timeInfo->tm_wday = %d\n",timeInfo->tm_wday);
    #ifdef DEBUG
        printf("jt: timeInfo->tm_wday = %d", timeInfo->tm_wday);
        if (timeInfo->tm_wday == 2) {
            printf("timeInfo->tm_wday == 2 = %d and because of this was jump to %d\n", timeInfo->tm_wday == 2, (int)(cpu->code[++cpu->ofs]));
        } else {
            printf("timeInfo->tm_wday == 2 = %d and because of this there WAS NOT jump to %d\n", timeInfo->tm_wday == 2, (int)(cpu->code[++cpu->ofs]));
        }
    #endif
    if (timeInfo->tm_wday == 2) {
        int argument = (int)(cpu->code[++cpu->ofs]);
        cpu->ofs = argument;
        cpu->ofs--;
        MOVE_ADRESS_BECAUSE_OF_HEADER
    }
} ) //Joke

// ---

DEF_CMD (call, 30, 2, {
    stackPush(cpu->callings, cpu->ofs + sizeof(double));
	int argument = (int)(cpu->code[cpu->ofs]);
    cpu->ofs = argument;
    MOVE_ADRESS_BECAUSE_OF_HEADER
} )

DEF_CMD (ret, 31, 0, {
    cpu->ofs = stackPop(cpu->callings);
} )

#ifdef DEBUG
#undef DEF_CMD
#endif
