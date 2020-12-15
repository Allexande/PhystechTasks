//Version 0.4

#include <stdio.h>
#include <stdlib.h>

#include "Differentiator.c"

//SOME QUESTIONS
//Is it OK to write node1 node2... on treemaster.c

//TODO PARENT of NODES is not used

//TODO ¬—≈ œŒ¬“Œ–ﬂﬁŸ≈≈—ﬂ «¿Ã≈Õ»“‹ Õ¿ DEFINE!!!

int main() {

    //Probably there can be input in file
    char* str = (char*) calloc (sizeof(char), MAX_LENGTH_OF_EXPRESSION);

    str = "1/x+x/1";

    DiffTree* myTree = BuildTreeFromText (str);

    //TreeDump (myTree);

    //SimplifyTree (myTree);

    FindFewDerivatives (myTree, 0);

    TreeDump (myTree);

    return 0;
}
