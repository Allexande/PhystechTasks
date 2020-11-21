//Version 0.5

#define COEF_OF_REALLOC 2

#define BEGIN_CORONARY_VALUE 0xBADC0FFE
#define END_CORONARY_VALUE   0xDEAD9999

#define POISON 0

#define DEBUG_MODE
#ifdef DEBUG_MODE
#define ASSERT_OK(thov) if(stackNotOK(thov)) {printf("ERROR:%d\n",stackNotOK(thov));stackDump(thov); assert(!"OK");}
#else
#define ASSERT_OK ;
#endif

typedef Node* Elem_t;
typedef long  hash_t;
typedef long  coronary_t;

struct stack_t {

    coronary_t beginCoronary;

    Elem_t*    data;
    size_t     length;
    size_t     capacity;

    stack_t*   adress;
    hash_t     protectingHash;
    coronary_t endCoronary;

};

enum error_t {
    NO_ERROR = 0,
    POINTER_ON_STACK_IS_NULL,    //1
    POINTER_ON_DATA_IS_NULL,     //2
    LENGTH_BIGGER_THAN_CAPACITY, //3
    CAPACITY_LOWER_THAN_ONE,     //4
    BEGIN_CORONARY_DEAD,         //5
    END_CORONARY_DEAD,           //6
    WRONG_HASH,                  //7
    WRONG_ADRESS                 //8
};

stack_t* newStack (size_t capacity);

bool stackConstructor (stack_t* thov, size_t capacity);

void stackDesructor (stack_t* thov);

void stackPush (stack_t* thov, Elem_t element);

Elem_t stackPop (stack_t* thov);

Elem_t stackTop (stack_t* thov);

void stackDump (stack_t* thov);

bool changeMemory (stack_t* thov, int dir);

bool addMemory  (stack_t* thov);

bool lessMemory (stack_t* thov);

error_t stackNotOK (stack_t* thov);

hash_t getHash (stack_t* thov);

void poisonFrom (stack_t* thov, int point);

//#include "stack.c"
