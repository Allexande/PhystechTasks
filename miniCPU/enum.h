//version 1.0.0

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>

#define DEF_CMD(name, num, arg, code) \
        CMD_##name = num,

enum commands {
    #include "commands.h"
};

#undef DEF_CMD
