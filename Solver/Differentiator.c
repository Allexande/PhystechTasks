//Version 0.6

#include "Differentiator.h"

#define TEX_MODE

#ifdef TEX_MODE
    #define TEX_DIFF(first, second) \
        WriteDiff(TEX_FILE_NAME, first, second)
#endif

//Define block
// ---------------------------------------------------------------

#define LEFT  node->left
#define RIGHT node->right

#define dL Derivative(LEFT)
#define dR Derivative(RIGHT)
#define cL Copy(LEFT)
#define cR Copy(RIGHT)
#define cN Copy(node)

#define NEWNODE(number) CreateNewNode((OPnumber) number, CONST)

#define NUMBER(node)   (node->type == CONST)
#define VARIABLE(node) (node->type == VAR)

#define ADD(left, right) \
  TreeSetNode(left, right, OP_ADD, OPERATION)

#define SUB(left, right) \
  TreeSetNode(left, right, OP_SUB, OPERATION)

#define MUL(left, right) \
  TreeSetNode(left, right, OP_MUL, OPERATION)

#define DIV(left, right) \
  TreeSetNode(left, right, OP_DIV, OPERATION)

#define POW(left, right) \
  TreeSetNode(left, right, OP_POW, OPERATION)

#define EXP(right) \
  TreeSetNode(NULL, right, OP_EXP, OPERATION)

#define LGN(right) \
  TreeSetNode(NULL, right, OP_LGN, OPERATION)

// ---------------------------------------------------------------

void FindFewDerivatives (DiffTree* tree, size_t derivativeOrder) {

    assert (tree);

    #ifdef TEX_MODE
        WriteBeginning (TEX_FILE_NAME);
    #endif

    for (size_t i = 0; i < derivativeOrder; i++) {

        #ifdef TEX_MODE
            StartOfTakingDerivative (TEX_FILE_NAME, i + 1);
        #endif

        SimplifyTree (tree);

        FindTheDerivative (tree);
        SimplifyTree (tree);

        #ifdef TEX_MODE
            WriteSubtree (TEX_FILE_NAME, tree->root);
        #endif
    }



    #ifdef TEX_MODE
        WriteEnd       (TEX_FILE_NAME);
        //TranslateToPDF (TEX_FILE_NAME);
    #endif
}

void FindTheDerivative (DiffTree* tree) {

    assert (tree);

    tree->root = Derivative (tree->root);
}

