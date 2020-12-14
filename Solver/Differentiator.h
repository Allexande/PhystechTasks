//Version 0.1

#include <math.h>
#include <string.h>
#include <assert.h>

typedef double number_t;

enum Limit {
    MAX_LENGTH_OF_EXPRESSION = 100
};

enum NodeType {

    //Constant
    CONST     = 0,

    //Variable
    VAR       = 1,

    //Operation
    OPERATION = 2

};

enum OPnumber {

    #define DEF_FUNCTION(name, number) \
        OP_##name = number,

    #include "functions.h"

    #undef DEF_FUNCTION

};

union value_u {

    //Constant value
	number_t number;

	//Operator's number
	OPnumber op;

	//Variable name
	char var;

};

struct DiffNode {

    //Type of node
    NodeType type;

    //Value of node
    value_u value;

    //Pointers to other nodes
    DiffNode* left;
    DiffNode* right;
    DiffNode* parent;

};

struct DiffTree {

    //Root
    DiffNode* root;

};

#include "treemaster.c"

//Simplification
void SimplifyTree  (DiffTree* tree);
void SimplifyNode  (DiffNode* node);
void TryToSimplify (DiffNode* node);
