//Version 0.1

//Every rule have special structure:
//SIMPLIFICATION_RULE(condition, action)

SIMPLIFICATION_RULE(                     \
                                        \
    node->left != NULL              &&   \
    node->left->type == CONST       &&   \
    node->right != NULL             &&   \
    node->right->type == CONST           \
,                                       \
    printf("SIMPL works for: node=%ld node->type=%d node->value.op=%d\n", node, node->type, node->value.op);                                    \
    switch (node->value.op) {                \
                                         \
        case OP_ADD: {                   \
            node->type = CONST;          \
            node->value.number = node->left->value.number + node->right->value.number; \
                                         \
            DeleteChild (node, 1);     \
            DeleteChild (node, 0);    \
        } break;                         \
                                         \
    }                                    \
)
