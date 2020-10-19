bool executeProgram (stack_t* programStack) {
    stack_t* computeStack = newStack (4);
    int currentCommand;

    while (true) {
        currentCommand = (int) stackPop (programStack);

        switch(currentCommand) {
            case 0:
            {
                return true;
            }
            case 1:
            {
                stackDump (computeStack);
                double input;
                scanf("%lf", &input);
                stackPush (computeStack, input);
                stackDump (computeStack);
                break;
            }
            case 2:
            {
                double forOutput = stackTop (computeStack);
                break;
            }
            case 3:
            {
                double toPush = stackPop (programStack);
                stackPush (computeStack, toPush);
                break;
            }
            case 4:
            {
                stackPop (computeStack);
                break;
            }
            case 5:
            {
                double first  = stackPop (computeStack);
                double second = stackPop (computeStack);
                stackPush (computeStack, first + second);
                break;
            }
            case 6:
            {
                double first  = stackPop (computeStack);
                double second = stackPop (computeStack);
                stackPush (computeStack, first - second);
                break;
            }
            case 7:
            {
                double first  = stackPop (computeStack);
                double second = stackPop (computeStack);
                stackPush (computeStack, first * second);
                break;
            }
            case 8:
            {
                double first  = stackPop (computeStack);
                double second = stackPop (computeStack);
                stackPush (computeStack, first / second);
                break;
            }
            case 9:
            {
                double first  = stackPop (computeStack);
                double second = stackPop (computeStack);
                stackPush (computeStack, pow (first, 1/second));
                break;
            }
            case 10:
            {
                double first  = stackPop (computeStack);
                double second = stackPop (computeStack);
                stackPush (computeStack, pow (first, second));
                break;
            }
            case 11:
            {
                double first  = stackPop (computeStack);
                stackPush (computeStack, sin (first));
                break;
            }
            case 12:
            {
                double first  = stackPop (computeStack);
                stackPush (computeStack, cos (first));
                break;
            }
        }
    }
};