DiffNode* Derivative (DiffNode* node) {

    assert(node);

    switch (node->type) {

        case CONST: {
            DiffNode* newNode = CreateNewNode ((OPnumber) 0, CONST);
            TEX_DIFF(node, newNode);
            return newNode;
        } break;

        case VAR: {
            DiffNode* newNode = CreateNewNode ((OPnumber) 1, CONST);
            TEX_DIFF(node, newNode);
            return newNode;
        } break;

        case OPERATION: {

            switch (node->value.op) {

                case OP_ADD: {
                    DiffNode* newNode = ADD(dL, dR);
                    TEX_DIFF(node, newNode);
                    return newNode;
                } break;

                case OP_SUB: {
                    DiffNode* newNode = SUB(dL, dR);
                    TEX_DIFF(node, newNode);
                    return newNode;
                } break;

                case OP_DIV: {
                    DiffNode* newNode = DIV( SUB(MUL(dL, cR), MUL(cL, dR)), MUL(cR, cR) );
                    TEX_DIFF(node, newNode);
                    return newNode;
                } break;

                case OP_MUL: {
                    DiffNode* newNode = ADD(MUL(dL, cR), MUL(cL, dR));
                    TEX_DIFF(node, newNode);
                    return newNode;
                } break;

                case OP_POW: {

                        DiffNode* newNode = NULL;
                        if (FindVar(LEFT))
                          newNode = MUL(MUL(POW(cL, SUB(cR, NEWNODE(1)) ), cR), dL);

                        else {
                          DiffNode* ln_a = CreateNewNode(OP_LGN, OPERATION);
                          ln_a->right = cL;

                          newNode = MUL( MUL(cN, ln_a), dR);
                        }

                        TEX_DIFF(node, newNode);
                        return newNode;
                } break;

                case OP_SIN: {
                    node->value.op = OP_COS;

                    DiffNode* newNode = MUL(cN, dR);

                    node->value.op = OP_SIN;
                    TEX_DIFF(node, newNode);
                    return newNode;
                } break;

                case OP_COS: {
                    node->value.op = OP_SIN;

                    DiffNode* newNode = MUL(SUB(NEWNODE(0), cN), dR);

                    node->value.op = OP_COS;
                    TEX_DIFF(node, newNode);
                    return newNode;
                } break;

                case OP_TAN: {
                    node->value.op = OP_COS;

                    DiffNode* newNode = MUL(DIV(NEWNODE(1), POW(cN, NEWNODE(2))), dR);

                    node->value.op = OP_TAN;
                    TEX_DIFF(node, newNode);
                    return newNode;
                } break;

                case OP_CTN: {
                    node->value.op = OP_SIN;

                    DiffNode* newNode = MUL(SUB(NEWNODE(0), DIV(NEWNODE(1), POW(cN, NEWNODE(2)))), dR);

                    node->value.op = OP_CTN;
                    TEX_DIFF(node, newNode);
                    return newNode;
                } break;

                case OP_ACS: {
                    DiffNode* newNode = MUL(SUB(NEWNODE(0), DIV(NEWNODE(1), POW(SUB(NEWNODE(1), POW(cR, NEWNODE(2))), NEWNODE(0.5)))), dR);
                    TEX_DIFF(node, newNode);
                    return newNode;
                } break;

                case OP_ASN: {
                    DiffNode* newNode = MUL(DIV(NEWNODE(1), POW(SUB(NEWNODE(1), POW(cR, NEWNODE(2))), NEWNODE(0.5))), dR);
                    TEX_DIFF(node, newNode);
                    return newNode;
                } break;

                case OP_ATN: {
                    DiffNode* newNode = MUL(DIV(NEWNODE(1), ADD(NEWNODE(1), POW(cR, NEWNODE(2)) )), dR);
                    TEX_DIFF(node, newNode);
                    return newNode;
                } break;

                case OP_SIH: {
                    node->value.op = OP_COH;

                    DiffNode* newNode = MUL(cN, dR);

                    node->value.op = OP_SIH;

                    TEX_DIFF(node, newNode);
                    return newNode;
                } break;

                case OP_COH: {
                    node->value.op = OP_SIH;

                    DiffNode* newNode = MUL(cN, dR);

                    node->value.op = OP_COH;

                    TEX_DIFF(node, newNode);
                    return newNode;
                } break;

                case OP_TGH: {
                    node->value.op = OP_COH;

                    DiffNode* newNode = MUL(DIV(NEWNODE(1), POW(cN, NEWNODE(2))), dR);

                    node->value.op = OP_TGH;

                    TEX_DIFF(node, newNode);
                    return newNode;
                } break;

                case OP_LGN: {
                    DiffNode* newNode = MUL(DIV(NEWNODE(1), cR), dR);

                    TEX_DIFF(node, newNode);
                    return newNode;
                } break;


                default: {
                  printf("Unknown function\n");
                } break;
            }
        }

        return node;
    }
}

void SimplifyTree (DiffTree* tree) {

    assert (tree);

    SimplifyNode (tree->root, NULL);
}

void SimplifyNode (DiffNode* node, DiffNode* parent) {

    assert (node);

    if (LEFT != NULL) {
        SimplifyNode (LEFT, node);
    }

    if (node->right != NULL) {
        SimplifyNode (node->right, node);
    }

    TryToSimplify (node, parent);
}

void TryToSimplify (DiffNode* node, DiffNode* parent) {

    DiffNode* nodeBeforeSimplification = Copy (node);

    #define SIMPLIFICATION_RULE(condition, action)  \
        if (condition) {                            \
            action;                                 \
            return;                                 \
        }

    #include "simplifications.h"

    #undef SIMPLIFICATION_RULE

    #ifdef TEX_MODE
        WriteSimp (TEX_FILE_NAME, nodeBeforeSimplification, node);
    #endif
}

void ChangeNodeForBinaryOperation (DiffNode* node) {

    assert (node);

    node->type = CONST;
    DeleteChildren (node);
}

void SimplifyADD (DiffNode* node) {

    assert (node);

    node->value.number = LEFT->value.number + node->right->value.number;
    ChangeNodeForBinaryOperation (node);
}

void SimplifySUB (DiffNode* node) {

    assert (node);

    node->value.number = LEFT->value.number - node->right->value.number;
    ChangeNodeForBinaryOperation (node);
}

void SimplifyMUL (DiffNode* node) {

    assert (node);

    node->value.number = LEFT->value.number * node->right->value.number;
    ChangeNodeForBinaryOperation (node);
}

