#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "quadraticEquation.с"

/*
ОТКРЫТЫЕ ВОПРОСЫ:
- Как дробить программу на файлы?
- Как CodeBlocks'у объяснить, что файл является СИшным и чтобы он начал его правильно отображать?
- Как нормально реализовывать ООП в СИ?
- Как делать документацию к отдельным файлам/методам/структурам?
*/

#define NOT_QUADRATIC_CODE -1

int solveQuadraticEquation (float a ,float b ,float c, float* root1, float* root2){

    if(a == 0) {
        return NOT_QUADRATIC_CODE;
    }

    float discriminant = pow(b, 2) - 4*a*c;
    if(discriminant > 0) {
        if(discriminant == 0){
            *root1 = (-b / (2*a));
            *root2 = *root1;
            return 1;
        } else {
            *root1 = ((-b + sqrt(discriminant)) / (2*a));
            *root2 = ((-b - sqrt(discriminant)) / (2*a));
            return 2;
        }
    } else {
        return 0;
    }
}

int main()
{

    printf("%s\n", "Write coefficient a:");
    float a = 0.0;
    scanf("%e", &a);

    printf("%s\n", "Write coefficient b:");
    float b = 0.0;
    scanf("%e", &b);

    printf("%s\n", "Write coefficient c:");
    float c = 0.0;
    scanf("%e", &c);

    float root1 = 0;
    float root2 = 0;
    int numberOfRoots = solveQuadraticEquation (a ,b ,c, &root1, &root2);

    switch(numberOfRoots) {

        case 0:
        printf("%s\n", "There are no roots.");
        break;

        case 1:
        printf("%s\n%.2f", "There is one root:", root1);
        break;

        case 2:
        printf("%s\n%.2f\n%.2f", "There are two roots:", root1, root2);
        break;

        case NOT_QUADRATIC_CODE:
        printf("%s\n", "The a coefficient cannot be equal to 0!");
        break;

    }

    return 0;
}
