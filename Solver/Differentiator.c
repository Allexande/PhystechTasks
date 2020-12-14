//Version 0.2

#include "Differentiator.h"

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

    node->value.number = sqrt (node->right->value.number);
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

    node->value.number = tan (node->right->value.number);
    ChangeNodeForSingalOperation (node);
}

void SimplifyCTN (DiffNode* node) {

    assert (node);

    node->value.number = 1 / tan (node->right->value.number);
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