void SimplifyDIV (DiffNode* node) {

    assert (node);

    if (node->right->value.number == 0) {

        printf("\nDEVIDING ON ZERO! RESULT IS NOT CORRECT\n");
        node->value.number = 99999; //Just a huge number

    } else {
        node->value.number = LEFT->value.number / node->right->value.number;
    }

    ChangeNodeForBinaryOperation (node);
}

void SimplifyPOW (DiffNode* node) {

    assert (node);

    node->value.number = pow (LEFT->value.number, node->right->value.number);
    ChangeNodeForBinaryOperation (node);
}

void ChangeNodeForSingalOperation (DiffNode* node) {

    assert (node);

    node->type = CONST;
    DeleteChild (node, 0);
}

void SimplifyABS (DiffNode* node) {

    assert (node);

    node->value.number = fabs (node->right->value.number);
    ChangeNodeForSingalOperation (node);
}

void SimplifyLGN (DiffNode* node) {

    assert (node);

    node->value.number = log (node->right->value.number);
    ChangeNodeForSingalOperation (node);
}

void SimplifyEXP (DiffNode* node) {

    assert (node);

    node->value.number = exp (node->right->value.number);
    ChangeNodeForSingalOperation (node);
}

void SimplifySRT (DiffNode* node) {

    assert (node);

    if (node->right->value.number >= 0) {
        node->value.number = sqrt (node->right->value.number);
    } else {

        printf("\SQRT FROM ZERO! RESULT IS NOT CORRECT\n");
        node->value.number = 0; //Just a zero number

    }

    ChangeNodeForSingalOperation (node);
}

void SimplifySIN (DiffNode* node) {

    assert (node);

    node->value.number = sin (node->right->value.number);
    ChangeNodeForSingalOperation (node);
}

void SimplifyCOS (DiffNode* node) {

    assert (node);

    node->value.number = cos (node->right->value.number);
    ChangeNodeForSingalOperation (node);
}

void SimplifyTAN (DiffNode* node) {

    assert (node);

    if (node->right->value.number != 0) {
        node->value.number = tan (node->right->value.number);
    } else {

        printf("\nIMPOSSIBLE TAN! RESULT IS NOT CORRECT\n");
        node->value.number = 99999; //Just a huge number

    }

    ChangeNodeForSingalOperation (node);
}

void SimplifyCTN (DiffNode* node) {

    assert (node);

    if (tan (node->right->value.number) != 0) {
        node->value.number = 1 / tan (node->right->value.number);
    } else {

        printf("\nIMPOSSIBLE ATAN! RESULT IS NOT CORRECT\n");
        node->value.number = 99999; //Just a huge number

    }

    ChangeNodeForSingalOperation (node);
}

void SimplifyASN (DiffNode* node) {

    assert (node);

    node->value.number = asin (node->right->value.number);
    ChangeNodeForSingalOperation (node);
}

void SimplifyACS (DiffNode* node) {

    assert (node);

    node->value.number = acos (node->right->value.number);
    ChangeNodeForSingalOperation (node);
}

void SimplifyATN (DiffNode* node) {

    assert (node);

    node->value.number = atan (node->right->value.number);
    ChangeNodeForSingalOperation (node);
}

void SimplifyACN (DiffNode* node) {

    assert (node);

    node->value.number = M_PI/2 - atan (node->right->value.number);
    ChangeNodeForSingalOperation (node);
}

void SimplifySIH (DiffNode* node) {

    assert (node);

    node->value.number = sinh (node->right->value.number);
    ChangeNodeForSingalOperation (node);
}

void SimplifyCOH (DiffNode* node) {

    assert (node);

    node->value.number = cosh (node->right->value.number);
    ChangeNodeForSingalOperation (node);
}

void SimplifyTGH (DiffNode* node) {

    assert (node);

    node->value.number = tanh (node->right->value.number);
    ChangeNodeForSingalOperation (node);
}

void SimplifyCTH (DiffNode* node) {

    assert (node);

    node->value.number = atanh (node->right->value.number);
    ChangeNodeForSingalOperation (node);
}

//Undefine block
// ---------------------------------------------------------------

#undef LEFT
#undef RIGHT

#undef dL
#undef dR
#undef cL
#undef cR
#undef cN

#undef NEWNODE(number)

#undef NUMBER(node)
#undef VARIABLE(node)

#undef ADD(left, right)

#undef SUB(left, right)

#undef MUL(left, right)

#undef DIV(left, right)

#undef POW(left, right)

// ---------------------------------------------------------------

