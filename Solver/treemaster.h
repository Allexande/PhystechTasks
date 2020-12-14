//Version 0.1

#include <string.h>
#include <ctype.h>

#include "filemaster.c"

//Creating new structures
DiffTree* CreateNewTree ();
DiffNode* CreateNewNode (OPnumber newValue, NodeType newType);

//Building tree
DiffTree* BuildTreeFromFile (const char* fileName);
DiffTree* BuildTreeFromText (const char* text);

//Recurrent descent
DiffNode* GetGeneral           (const char* str, size_t* position);
DiffNode* GetExpression        (const char* str, size_t* position);
DiffNode* GetTerm              (const char* str, size_t* position);
DiffNode* GetPower             (const char* str, size_t* position);
DiffNode* GetFunction          (const char* str, size_t* position);
DiffNode* GetPrimaryExpression (const char* str, size_t* position);
DiffNode* GetVariable          (const char* str, size_t* position);
DiffNode* GetNumber            (const char* str, size_t* position);

char* ReadFuncName (const char* str, size_t* position);

//Adding nodes to tree
DiffNode* TreeSetNode (DiffNode* addingLeft,   \
                       DiffNode* addingRight,  \
                       number_t addingData,    \
                       NodeType addingType);

//Error alerts
void SyntaxError (const char* str, const size_t* position, const char* message);
void LogicError  (const char* str, const size_t* position, const char* message);
void ErrorAlert  (const char* str, const size_t* position, const char* message);

//Deleting
//void DeleteNode (DiffNode* node);
void DeleteChild (DiffNode* node, bool left);

//Tree dump
bool TreeDump  (DiffTree* tree);
void GraphNode (DiffNode* thisNode, FILE* file);
