//Version 0.4

#include "Differentiator.h"

//Define block
// ---------------------------------------------------------------

#define dL Derivative(node->left)
#define dR Derivative(node->right)
#define cL Copy(node->left)
#define cR Copy(node->right)
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

    SimplifyTree (tree);

    for (size_t i = 0; i < derivativeOrder; i++) {
        FindTheDerivative (tree);
        SimplifyTree (tree);
    }
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
            return newNode;
        } break;

        case VAR: {
            printf(">>>> node->value.var=%c node->left=%ld node->right=%ld\n", node->value.var, node->left, node->right);
            DiffNode* newNode = CreateNewNode ((OPnumber) 1, CONST);
            return newNode;
        } break;

        case OPERATION: {

            switch (node->value.op) {

                case OP_ADD: {
                    printf("HEY\n");
                    DiffNode* newNode = ADD(dL, dR);
                    //RETURN('+');
                    return newNode;
                } break;

                case OP_SUB: {
                    DiffNode* newNode = SUB(dL, dR);
                    //RETURN('-');
                    return newNode;
                } break;

                case OP_DIV: {
                    DiffNode* newNode = DIV( SUB(MUL(dL, cR), MUL(cL, dR)), MUL(cR, cR) );
                    //RETURN('/');
                    return newNode;
                } break;

                case OP_MUL: {
                    DiffNode* newNode = ADD(MUL(dL, cR), MUL(cL, dR));
                    //RETURN("*");
                    return newNode;
                } break;

                case OP_POW: {

                    //RETURN("pow");

                    /*
                    if (node->left->type == VAR && node->right->type == VAR) {
                        DiffNode* newNode = Derivative(EXP(MUL(cR, LGN(cL))));
                    } else {
                        if (node->left->type == VAR) {
                            DiffNode* newNode = MUL(MUL(cR, POW(cL, SUB(cR, VAR))), dL);
                        } else {
                            DiffNode* newNode = MUL(MUL(POW(cL, cR), LGN(cL)), dR);
                        }
                    } */

                        DiffNode* newNode = NULL;
                        if (FindVar(node->left))
                          newNode = MUL(MUL(POW(cL, SUB(cR, NEWNODE(1)) ), cR), dL);

                        else {
                          DiffNode* ln_a = CreateNewNode(OP_LGN, OPERATION);
                          ln_a->right = cL;

                          newNode = MUL( MUL(cN, ln_a), dR);
                        }

                        //RETURN("pow");
                        return newNode;
                } break;

                case OP_SIN: {
                    node->value.op = OP_COS;

                    DiffNode* newNode = MUL(cN, dR);

                    node->value.op = OP_SIN;
                    //RETURN("sin");
                    return newNode;
                } break;

                case OP_COS: {
                    node->value.op = OP_SIN;

                    DiffNode* newNode = MUL(SUB(NEWNODE(0), cN), dR);

                    node->value.op = OP_COS;
                    //RETURN("cos");
                    return newNode;
                } break;

                case OP_TAN: {
                    node->value.op = OP_COS;

                    DiffNode* newNode = MUL(DIV(NEWNODE(1), POW(cN, NEWNODE(2))), dR);

                    node->value.op = OP_TAN;
                    //RETURN("tan");
                    return newNode;
                } break;

                case OP_CTN: {
                    node->value.op = OP_SIN;

                    DiffNode* newNode = MUL(SUB(NEWNODE(0), DIV(NEWNODE(1), POW(cN, NEWNODE(2)))), dR);

                    node->value.op = OP_CTN;
                    //RETURN("cotan");
                    return newNode;
                } break;

                case OP_ACS: {
                    DiffNode* newNode = MUL(SUB(NEWNODE(0), DIV(NEWNODE(1), POW(SUB(NEWNODE(1), POW(cR, NEWNODE(2))), NEWNODE(0.5)))), dR);

                    //RETURN("acos");
                    return newNode;
                } break;

                case OP_ASN: {
                    DiffNode* newNode = MUL(DIV(NEWNODE(1), POW(SUB(NEWNODE(1), POW(cR, NEWNODE(2))), NEWNODE(0.5))), dR);

                    //RETURN("asin");
                    return newNode;
                } break;

                case OP_ATN: {
                    DiffNode* newNode = MUL(DIV(NEWNODE(1), ADD(NEWNODE(1), POW(cR, NEWNODE(2)) )), dR);

                    //RETURN("atan");
                    return newNode;
                } break;

                case OP_SIH: {
                    node->value.op = OP_COH;

                    DiffNode* newNode = MUL(cN, dR);

                    node->value.op = OP_SIH;
                    //RETURN("sinh");
                    return newNode;
                } break;

                case OP_COH: {
                    node->value.op = OP_SIH;

                    DiffNode* newNode = MUL(cN, dR);

                    node->value.op = OP_COH;
                    //RETURN("cosh");
                    return newNode;
                } break;

                case OP_TGH: {
                    node->value.op = OP_COH;

                    DiffNode* newNode = MUL(DIV(NEWNODE(1), POW(cN, NEWNODE(2))), dR);

                    node->value.op = OP_TGH;
                    //RETURN("tanh");
                    return newNode;
                } break;

                case OP_LGN: {
                    DiffNode* newNode = MUL(DIV(NEWNODE(1), cR), dR);

                    //RETURN("loge");
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

    if (node->left != NULL) {
        SimplifyNode (node->left, node);
    }

    if (node->right != NULL) {
        SimplifyNode (node->right, node);
    }

    TryToSimplify (node, parent);
}

void TryToSimplify (DiffNode* node, DiffNode* parent) {

    #define SIMPLIFICATION_RULE(condition, action)  \
        if (condition) {                            \
            action;                                 \
            return;                                 \
        }

    #include "simplifications.h"

    #undef SIMPLIFICATION_RULE
}

void ChangeNodeForBinaryOperation (DiffNode* node) {

    assert (node);

    node->type = CONST;
    DeleteChildren (node);
}

void SimplifyADD (DiffNode* node) {

    assert (node);

    node->value.number = node->left->value.number + node->right->value.number;
    ChangeNodeForBinaryOperation (node);
}

void SimplifySUB (DiffNode* node) {

    assert (node);

    node->value.number = node->left->value.number - node->right->value.number;
    ChangeNodeForBinaryOperation (node);
}

void SimplifyMUL (DiffNode* node) {

    assert (node);

    node->value.number = node->left->value.number * node->right->value.number;
    ChangeNodeForBinaryOperation (node);
}

void SimplifyDIV (DiffNode* node) {

    assert (node);

    if (node->right->value.number == 0) {

        printf("\nDEVIDING ON ZERO! RESULT IS NOT CORRECT\n");
        node->value.number = 99999; //Just a huge number

    } else {
        node->value.number = node->left->value.number / node->right->value.number;
    }

    ChangeNodeForBinaryOperation (node);
}

void SimplifyPOW (DiffNode* node) {

    assert (node);

    node->value.number = pow (node->left->value.number, node->right->value.number);
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

