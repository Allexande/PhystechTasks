bool stackConstructor (stack_t* thov, size_t capacity) {

    thov->data = (Elem_t*) calloc (capacity, sizeof(Elem_t));
    if (thov->data == NULL) {
        return  false;
    }

    thov->capacity = capacity;
    thov->beginCoronary  = BEGIN_CORONARY_VALUE;
    thov->endCoronary    = END_CORONARY_VALUE;
    thov->protectingHash = getHash (thov);
    thov->adress = thov;

    ASSERT_OK(thov)

    return  true;
}

stack_t* newStack (size_t capacity) {

    stack_t* thov = (stack_t*) calloc (capacity, sizeof(stack_t));

    if (thov != NULL && stackConstructor (thov, capacity)) {;
        ASSERT_OK(thov)
        return thov;
    } else {
        return NULL;
    }
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
        poisonFrom (thov, thov->length + 1);
    }

    thov->data[thov->length++] = element;

    thov->protectingHash = getHash (thov);

    ASSERT_OK(thov)

};

Elem_t stackPop (stack_t* thov) {

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

Elem_t stackTop (stack_t* thov) {

    ASSERT_OK(thov)

    return thov->data[thov->length - 1];

}

error_t stackNotOK (stack_t* thov) {

    if (thov == NULL) {
        return POINTER_ON_STACK_IS_NULL;
    }

    if (thov->adress != thov) {
        return WRONG_ADRESS;
    }

    if (thov->data == NULL) {
        return POINTER_ON_DATA_IS_NULL;
    }

    if ((long)thov->beginCoronary != (long)BEGIN_CORONARY_VALUE) {
        return BEGIN_CORONARY_DEAD;
    }

    if ((long)thov->endCoronary != (long)END_CORONARY_VALUE) {
        return END_CORONARY_DEAD;
    }

    if (thov->length > thov->capacity) {
        return LENGTH_BIGGER_THAN_CAPACITY;
    }

    if (thov->capacity < 1 ) {
        return CAPACITY_LOWER_THAN_ONE;
    }

    if (thov->protectingHash != getHash (thov)) {
        return WRONG_HASH;
    }

    return NO_ERROR;

};

bool changeMemory (stack_t* thov, int dir) {

    ASSERT_OK(thov)

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

    hash_t newHash = thov->length + thov->capacity + (int)thov->data;
    for (int i = 0; i < thov->length; i++) {
        newHash += thov->data[i] * (i + 1);
    }

    return newHash;
};

void stackDump (stack_t* thov) {

    assert (thov);

    //Name of struct, is it OK and adress
    printf("stack_t (%d) [%ld] {\n", !stackNotOK(thov), thov);

    //length and capacity
    printf("    length=%d \n    capacity=%d \n", thov->length, thov->capacity);

    //coronarys and hash
    printf("    beginCoronary=%d \n    endCoronary=%d \n    protectingHash=%ld \n", thov->beginCoronary, thov->endCoronary, thov->protectingHash);

    //data
    printf("    data [%ld] {\n", thov->data);
    for (int i = 0; i < thov->capacity; i++) {
        if (thov->data[i] == POISON) {
            printf("        data[%d] [%ld] = %d (POISON!) \n", i, &(thov->data[i]), POISON, &(thov->data[i]));
        } else {
            printf("        data[%d] [%ld] = %d \n", i, &(thov->data[i]), thov->data[i]);
        }

    }

    printf("    }\n}\n\n");

};

void poisonFrom (stack_t* thov, int point) {
    for (int i = point; i < thov->capacity; i++) {
        thov->data[i] = POISON;
    }
};
