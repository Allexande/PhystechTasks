//Version 0.7

#include <stdio.h>
#include <stdlib.h>

#include "Differentiator.c"

//SOME QUESTIONS
//Is it OK to write node1 node2... on treemaster.c

//TODO ��� ������������� �������� �� DEFINE!!!

int main() {

    //Probably there can be input in file
    char* str = (char*) calloc (sizeof(char), MAX_LENGTH_OF_EXPRESSION);

    str = "SIN(3+7+1+x)+COS(x)^2";

    DiffTree* myTree = BuildTreeFromText (str);

    //TreeDump (myTree);

    //SimplifyTree (myTree);

    //TreeDump (myTree);

    FindFewDerivatives (myTree, 2);

    return 0;
}
