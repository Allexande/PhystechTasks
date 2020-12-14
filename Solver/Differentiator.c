//Version 0.1

#include "Differentiator.h"

void SimplifyTree (DiffTree* tree) {

    assert (tree);

    SimplifyNode (tree->root);
}

void SimplifyNode (DiffNode* node) {

    assert (node);

    if (node->left != NULL) {
        SimplifyNode (node->left);
    }

    if (node->right != NULL) {
        SimplifyNode (node->right);
    }

    TryToSimplify (node);
}

void TryToSimplify (DiffNode* node) {

    #define SIMPLIFICATION_RULE(condition, action)  \
        if (condition) {                            \
            action;                                 \
            return;                                 \
        }

    #include "simplifications.h"

    #undef SIMPLIFICATION_RULE
}


