//Version 0.3

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

    str = "2+(x+4)^0+(x-2)^0+4+(9-x)^1+(55-55)^(3+3)";

    DiffTree* myTree = BuildTreeFromText (str);

    //TreeDump (myTree);

    SimplifyTree (myTree);

    TreeDump (myTree);

    return 0;
}
