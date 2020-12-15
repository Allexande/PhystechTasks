//Version 0.6

#include <stdio.h>
#include <stdlib.h>

#include "Differentiator.c"

//SOME QUESTIONS
//Is it OK to write node1 node2... on treemaster.c

//TODO ¬—≈ œŒ¬“Œ–ﬂﬁŸ≈≈—ﬂ «¿Ã≈Õ»“‹ Õ¿ DEFINE!!!

int main() {

    //Probably there can be input in file
    char* str = (char*) calloc (sizeof(char), MAX_LENGTH_OF_EXPRESSION);

    str = "x^2+1/x";

    DiffTree* myTree = BuildTreeFromText (str);

    //TreeDump (myTree);

    //SimplifyTree (myTree);

    FindFewDerivatives (myTree, 2);

    return 0;
}
