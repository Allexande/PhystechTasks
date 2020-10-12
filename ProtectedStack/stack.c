#define COEF_OF_REALLOC 2

#define CORONARY_VALUE 0xBADC0FFEE

#define DEBUG_MODE
#ifdef DEBUG_MODE
#define ASSERT_OK(thov) if(stackOK(thov)) {printf("ERROR:%d\n",stackOK(thov));stackDump(thov); assert(!"OK");}
#else
#define ASSERT_OK ;
#endif

typedef int Elem_t;
typedef long hash_t;
typedef long coronary_t;

struct stack_t {

    coronary_t beginCoronary;
    Elem_t* data;
    size_t length;
    size_t capacity;
    hash_t protectingHash;
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
    WRONG_HASH                   //7
};

stack_t* newStack (size_t capacity);

void stackConstructor (stack_t* thov, size_t capacity);

void stackDesructor (stack_t* thov);

void stackPush (stack_t* thov, Elem_t element);

Elem_t stackPop (stack_t* thov);

Elem_t stackTop (stack_t* thov);

void stackDump (stack_t* thov);

bool changeMemory (stack_t* thov, int dir);

bool addMemory  (stack_t* thov);

bool lessMemory (stack_t* thov);

error_t stackOK (stack_t* thov);

hash_t getHash (stack_t* thov);

void stackConstructor (stack_t* thov, size_t capacity) {

    thov->data = (Elem_t*) calloc (capacity, sizeof(Elem_t));
    assert (thov->data); //??
    thov->capacity = capacity;
    thov->beginCoronary  = CORONARY_VALUE;
    thov->endCoronary    = CORONARY_VALUE;
    thov->protectingHash = getHash (thov);

    ASSERT_OK(thov)

}

stack_t* newStack (size_t capacity) {

    stack_t* thov = (stack_t*) calloc (capacity, sizeof(stack_t));
    assert (thov);

    stackConstructor (thov, capacity);

    ASSERT_OK(thov)

    return thov;

};

void stackDesructor (stack_t* thov) {

    assert (thov);

    thov->data     = NULL;
    thov->capacity = 0;
    free (thov);

};

void stackPush (stack_t* thov, Elem_t element) {

    ASSERT_OK(thov)

    if (thov->length == thov->capacity) {
        addMemory (thov);
    }

    thov->data[thov->length++] = element;

    thov->protectingHash = getHash (thov);

    ASSERT_OK(thov)

};

int stackPop (stack_t* thov) {

    ASSERT_OK(thov)

    if (thov->length * COEF_OF_REALLOC < thov->capacity) {
        lessMemory (thov);
    }

    thov->data[thov->length] = NAN;
    thov->length--;

    thov->protectingHash = getHash (thov);

    ASSERT_OK(thov)

    return thov->data[thov->length];

};

int stackTop (stack_t* thov) {

    ASSERT_OK(thov)

    return thov->data[thov->length - 1];

}

error_t stackOK (stack_t* thov) {

    if (thov == NULL) {
        return POINTER_ON_STACK_IS_NULL;
    }

    if (thov->data == NULL) {
        return POINTER_ON_DATA_IS_NULL;
    }

    if (thov->length > thov->capacity) {
        return LENGTH_BIGGER_THAN_CAPACITY;
    }

    if (thov->capacity < 1 ) {
        return CAPACITY_LOWER_THAN_ONE;
    }

    if ((long)thov->beginCoronary != (long)CORONARY_VALUE) {
        return BEGIN_CORONARY_DEAD;
    }

    if ((long)thov->endCoronary != (long)CORONARY_VALUE) {
        return END_CORONARY_DEAD;
    }

    if (thov->protectingHash != getHash (thov)) {
        return WRONG_HASH;
    }

    return NO_ERROR;

};

bool changeMemory (stack_t* thov, int dir) {

    ASSERT_OK(thov)

    //thov->capacity += dir * SIZE_OF_REALLOC;
    if (dir == 1) {
        thov->capacity *= COEF_OF_REALLOC;
    } else {
        thov->capacity /= COEF_OF_REALLOC;

    }

    Elem_t* possibleAdress = (Elem_t*) realloc (thov->data, thov->capacity * sizeof(Elem_t));

    if (possibleAdress != NULL) {
        thov->data = possibleAdress;
        thov->protectingHash = getHash (thov);
        return true;
    } else {
        return false;
    }

};

bool addMemory (stack_t* thov) {

    ASSERT_OK(thov)

    return changeMemory (thov, 1);
};

bool lessMemory (stack_t* thov) {

    ASSERT_OK(thov)

    if (thov != NULL && thov->capacity > 1) {
        return changeMemory (thov, -1);
    } else {
        return false;
    }
};

hash_t getHash (stack_t* thov) {

    assert (thov); //Can't use ASSERT_OK

    hash_t newHash = thov->length + thov->capacity;
    for (int i = 0; i < thov->length; i++) {
        newHash += thov->data[i] * (i + 1);
    }

    return newHash;
};

void stackDump (stack_t* thov) {

    assert (thov);

    //Name of struct, is it OK and adress
    printf("stack_t (%d) [%ld] \n", !stackOK(thov), thov);

    //length and capacity
    printf("length=%d \ncapacity=%d \n", thov->length, thov->capacity);

    //coronarys and hash
    printf("beginCoronary=%d \nendCoronary=%d \nprotectingHash=%ld \n", thov->beginCoronary, thov->endCoronary, thov->protectingHash);

    //data
    printf("data [%ld] \n", thov->data);
    for (int i = 0; i < thov->length; i++) {
        if (thov->data[i] == NAN) {
            printf("data[%d] [%ld] = NAN (POISON!) \n", i, &(thov->data[i]));
        } else {
            printf("data[%d] [%ld] = %d \n", i, &(thov->data[i]), thov->data[i]);
        }

    }

};
