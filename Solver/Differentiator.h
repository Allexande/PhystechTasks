//Version 0.5

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
#include "texmaster.c"

//Differentiation
void FindFewDerivatives (DiffTree* tree, size_t derivativeOrder);
void FindTheDerivative  (DiffTree* tree);
DiffNode* Derivative    (DiffNode* node);

//Simplification
void SimplifyTree  (DiffTree* tree);
void SimplifyNode  (DiffNode* node, DiffNode* parent);
void TryToSimplify (DiffNode* node, DiffNode* parent);
// (Simplification function)
void ChangeNodeForBinaryOperation (DiffNode* node);

void SimplifyADD (DiffNode* node);
void SimplifySUB (DiffNode* node);
void SimplifyMUL (DiffNode* node);
void SimplifyDIV (DiffNode* node);
void SimplifyPOW (DiffNode* node);

void ChangeNodeForSingalOperation (DiffNode* node);

void SimplifyABS (DiffNode* node);
void SimplifyLGN (DiffNode* node);
void SimplifyEXP (DiffNode* node);
void SimplifySRT (DiffNode* node);
void SimplifySIN (DiffNode* node);
void SimplifyCOS (DiffNode* node);
void SimplifyTAN (DiffNode* node);
void SimplifyCTN (DiffNode* node);
void SimplifyASN (DiffNode* node);
void SimplifyACS (DiffNode* node);
void SimplifyATN (DiffNode* node);
void SimplifyACN (DiffNode* node);
void SimplifySIH (DiffNode* node);
void SimplifyCOH (DiffNode* node);
void SimplifyTGH (DiffNode* node);
void SimplifyCTH (DiffNode* node);
