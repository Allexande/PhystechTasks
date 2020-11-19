//Version 0.1

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

//Create new structures
Tree* CreateEmptyTree ();
Node* CreateEmptyNode ();

//Work with data base files
Tree* GetTreeFromFile (const char *fileName);

//Work with strings
char* CutBothSides (char* str);

//Dump
bool GraphTree (Tree* thisTree);
