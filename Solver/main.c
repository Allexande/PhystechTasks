//Version 0.2

#include <stdio.h>
#include <stdlib.h>

#include "Differentiator.c"

//SOME QUESTIONS
//Is it OK to write node1 node2... on treemaster.c

//TODO PARENT of NODES is not used

//TODO ��� ������������� �������� �� DEFINE!!!

int main() {

    //Probably there can be input in file
    char* str = (char*) calloc (sizeof(char), MAX_LENGTH_OF_EXPRESSION);

    str = "3*(x+0)-0+SIN(COS(x-0))+0";

    DiffTree* myTree = BuildTreeFromText (str);

    //TreeDump (myTree);

    SimplifyTree (myTree);

    printf(">>>>>>> myTree=%ld myTree->root=%ld myTree->root->left=%ld myTree->root->right=%ld\n", myTree, myTree->root, myTree->root->left, myTree->root->right);

    TreeDump (myTree);

    return 0;
}
