#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEF_CMD(name, num, arg, code) \
        CMD_##name = num,

enum commands {
    #include "commands.h"
};

#undef DEF_CMD
