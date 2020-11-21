//Version 0.6

#include "filemaster.c"

struct Node {

   //Type
   //= 1 means this is question
   //= 0 means this is sheet
   bool question;

   //Node whose child this node is
   //= NULL if this is the root of tree
   Node* parent;

   //The text of question or subject
   char* text;

   //Link to node if the answer is yes
   Node* right;
   //Link to node if the answer is no
   Node* left;

};

#include "stack.c"

struct Tree {

    //The first node in the tree
    Node* root;

    //Array of pointers on sheet nodes
    Node** subjects;

    //Mode
    //= 1 means this tree got new nodes
    //= 0 means this tree remains unchanged
    bool wasChanged;

};

enum AllocationConsts {
    DEFAULT_POSSIBLESUB_SIZE = 10,
    MAXIMUM_TEXT_SIZE        = 256
};

//Create new structures
Tree* CreateEmptyTree ();
Node* CreateEmptyNode ();

//Work with data base files
Tree* GetTreeFromFile (const char *fileName);
bool  PutTreeToFile   (const char *fileName, Tree* thisTree);
void  WriteNodeToFile (Node* thisNode, FILE *file);

//Work with strings
char* CutBothSides (char* str);

//Work with list of subjects
size_t FillArrayOfSubs           (Tree* thisTree);
void   TryToAddNodeInArrayOfSubs (Tree* thisTree, Node* currentNode, size_t* subsLength);
/*
/bool   AddNodeInArrayOfSubs      (Tree* thisTree, Node* nodeToAdd);
*/

//Add new nodes
bool AddNewSub (Node* thisNode, char* newSub, char* newQuestion);

//Dump
bool GraphTree (Tree* thisTree);
void GraphNode (Node* thisNode, FILE* file);
void ConsoleTreeDump (Tree* thisTree);
void ConsoleNodeDump (Node* thisNode);
