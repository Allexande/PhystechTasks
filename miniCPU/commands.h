
//Command (name, code, parameters, call)

DEF_CMD (hlt, 0, 0, {printf("itHappened\n");} )

DEF_CMD (in,   1, 0, {printf("itHappened\n");} )
DEF_CMD (out,  2, 0, {printf("itHappened\n");} )

DEF_CMD (push, 32, 1, {printf("itHappened\n");} )
DEF_CMD (pop,  64, 1, {printf("itHappened\n");} )

DEF_CMD (add,  10, 0, {printf("itHappened\n");} )
DEF_CMD (sub,  11, 0, {printf("itHappened\n");} )
DEF_CMD (mul,  12, 0, {printf("itHappened\n");} )
DEF_CMD (div,  13, 0, {printf("itHappened\n");} )
DEF_CMD (sqrt, 14, 0, {printf("itHappened\n");} )
DEF_CMD (sin,  15, 0, {printf("itHappened\n");} )
DEF_CMD (cos,  16, 0, {printf("itHappened\n");} )

DEF_CMD (jmp,  20, 2, {printf("itHappened\n");} )
DEF_CMD (ja,   21, 2, {printf("itHappened\n");} )
DEF_CMD (jae,  22, 2, {printf("itHappened\n");} )
DEF_CMD (jb,   23, 2, {printf("itHappened\n");} )
DEF_CMD (jbe,  24, 2, {printf("itHappened\n");} )
DEF_CMD (je,   25, 2, {printf("itHappened\n");} )
DEF_CMD (jne,  26, 2, {printf("itHappened\n");} )
DEF_CMD (jt,   27, 2, {printf("itHappened\n");} ) //Joke

DEF_CMD (call,  30, 2, {printf("itHappened\n");} )
DEF_CMD (ret,   31, 0, {printf("itHappened\n");} )
