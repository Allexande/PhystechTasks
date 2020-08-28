//TESTING FUNCTIONS

bool thisNumbersAreRootsForEquation(double a, double b, double c, double root1, double root2){
    printf("a*power(root1, 2) + b*root1 + c -> %.5lf*power(%.5lf, 2) + %.5lf*%.5lf + %.5lf = %.5lf\n", a, root1, b, root1, c, (a*power(root1, 2) + b*root1 + c));
    printf("a*power(root2, 2) + b*root2 + c -> %.5lf*power(%.5lf, 2) + %.5lf*%.5lf + %.5lf = %.5lf\n", a, root2, b, root2, c, (a*power(root2, 2) + b*root2 + c));
    return (numberIsNearZero(a*power(root1, 2) + b*root1 + c) && numberIsNearZero(a*power(root2, 2) + b*root2 + c));
}

bool thisNumberIsRootForEquation(double a, double b, double c, double root){
    printf("a*power(root, 2) + b*root + c -> %.5lf*power(%.5lf, 2) + %.5lf*%.5lf + %.5lf = %.5lf\n", a, root, b, root, c, (a*power(root, 2) + b*root + c));
    return numberIsNearZero(a*power(root, 2) + b*root + c);
}

bool thisEquationDoesntHaveAnyRoot(double a, double b, double c){
    printf("power(b, 2) - 4*a*c -> power(%.5lf, 2) - 4*%.5lf*%.5lf = %.5lf\n", b, a, c, (power(b, 2) - 4*a*c));
    return (power(b, 2) - 4*a*c < 0);
}

bool thisEquationIsNotQuadratic(double a){
    printf("a = %.5lf\n", a);
    return (numberIsNearZero(a));
}

bool doTest(double a, double b, double c){
    printf("= = = TEST = = = \na=%.2lf b=%.2lf c=%.2lf \n", a, b, c);
    double root1 = 0;
    double root2 = 0;
    int numberOfRoots = solveQuadraticEquation (a ,b ,c, &root1, &root2);

    switch(numberOfRoots) {

        case 0:
        printf("%s\n", "solveQuadraticEquation: There are no roots.");
        if(thisEquationDoesntHaveAnyRoot(a, b, c)){
            printf("%s\n", "This is true.\n\n");
            return true;
        }
        break;

        case 1:
        printf("%s%.2lf\n", "solveQuadraticEquation: There is one root: ", root1);
        if(thisNumberIsRootForEquation(a, b, c, root1)){
            printf("%s\n", "This is true.\n\n");
            return true;
        }
        break;

        case 2:
        printf("%s%.2lf %.2lf\n", "solveQuadraticEquation: There are two roots: ", root1, root2);
        if(thisNumbersAreRootsForEquation(a, b, c, root1, root2)){
            printf("%s\n", "This is true.\n\n");
            return true;
        }
        break;

        case NOT_QUADRATIC_CODE:
        printf("%s\n", "solveQuadraticEquation: The a coefficient cannot be equal to 0!");
        if(thisEquationIsNotQuadratic(a)){
            printf("%s\n", "This is true.\n\n");
            return true;
        }
        break;

    }

    printf("%s\n", "This is false!\n\n");
    return false;
}

double generateRandomDouble(double minNumber, double maxNumber){
    return (double)(rand())/RAND_MAX*(maxNumber - minNumber) + minNumber;
}

bool doTestWithRandomValues(double minNumber, double maxNumber){
    double a = generateRandomDouble(minNumber, maxNumber);
    double b = generateRandomDouble(minNumber, maxNumber);
    double c = generateRandomDouble(minNumber, maxNumber);
    return doTest(a, b, c);
}
