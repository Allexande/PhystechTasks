
//Crash
struct test {
    int inBegin;
    stack_t* testStack;
    int inEnd;
};

void breakStack() {
    /*
    test* myTest = (test*) calloc (1, sizeof(test));
    myTest->testStack = newStack (5);

    //printf("hey\n");

    stackPush (myTest->testStack, 1);
    stackPush (myTest->testStack, 10);
    stackPush (myTest->testStack, 1000);
    stackPush (myTest->testStack, 2);
    stackPush (myTest->testStack, 200);
    stackPush (myTest->testStack, 2000);

    stackDump (myTest->testStack);


    int* adress1 = &(myTest->inBegin);

    printf("adress1=%ld\n", adress1);

    *(adress1 + 12) = 999;
    *(adress1 + 36) = 999;
    *(adress1 + 156) = 999;
    *(adress1 + 160) = 999;
    *(adress1 + 170) = 999;
    *(adress1 + 180) = 999;

    for (int i = 0; i< 100; i++) {
        *(adress1 + i*4) = i*i;
        printf("NOW *(adress1 + %d) =%d\n",i*4,*(adress1 + i*4));
    }

    stackPush (myTest->testStack, 5);

    stackDump (myTest->testStack);


    //printf("hey\n");

    */



    //Petr crash
    test* myTest = (test*) calloc (1, sizeof(test));

}
